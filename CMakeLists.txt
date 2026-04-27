cmake_minimum_required(VERSION 4.2)
project(GymProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(diet)
include_directories(membership)
include_directories(progress)
include_directories(recomendation)
include_directories(user)
include_directories(utils)
include_directories(workout)

add_executable(GymProject
        diet/diet.cpp
        diet/diet.h
        main/main.cpp
        membership/membership.cpp
        membership/membership.h
        progress/progress.cpp
        progress/progress.h
        recomendation/recomendation.cpp
        recomendation/recomendation.h
        user/user.cpp
        user/user.h
        utils/utils.cpp
        utils/utils.h
        workout/workout.cpp
        workout/workout.h)
