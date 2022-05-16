set(TARGET ${PFTR_UTIL_LIBRARY_TARGET})

# Public headers
set(HEADERS
    include/pftr/util/interfaces/exception.hpp
    include/pftr/util/base_exception.hpp
    include/pftr/util/state_machine.hpp
    include/pftr/util/singleton.hpp)

# Private headers
set(HEADERS ${HEADERS})

set(SOURCES
    src/base_exception.cpp)

add_library(${TARGET} ${SOURCES} ${HEADERS})

target_include_directories(${TARGET} PUBLIC include)
