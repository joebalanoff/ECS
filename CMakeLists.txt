cmake_minimum_required(VERSION 3.31)
project(ECS VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED O)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(src)

# find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL2_image REQUIRED CONFIG)

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_target(run
	COMMAND ${CMAKE_COMMAND} --build . --target ${PROJECT_NAME}
	COMMAND ${PROJECT_NAME}
	DEPENDS ${PROJECT_NAME}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

if(TARGET SDL2::SDL2main)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

if(TARGET SDL2_image::SDL2_image)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
else()
    message(WARNING "SDL2_image target not found, using fallback linking method.")
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
