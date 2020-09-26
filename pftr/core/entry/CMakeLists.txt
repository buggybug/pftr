set(TARGET ${PFTR_CORE_APPLICATION_TARGET})

set(SOURCES
    src/main.cpp)

add_executable(${TARGET} ${SOURCES})

if(WIN32)
    add_target_link_flags(${TARGET} "/SUBSYSTEM:WINDOWS")
endif()
