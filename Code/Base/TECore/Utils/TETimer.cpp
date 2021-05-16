#include "TETimer.h"
#include <assert.h>
#include <chrono>
#include <thread>

TE::Time::Timer::Timer()
    : m_isRunning(true),
      m_start(std::chrono::high_resolution_clock::now()) {
    m_update = m_start;
}

void TE::Time::Timer::Restart() {
    m_isRunning = true;
    m_start     = std::chrono::high_resolution_clock::now();
    m_update    = m_start;
}

void TE::Time::Timer::Stop() {
    m_isRunning = false;
    Update();
}

bool TE::Time::Timer::IsRunning() {
    return m_isRunning;
}

U64 TE::Time::Timer::GetTime(Units unit) {
    switch (unit) {
    case TE::Time::Units::Milliseconds:
        return GetMilliseconds();
    case TE::Time::Units::Microseconds:
        return GetMicroseconds();
    case TE::Time::Units::Nanoseconds:
        return GetNanoseconds();
    }

    assert(false && "Should not get here");
    return 0;
}

U64 TE::Time::Timer::GetMilliseconds() {
    auto tp = std::chrono::high_resolution_clock::now() - m_start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp).count();
}

U64 TE::Time::Timer::GetMicroseconds() {
    auto tp = std::chrono::high_resolution_clock::now() - m_start;
    return std::chrono::duration_cast<std::chrono::microseconds>(tp).count();
}

U64 TE::Time::Timer::GetNanoseconds() {
    auto tp = std::chrono::high_resolution_clock::now() - m_start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(tp).count();
}

void TE::Time::Timer::Update() {
    m_previousUpdate = m_update;
    m_update         = std::chrono::high_resolution_clock::now();
}

U64 TE::Time::Timer::GetUpdatedTime(Units unit) {
    switch (unit) {
    case TE::Time::Units::Milliseconds:
        return GetUpdatedMilliseconds();
    case TE::Time::Units::Microseconds:
        return GetUpdatedMicroseconds();
    case TE::Time::Units::Nanoseconds:
        return GetUpdatedNanoseconds();
    }

    assert(false && "Should not get here");
    return 0;
}

U64 TE::Time::Timer::GetUpdatedMilliseconds() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(m_update - m_start).count();
}

U64 TE::Time::Timer::GetUpdatedMicroseconds() {
    return std::chrono::duration_cast<std::chrono::microseconds>(m_update - m_start).count();
}

U64 TE::Time::Timer::GetUpdatedNanoseconds() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(m_update - m_start).count();
}

U64 TE::Time::Timer::GetDeltaTime(Units unit) {
    switch (unit) {
    case TE::Time::Units::Milliseconds:
        return GetDeltaMilliseconds();
    case TE::Time::Units::Microseconds:
        return GetDeltaMicroseconds();
    case TE::Time::Units::Nanoseconds:
        return GetDeltaNanoseconds();
    }

    assert(false && "Should not get here");
    return 0;
}

U64 TE::Time::Timer::GetDeltaMilliseconds() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(m_update - m_previousUpdate).count();
}

U64 TE::Time::Timer::GetDeltaMicroseconds() {
    return std::chrono::duration_cast<std::chrono::microseconds>(m_update - m_previousUpdate).count();
}

U64 TE::Time::Timer::GetDeltaNanoseconds() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(m_update - m_previousUpdate).count();
}
