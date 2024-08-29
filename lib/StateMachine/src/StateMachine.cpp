/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 MaskUp
 */

#include "StateMachine.h"

namespace MaskUP
{
namespace StateMachine
{

void StateMachine::clearQueue ()
{
    auto state = m_state;
    changeState<::MaskUP::StateMachine::StateMachine> (this, ::MaskUP::Enum::State::WORKING);
    if (!m_emergencyRequest.empty())
    {
        m_emergencyRequest.erase(m_emergencyRequest.begin());
    }
    else if (!m_standardRequest.empty())
    {
        m_standardRequest.erase(m_standardRequest.begin());
    }
    changeState<::MaskUP::StateMachine::StateMachine> (this, state);
}

template <typename T>
void StateMachine::changeState (const T* inpCaller ,const ::MaskUP::Enum::State inState)
{
    if (inpCaller->m_state == inState
        || isAllowed<T> (inpCaller)
    )
    {
        return;
    }
    m_state = inState;
    m_pLeftBCHeadPhone->m_state = inState;
    m_pRightBCHeadPhone->m_state = inState;
    m_pLeftVibrator->m_state = inState;
    m_pRightVibrator->m_state = inState;
    m_pServomotor->m_state = inState;
}

template <typename T>
bool StateMachine::isAllowed (const T *inpCaller)
{
    bool ret = false;

    // for (const auto &allowed : m_allowedComponents)
    // {
    //     // if 
    //     (void) inpCaller;
    // }
    return ret;
}

}
}