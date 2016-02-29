cmake_minimum_required(VERSION 3.3)
project(Zerokan_WT_Flight_Recorder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

###########################
##       boost
###########################
find_package(Boost REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost is ${BOOST_ROOT}")
    message(STATUS "Boost directories found at ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libraries found at ${Boost_LIBRARY_DIRS}")
    message(STATUS "Boost component libraries to be linked are ${Boost_LIBRARIES}")
    message(STATUS "Boost version found is ${Boost_VERSION}")
    include_directories("../include" "${Boost_INCLUDE_DIRS}")
    link_directories("${Boost_LIBRARY_DIRS}")
elseif()
    message("Boost NOT Found!")
endif()

set(SOURCE_FILES main.cpp hudmsg_reader.cpp hudmsg_reader.h http_client.cpp http_client.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0501")
    target_link_libraries(${PROJECT_NAME} libboost_system-mgw49-mt-s-1_58.a)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()