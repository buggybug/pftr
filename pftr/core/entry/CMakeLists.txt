set(TARGET ${PFTR_CORE_APPLICATION_TARGET})

set(SOURCES
    src/factories/application.cpp
    src/base_application.cpp
    src/main.cpp)

set(HEADERS
    src/interfaces/application.hpp
    src/base_application.hpp)

set(LIBRARIES
    ${PFTR_UTIL_LIBRARY_TARGET})

if(WIN32)
    set(SOURCES ${SOURCES}
        src/windows/windows_application.cpp)

    set(HEADERS ${HEADERS}
        src/windows/windows_application.hpp)
endif()

if(UNIX)
    set(SOURCES ${SOURCES}
        src/linux/linux_application.cpp)

    set(HEADERS ${HEADERS}
        src/linux/linux_application.hpp)
endif()

add_executable(${TARGET} ${SOURCES} ${HEADERS})

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${TARGET} ${LIBRARIES})

if(WIN32)
    add_target_link_flags(${TARGET} "/SUBSYSTEM:WINDOWS")
endif()
