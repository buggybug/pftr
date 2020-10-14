#include "base_application.hpp"

namespace pftr
{
    namespace core
    {
        Status BaseApplication::run()
        {
            return Status::eNotImplemented;
        }


        Status BaseApplication::stop(Status exitStatus)
        {
            return Status::eNotImplemented;
        }


        Status BaseApplication::terminate(Status exitStatus)
        {
            return Status::eNotImplemented;
        }


        BaseApplication::BaseApplication(StateChangedCallbackT const &stateChangedCallback)
            : StateMachine(createStateMap(), getApplicationInitialState()),
              m_stateChangedCallback(stateChangedCallback),
              m_state(ApplicationState::eCreated),
              m_isBusy(false),
              m_isTerminating(false)
        {
        }


        BaseApplication::BaseApplication()
            : BaseApplication(nullptr)
        {
        }


        BaseApplication::~BaseApplication() noexcept
        {
        }


        util::StateMachine<ApplicationState>::StateMapT BaseApplication::createStateMap()
        {
            return { { ApplicationState::eCreated,       { ApplicationState::eInitialized,
                                                           ApplicationState::eCriticalError } },
                     { ApplicationState::eInitialized,   { ApplicationState::eStarted,
                                                           ApplicationState::eCriticalError } },
                     { ApplicationState::eStarted,       { ApplicationState::eStopping,
                                                           ApplicationState::eCriticalError } },
                     { ApplicationState::eStopping,      { ApplicationState::eStopped,
                                                           ApplicationState::eCriticalError } },
                     { ApplicationState::eStopped,       { ApplicationState::eCleanup,
                                                           ApplicationState::eCriticalError } },
                     { ApplicationState::eCleanup,       { ApplicationState::eCreated,
                                                           ApplicationState::eCriticalError } },
                     { ApplicationState::eCriticalError, { ApplicationState::eCleanup,
                                                           ApplicationState::eCreated } } };
        }
    }; // namespace core
}; // namespace pftr
