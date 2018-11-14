#include <TETaskManager.h>
#include "boost/thread.hpp"
#include <srutil/delegate/delegate.hpp>

TE::Engine::ThreadedTask::ThreadedTask()
{

}

void TE::Engine::ThreadedTask::SetTaskNotifier( TaskNotifier& taskNotifier )
{
	m_taskNotifier = &taskNotifier;
	m_taskNotifier->AddJobCount();
}

void TE::Engine::ThreadedTask::Execute()
{
	bool threadedExecution = true;
	TaskExecution(threadedExecution);
	m_taskNotifier->Done();
}

TE::Engine::TaskManager::TaskManager()
	:
	m_ioservice(boost::thread::hardware_concurrency()),
	m_work(m_ioservice)
{
	U32 m_threadCount = GetThreadCount();

	for (U32 i = 0; i < m_threadCount; ++i)
	{
		//m_threadGroup.create_thread(boost::bind(&boost::asio::io_service::run, &m_ioservice ));
		m_threadGroup.create_thread<srutil::delegate0<size_t> >(
			srutil::delegate0<size_t>::from_method<boost::asio::io_service, &boost::asio::io_service::run>(&m_ioservice));
	}
}

TE::Engine::TaskManager::~TaskManager()
{
	m_ioservice.stop();
}

U32 TE::Engine::TaskManager::GetThreadCount()
{
	return boost::thread::hardware_concurrency();
}

void TE::Engine::TaskManager::WaitForJobs()
{
    m_taskNotifier.Wait();
}

void TE::Engine::TaskManager::CallFuntionOnAllThreads(TE::Engine::Func0 function)
{

}

void TE::Engine::TaskManager::PostThreadedTask( ThreadedTask& threadedTask )
{
	threadedTask.SetTaskNotifier(m_taskNotifier);
    m_ioservice.post<srutil::delegate0<void> >(
		srutil::delegate0<void>::from_method<ThreadedTask, &ThreadedTask::Execute>(&threadedTask));
}
