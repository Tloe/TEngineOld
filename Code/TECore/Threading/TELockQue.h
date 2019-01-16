#ifndef TELOCKQUE_H
#define TELOCKQUE_H

#include <memory>
#include <mutex>
#include <condition_variable>

namespace TE
{
    namespace Threading
    {
        template <typename T>
        class LockQue
        {
            struct Node; typedef std::unique_ptr<Node> NodeUPtr;
        public:
            typedef std::shared_ptr<T> T_SPtr;

            LockQue()
                : m_head(new Node)
                , m_tail(m_head.get())
            {}

            T_SPtr TryPop()
            {
                NodeUPtr oldHead = TryPopHead();

                return oldHead ? oldHead->data : std::shared_ptr<T>();
            }

            bool TryPop(T& value)
            {
                const NodeUPtr oldHead = TryPopHead(value);

                return oldHead != nullptr;
            }

            T_SPtr WaitPop()
            {
                const NodeUPtr oldHead = WaitPopHead();
                return oldHead->data;
            }

            void WaitPop(T& value)
            {
                const NodeUPtr oldHead=WaitPopHead(value);
            }

            void Push(T value)
            {
                T_SPtr newData = std::make_shared<T>(std::move(value));
                NodeUPtr p = std::make_unique<Node>();
                {
                    std::lock_guard<std::mutex> tailLock(m_tailMutex);
                    m_tail->data = newData;
                    Node* newTail = p.get();
                    m_tail->next = std::move(p);
                    m_tail = newTail;
                }
                m_dataCondition.notify_one();
            }
            bool Empty()
            {
                std::lock_guard<std::mutex> headLock(m_headMutex);
                return m_head.get() == GetTail();
            }

        private:
            struct Node
            {
                T_SPtr data;
                NodeUPtr next;
            };

            LockQue(const LockQue&){}
            LockQue& operator=(const LockQue&){}

            Node* GetTail()
            {
                std::lock_guard<std::mutex> tailLock(m_tailMutex);

                return m_tail;
            }

            NodeUPtr PopHead()
            {
                NodeUPtr oldHead(std::move(m_head));
                m_head=std::move(oldHead->next);

                return oldHead;
            }

            std::unique_lock<std::mutex> WaitForData()
            {
                std::unique_lock<std::mutex> headLock(m_headMutex);
                m_dataCondition.wait(headLock, [&] { return m_head.get() != GetTail(); });

                return headLock;
            }

            NodeUPtr WaitPopHead()
            {
                std::unique_lock<std::mutex> headLock(WaitForData());

                return PopHead();
            }

            NodeUPtr WaitPopHead(T& value)
            {
                std::unique_lock<std::mutex> headLock(WaitForData());
                value = std::move(*m_head->data);

                return PopHead();
            }

            NodeUPtr TryPopHead()
            {
                std::lock_guard<std::mutex> headLock(m_headMutex);
                if(m_head.get() == GetTail())
                {
                    return NodeUPtr(nullptr);
                }

                return PopHead();
            }

            NodeUPtr TryPopHead(T& value)
            {
                std::lock_guard<std::mutex> headLock(m_headMutex);
                if(m_head.get() == GetTail())
                {
                    return NodeUPtr(nullptr);
                }
                value = std::move(*m_head->data);

                return PopHead();
            }

            std::mutex m_headMutex;
            NodeUPtr m_head;
            std::mutex m_tailMutex;
            Node* m_tail;
            std::condition_variable m_dataCondition;
        };
    }
}

#endif
