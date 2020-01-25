add_executable(static_valarray static_valarray.cpp)
add_custom_command(TARGET static_valarray POST_BUILD COMMAND static_valarray)

