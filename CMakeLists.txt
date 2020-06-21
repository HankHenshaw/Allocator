cmake_minimum_required(VERSION 3.5)

project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(SOURCE main.cpp)
set(HEADERS hard.h myallocator.h mylist.h)

add_executable(alloc ${SOURCE} ${HEADERS})

set_target_properties(alloc PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wextra;-Wpedantic;-Wall"
)

install(TARGETS alloc RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT HankHenshow at github.com)

include(CPack)