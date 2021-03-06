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

############################
##          Qt
############################
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)
# dependency
find_package(Qt5Core)
get_target_property(QtCore_location Qt5::Core LOCATION)
find_package(Qt5Gui)
get_target_property(QtCore_location Qt5::Gui LOCATION)
find_package(Qt5Widgets)
get_target_property(QtCore_location Qt5::Widgets LOCATION)
qt5_wrap_ui(QT_UI_HEADERS mainwindow.ui setting_form.ui)
qt5_add_resources(QRC ${PROJECT_SOURCE_DIR}/Zerokan_WT_Flight_Recorder.qrc)


set(SOURCE_FILES main.cpp
        hudmsg_reader.cpp hudmsg_reader.h
        mainwindow.cpp mainwindow.h
        damages.cpp damages.h
        game_state.cpp game_state.h
        user.cpp user.h
        ini_accessor.cpp ini_accessor.h
        async_client.cpp async_client.h
        setting_form.cpp setting_form.h
        timer.cpp timer.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${QT_UI_HEADERS} ${QRC})

#Use the Boost
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
# Use the Widgets module from Qt 5.
#target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Qt5::Core Qt5::Gui Qt5::Multimedia Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)


#Boost Setting
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0501")
    target_link_libraries(${PROJECT_NAME} libboost_system-mgw49-mt-s-1_58.a)
    target_link_libraries(${PROJECT_NAME} libboost_filesystem-mgw49-mt-s-1_58.a)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

if(UNIX)
    target_link_libraries(${PROJECT_NAME} boost_system pthread)
endif()