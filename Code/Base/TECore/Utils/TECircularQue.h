#ifndef TECIRCULARQUE_H
#define TECIRCULARQUE_H

#include "TEDataTypes.h"

namespace TE
{
    namespace Utils
    {
        template <typename T, int Size>
        class CircularQue
        {
        public:
            CircularQue() : m_que(Size), m_head(0), m_tail(0) {}

            void Push(T data)
            {
                m_que[m_tail] = data;
                Addvance(m_tail);
            }

            U32 GetTailIndex() const
            {
                return m_tail;
            }

            U32 GetHeadIndex() const
            {
                return m_head;
            }

            const T & GetHead() const
            {
                return m_que[m_head];
            }

            void Pop()
            {
                if(Empty())
                    return;

                Addvance(m_head);
            }

            bool PopToIndex(U32 index)
            {
                while(m_head != m_tail && m_head != index)
                    Addvance(m_head);

                if(m_head == m_tail)
                    return false;

                return true;
            }

            bool Empty() const
            {
                return m_head == m_tail;
            }
        private:
            void Addvance(U32 & index)
            {
                index++;
                if(index >= m_que.size())
                    index -= m_que.size();
            }

            std::vector<T> m_que;
            U32 m_head;
            U32 m_tail;
        };

    }
}

#endif
