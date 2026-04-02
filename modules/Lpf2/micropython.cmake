add_library(lpf2_mod INTERFACE)

set(LPF2_DIR ${CMAKE_CURRENT_LIST_DIR}/../../lib/Lpf2)

# Add source files to the library.
file(GLOB_RECURSE LPF2_SOURCES "${LPF2_DIR}/src/Lpf2/*.cpp")
target_sources(lpf2_mod INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/example.cpp
    ${CMAKE_CURRENT_LIST_DIR}/examplemodule.c
    ${LPF2_SOURCES}
)

# Add the current directory as an include directory.
target_include_directories(lpf2_mod INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    ${LPF2_DIR}/include
    ${LPF2_DIR}/src
)

target_compile_features(lpf2_mod INTERFACE cxx_std_20)

# Link the INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE lpf2_mod)
