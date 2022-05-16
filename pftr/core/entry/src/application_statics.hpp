/// \file application_statics.hpp
/// \brief This module declares the API that provides an access to the application object
///        that implements IApplication interface.

#ifndef APPLICATION_STATICS__084A4BAD_5E36_4B2E_9197_CB35DF0CA83C__INCLUDED_
#define APPLICATION_STATICS__084A4BAD_5E36_4B2E_9197_CB35DF0CA83C__INCLUDED_

#include <pftr/pftr_def.hpp>
#include "interfaces/application.hpp"

namespace pftr
{
    namespace core
    {
        /// \brief Allocates and initializes the application object if it was not created
        ///        before, otherwise simply provides an access to the underlying
        ///        application object.
        /// \returns The pointer to the object that implements the IApplication interface.
        interfaces::IApplication *createApplication();


        /// \brief Provides an access to the underlying application object.
        /// \returns The pointer to the object that implements the IApplication interface.
        [[nodiscard("Pointer to the application object has been obtained, yet ignored.")]]
        interfaces::IApplication *getApplication() noexcept;
    }; // namespace core
}; // namespace pftr

#endif // APPLICATION_STATICS__084A4BAD_5E36_4B2E_9197_CB35DF0CA83C__INCLUDED_
