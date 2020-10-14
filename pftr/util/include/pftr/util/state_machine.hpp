#ifndef STATE_MACHINE_HPP__CC809410_98B1_4027_87B3_A6903E8239A6__INCLUDED_
#define STATE_MACHINE_HPP__CC809410_98B1_4027_87B3_A6903E8239A6__INCLUDED_

#include <map>
#include <vector>
#include "base_exception.hpp"

namespace pftr
{
    namespace util
    {
        template<class StateT> class BadStateException : public BaseException
        {
        public:
            BadStateException(Status status, 
                              StateT currentState,
                              StateT requestedState,
                              std::string const &description)
                : BaseException(status, description),
                  m_currentState(currentState),
                  m_requestedState(requestedState)
            {
            }


            BadStateException(Status status,
                              StateT currentState,
                              StateT requestedState,
                              std::string &&description)
                : BaseException(status, std::move(description)),
                  m_currentState(currentState),
                  m_requestedState(requestedState)
            {
            }


            BadStateException(Status status,
                              StateT currentState,
                              StateT requestedState,
                              char const *description = nullptr)
                : BaseException(status, description),
                  m_currentState(currentState),
                  m_requestedState(requestedState)
            {
            }


            BadStateException(BadStateException const &) = default;
            BadStateException &operator=(BadStateException const&) = default;


            BadStateException() = delete;


        private:
            StateT const m_currentState;
            StateT const m_requestedState;
        };


        template<class StateT> class StateMachine
        {
        public:
            using StateMapT = std::map<StateT, std::vector<StateT>>;


            StateMachine() = delete;


            StateMachine(StateMapT const &stateMap, StateT initialState)
                : m_stateMap(stateMap),
                  m_currentState(initialState)
            {
            }


            StateMachine(StateMapT &&stateMap, StateT initialState)
                : m_stateMap(stateMap),
                  m_currentState(initialState)
            {
            }


            StateMachine(StateMachine const &stateMachine)
                : m_stateMap(stateMachine.m_stateMap),
                  m_currentState(stateMachine.m_currentState)
            {
            }


            StateMachine(StateMachine &&stateMachine)
                : m_stateMap(std::move(stateMachine.m_stateMap)),
                  m_currentState(stateMachine.m_currentState)
            {
            }


            ~StateMachine() noexcept = default;


            StateMachine &operator=(StateMachine const &stateMachine)
            {
                m_stateMap = stateMachine.m_stateMap;
                m_currentState = stateMachine.m_currentState;
            }


            StateMachine &operator=(StateMachine &&stateMachine)
            {
                m_stateMap = std::move(stateMachine.m_stateMap);
                m_currentState = stateMachine.m_currentState;
            }


            StateT getCurrentState() const noexcept
            {
                return m_currentState;
            }


            bool canEnterState(StateT newState) const noexcept
            {
                auto const &allowedStates = m_stateMap[m_currentState];
                auto const &it = allowedStates.find(newState);
                
                return allowedStates.cend() != it;
            }


            bool tryEnterState(StateT newState) noexcept
            {
                if (!canEnterState(newState))
                {
                    return false;
                }

                m_currentState = newState;

                return true;
            }


            void enterStateOrThrow(StateT newState)
            {
                if (!tryEnterState(newState))
                {
                    throw BadStateException(Status::eInvalidState,
                                            m_currentState,
                                            newState);
                }
            }


        private:
            StateMapT const m_stateMap;
            StateT m_currentState;
        };
    }; // namespace util
}; // namespace pftr

#endif // STATE_MACHINE_HPP__CC809410_98B1_4027_87B3_A6903E8239A6__INCLUDED_
