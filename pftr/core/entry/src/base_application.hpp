#ifndef BASE_APPLICATION_HPP__5EC131BD_896F_4E48_97E3_071D6A331A29__INCLUDED_
#define BASE_APPLICATION_HPP__5EC131BD_896F_4E48_97E3_071D6A331A29__INCLUDED_

#include <atomic>
#include <functional>
#include <pftr/util/state_machine.hpp>
#include "interfaces/application.hpp"

namespace pftr
{
    namespace core
    {
        class BaseApplication
            : public interfaces::IApplication,
              private util::StateMachine<ApplicationState>
        {
        public:
            Status run() override;
            Status stop(Status exitStatus) override;
            Status terminate(Status exitStatus) override;

            BaseApplication(BaseApplication const &) = delete;
            BaseApplication(BaseApplication &&) = delete;
            BaseApplication &operator=(BaseApplication const &) = delete;
            BaseApplication &operator=(BaseApplication &&) = delete;

        protected:
            using StateChangedCallbackT = std::function<Status(ApplicationState)>;

            explicit BaseApplication(StateChangedCallbackT const &stateChangedCallback);
            BaseApplication();
            virtual ~BaseApplication() noexcept;

        private:
            static StateMapT createStateMap();

            StateChangedCallbackT m_stateChangedCallback;
            ApplicationState m_state;
            std::atomic_bool m_isBusy;
            std::atomic_bool m_isTerminating;
        };
    }; // namespace core
}; // namespace pftr

#endif // BASE_APPLICATION_HPP__5EC131BD_896F_4E48_97E3_071D6A331A29__INCLUDED_
