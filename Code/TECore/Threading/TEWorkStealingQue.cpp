#include "TEWorkStealingQue.h"

#include <iostream>

TE::Threading::WorkStealingQue::WorkStealingQue()
{

}

void TE::Threading::WorkStealingQue::Push(FunctionWrapper data)
{
    std::lock_guard<std::mutex> lock(m_queMutex);

    m_que.push_front(std::move(data));
}


bool TE::Threading::WorkStealingQue::Empty() const
{
    std::lock_guard<std::mutex> lock(m_queMutex);

    return m_que.empty();
}

bool TE::Threading::WorkStealingQue::TryPop(FunctionWrapper &res)
{
    std::lock_guard<std::mutex> lock(m_queMutex);
    if(m_que.empty())
    {
        return false;
    };

    res = std::move(m_que.front());
    m_que.pop_front();

    return true;
}


bool TE::Threading::WorkStealingQue::TrySteal(FunctionWrapper &res)
{
    std::lock_guard<std::mutex> lock(m_queMutex);

    if(m_que.empty()) return false;

    res = std::move(m_que.back());
    m_que.pop_back();

    return true;
}

