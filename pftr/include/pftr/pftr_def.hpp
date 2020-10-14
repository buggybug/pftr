#ifndef PFTR_DEF_HPP__783F446A_0C51_41AF_B513_671336953CEE__INCLUDED_
#define PFTR_DEF_HPP__783F446A_0C51_41AF_B513_671336953CEE__INCLUDED_

#include <cstdint>
#include <map>
#include <string>

namespace pftr
{
    enum class Status : int32_t
    {
        eSuccess                = static_cast<int32_t>(0x00000000),

        eAlreadyExists          = static_cast<int32_t>(0x80000001),
        eNotImplemented         = static_cast<int32_t>(0x80000002),

        eAlreadyRunning         = static_cast<int32_t>(0x80000003),
        eTerminating            = static_cast<int32_t>(0x80000004),
        eStopping               = static_cast<int32_t>(0x80000005),
        eCanceled               = static_cast<int32_t>(0x80000006),
        eTimeout                = static_cast<int32_t>(0x80000007),

        eInvalidArgument        = static_cast<int32_t>(0x80000008),
        eInvalidPointer         = static_cast<int32_t>(0x80000009),
        eInvalidState           = static_cast<int32_t>(0x8000000A),

        eBufferOverflow         = static_cast<int32_t>(0x8000000B),
        eIntegerOverflow        = static_cast<int32_t>(0x8000000C),

        eOutOfMemory            = static_cast<int32_t>(0x8000000D)
    };


    constexpr bool isSuccess(Status status) noexcept
    {
        return static_cast<int32_t>(status) >= 0;
    }


    constexpr bool isFailure(Status status) noexcept
    {
        return !isSuccess(status);
    }


    enum class ApplicationState : uint32_t
    {
        eCreated = 0,
        eInitialized,
        eStarted,
        eStopping,
        eStopped,
        eCleanup,
        eCriticalError
    };


    constexpr ApplicationState getApplicationInitialState() noexcept
    {
        return ApplicationState::eCreated;
    }


    namespace internals
    {
        using StatusDescriptionMap = std::map<Status, std::string const>;

        static std::string const c_statusNotFoundString("Unknown status");

        static StatusDescriptionMap const c_statusDescriptionMap =
            { { Status::eSuccess,         "" },
              { Status::eAlreadyExists,   "" },
              { Status::eNotImplemented,  "" },
              { Status::eAlreadyRunning,  "" },
              { Status::eTerminating,     "" },
              { Status::eStopping,        "" },
              { Status::eCanceled,        "" },
              { Status::eTimeout,         "" },
              { Status::eInvalidArgument, "" },
              { Status::eInvalidPointer,  "" },
              { Status::eInvalidState,    "" },
              { Status::eBufferOverflow,  "" },
              { Status::eIntegerOverflow, "" },
              { Status::eOutOfMemory,     "" } };

        inline std::string const &getStatusDescription(Status status) noexcept
        {
            auto const &it = c_statusDescriptionMap.find(status);

            if (c_statusDescriptionMap.cend() == it)
            {
                return c_statusNotFoundString;
            }

            return it->second;
        }
    }; // namespace internals


    inline std::string const &getStatusDescription(Status status) noexcept
    {
        return internals::getStatusDescription(status);
    }
}; // namespace pftr

#endif // PFTR_DEF_HPP__783F446A_0C51_41AF_B513_671336953CEE__INCLUDED_
