cmake_minimum_required( VERSION 3.3 )

project( Neuro )

include_directories( include include/Modules )

file( GLOB EXEC_FILES src/*.cpp )

add_executable( Neuro ${EXEC_FILES}) 

target_link_libraries( Neuro -lcurl -ljsoncpp )

