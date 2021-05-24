#include "TEFlowControl.h"
#include "TETime.h"

#include <iostream>

namespace {
    const U32 rttThreshold = TE::Time::Microseconds::Second / 4;
    const U32 oneMinute    = TE::Time::Microseconds::Second * 60;
    const U32 tenSeconds   = TE::Time::Microseconds::Second * 10;
}

TE::Net::FlowControl::FlowControl() { Reset(); }

void TE::Net::FlowControl::Reset() {
    mode                          = Mode::Bad;
    m_penaltyTime                 = Time::Microseconds::Second * 4;
    m_goodConditionsTime          = 0;
    m_penaltyReductionAccumulator = 0;
}

void TE::Net::FlowControl::Update(U64 deltaTime, U64 rtt) {
    if (mode == Mode::Good) {
        if (rtt > rttThreshold) {
            mode = Mode::Bad;
            std::cout << "send rate 10!" << std::endl;
            if (m_goodConditionsTime < tenSeconds && m_penaltyTime < oneMinute) {
                m_penaltyTime *= 2;
                if (m_penaltyTime > oneMinute)
                    m_penaltyTime = oneMinute;
            }
            m_goodConditionsTime          = 0;
            m_penaltyReductionAccumulator = 0;
            return;
        }

        m_goodConditionsTime += deltaTime;
        m_penaltyReductionAccumulator += deltaTime;

        if (m_penaltyReductionAccumulator > tenSeconds &&
            m_penaltyTime > Time::Microseconds::Second) {
            m_penaltyTime /= 2;
            if (m_penaltyTime < Time::Microseconds::Second)
                m_penaltyTime = Time::Microseconds::Second;
            m_penaltyReductionAccumulator = 0;
        }
    }

    if (mode == Mode::Bad) {
        if (rtt <= rttThreshold)
            m_goodConditionsTime += deltaTime;
        else
            m_goodConditionsTime = 0;

        if (m_goodConditionsTime > m_penaltyTime) {
            m_goodConditionsTime          = 0;
            m_penaltyReductionAccumulator = 0;
            mode                          = Mode::Good;
            std::cout << "send rate 30!" << std::endl;
            return;
        }
    }
}

U32 TE::Net::FlowControl::GetSendRate() { return mode == Mode::Good ? 30 : 10; }
