#ifndef TETASKMANAGER_H
#define TETASKMANAGER_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "TEDataTypes.h"

namespace TE
{
	namespace Engine { class SystemTask; }

	namespace Engine
	{
		class TaskNotifier
		{
		public:
			TaskNotifier() : m_waiting(false),m_jobsCount(0) {}

			void AddJobCount()
			{
				++m_jobsCount;
			}

			void Done()
			{
				boost::mutex::scoped_lock lock(m_mutex);
				if(--m_jobsCount <= 0 && m_waiting)
				{
					m_conditional.notify_one();
				}
			}

			void Wait()
			{
				boost::mutex::scoped_lock lock(m_mutex);
				if (m_jobsCount > 0)
				{
					m_waiting = true;
					m_conditional.wait(lock);
				}
				m_waiting = false;
			}
		private:
			bool m_waiting;
			U32 m_jobsCount;
			boost::mutex m_mutex;
			boost::condition_variable m_conditional;
		};

		class ThreadedTask
		{
		public:
			ThreadedTask();

			void SetTaskNotifier(TaskNotifier& taskNotifier);
			void Execute();
		private:
			virtual void TaskExecution(bool threaded) = 0;
			
			TaskNotifier* m_taskNotifier;
		};

        typedef void (*Func0)();
		class TaskManager
		{
		public:
			typedef std::vector<SystemTask*> SystemTaskVec;

            TaskManager();
			~TaskManager();

			U32 GetThreadCount();

			void PostThreadedTask(ThreadedTask& threadedTask);
			void WaitForJobs();
            void CallFuntionOnAllThreads(Func0 function);
		private:
			TaskNotifier m_taskNotifier;
			U32 m_threadCount;

			boost::thread_group m_threadGroup;
			boost::asio::io_service m_ioservice;
			boost::asio::io_service::work m_work;
		};
	}
}

#endif
