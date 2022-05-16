/// \file singleton.hpp
/// \brief This module declares and implements the Singleton template class.

#ifndef SINGLETON_HPP__0C652546_C433_4BE0_A8DD_3569713F99C0__INCLUDED_
#define SINGLETON_HPP__0C652546_C433_4BE0_A8DD_3569713F99C0__INCLUDED_

#include <cassert>
#include <memory>
#include <mutex>
#include <type_traits>

namespace pftr
{
    namespace util
    {
        /// \brief The base template type that restricts the instantiation of a class to
        ///        one "single" instance.
        /// \tparam TInterface the type to be used to interact with the underlying
        ///         Singleton object.
        /// \remarks Only the initialization order can be controlled, the physical
        ///          destruction is expected to take place in the context of the main
        ///          thread, yet the order is undefined. Blocking Singleton calls from
        ///          the context of the internal worker thread may result in a deadlock
        ///          during cleanup in case of an invalid design.
        template<typename TInterface>
        class Singleton
        {
        public:
            /// \brief Checks whether the Singleton object is initialized.
            /// \returns True if the Singleton object is initialized, false otherwise.
            [[nodiscard("Status of the Singleton object has been queried, yet ignored.")]]
            static bool isValid() noexcept
            {
                return nullptr != m_instance;
            }


            /// \brief Allocates and initializes the Singleton object.
            /// \tparam TImpl the type that implements interface \ref TInterface.
            /// \param arguments initialization parameters that will be forwarded to the
            ///                  constructor of the \ref TImpl object.
            /// \returns The pointer of type \ref TInterface to the newly initialized
            ///          Singleton object.
            template<typename TImpl,
                     typename... TArgs>
            static TInterface *createInstance(TArgs &&...arguments) noexcept(
#ifdef WIN32
                // CRT implementation is built on top of the INIT_ONCE structure and
                // related API usage, thus exception specification simply follows rules
                // of the invokable object.
                noexcept(std::make_unique<TImpl>(std::forward<TArgs>(arguments)...))
#else // ! WIN32
                // The pthread implementation does not result in the abort call in case
                // the low-level API routine fails, instead it throws an exception of the
                // type std::system_error, making the function potentially throwing.
                false
#endif // WIN32
                )
            {
                static_assert(std::is_base_of<TInterface, TImpl>::value, "Implementation class does not inherit the interface.");
                static_assert(!std::is_abstract<TImpl>::value, "Implementation class cannot be abstract.");

                static std::once_flag singletonInitialized;
                bool isFirstRun = false;

                std::call_once(singletonInitialized, [&isFirstRun, &arguments...]()
                {
                    m_instance = std::make_unique<TImpl>(std::forward<TArgs>(arguments)...);
                    isFirstRun = true;
                });

                // Creating instance makes sense only on the first run, all subsequent
                // calls will simply ignore initialization arguments and just return the
                // object pointer, which may not be the behavior the caller expects.
                assert(isFirstRun && "Singleton object has been already initialized.");

                return m_instance.get();
            }


            /// \brief Allocates and initializes the Singleton object.
            /// \param arguments initialization parameters that will be forwarded to the
            ///                  constructor of the \ref TImpl object.
            /// \returns The pointer of type \ref TInterface to the newly initialized
            ///          Singleton object.
            /// \remarks This overload assumes that \ref TInterface is both the interface
            ///          and the implementation class.
            template<typename... TArgs>
            static TInterface *createInstance(TArgs &&...arguments) noexcept(
                noexcept(createInstance<TInterface>(std::forward<TArgs>(arguments)...)))
            {
                return createInstance<TInterface>(std::forward<TArgs>(arguments)...);
            }


            /// \brief Provides an access to the underlying Singleton object.
            /// \returns The pointer of type \ref TInterface to the Singleton object.
            [[nodiscard("Pointer to the Singleton object has been obtained, yet ignored.")]]
            static TInterface *getInstance() noexcept
            {
                assert(isValid() && "Singleton object is not initialized.");
                return m_instance.get();
            }


            // The copy constructor and operator are implicitly removed by the member
            // unique pointer, prevent an accidental move of the Singleton object by
            // explicitly deleting all related routines.
            Singleton(Singleton &&) = delete;
            Singleton &operator=(Singleton &&) = delete;

        protected:
            Singleton() noexcept = default;
            ~Singleton() noexcept = default;

        private:
            static std::unique_ptr<TInterface> m_instance;
        };


        /// \brief The pointer to the Singleton object of type \ref TInterface, CAN NOT
        ///        BE USED directly, instead call the \ref getInstance() method to
        ///        obtain its raw representation.
        template<typename TInterface> std::unique_ptr<TInterface> Singleton<TInterface>::m_instance;
    }; // namespace util
}; // namespace pftr

#endif // SINGLETON_HPP__0C652546_C433_4BE0_A8DD_3569713F99C0__INCLUDED_
