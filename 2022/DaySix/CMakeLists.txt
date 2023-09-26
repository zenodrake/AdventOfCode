##ideally i'd like to have one command which both builds then runs the project
## this could be done with a bash script


set(PROJECT_NAME DaySix)


project(${PROJECT_NAME})

add_executable(main main.cpp day_six.cpp)

#target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")
