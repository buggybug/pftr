set(TARGET ${PFTR_CORE_APPLICATION_TARGET})

set(SOURCES
    src/application_statics.cpp
    src/base_application.cpp
    src/main.cpp)

set(HEADERS
    src/interfaces/application.hpp
    src/application_statics.hpp
    src/base_application.hpp)

set(LIBRARIES
    ${PFTR_UTIL_LIBRARY_TARGET})

if(WIN32)
    set(SOURCES ${SOURCES}
        src/windows/windows_application.cpp)

    set(HEADERS ${HEADERS}
        src/windows/windows_application.hpp)

    set(ADDITIONAL_EXECUTABLE_PROPERTIES WIN32)
endif()

if(UNIX)
    set(SOURCES ${SOURCES}
        src/linux/linux_application.cpp)

    set(HEADERS ${HEADERS}
        src/linux/linux_application.hpp)
endif()

add_executable(${TARGET}
    ${ADDITIONAL_EXECUTABLE_PROPERTIES}
    ${SOURCES}
    ${HEADERS})

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${TARGET} ${LIBRARIES})
