cmake_minimum_required(VERSION 3.16)

project(Assistant VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Network REQUIRED)

#指定头文件路径（这里都是库的头文件）
include_directories(CMAKE_CURRENT_SOURCE_DIR
    ./library/supernote/include/
    ./library/docx/include/
)

#指定库的路径
link_directories(CMAKE_CURRENT_SOURCE_DIR
    ./library/supernote/lib/
    ./library/docx/lib/
)

qt_add_executable(appAssistant
    utils.h
    utils.cpp
    httpclient.h
    httpclient.cpp
    main.cpp
    test.h
    test.cpp
)

qt_add_qml_module(appAssistant
    URI Assistant
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(appAssistant PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

#指定链接的库
target_link_libraries(appAssistant
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Network
    libSupernote
    libDocx
)

install(TARGETS appAssistant
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
