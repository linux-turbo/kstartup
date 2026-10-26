cmake_minimum_required(VERSION 3.16)

project(kstartup
    VERSION 1.0.0
    DESCRIPTION "Delayed autostart manager for desktop environments"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core LinguistTools)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
)

set(HEADERS
    include/mainwindow.h
)

set(TS_FILES
    translations/kstartup_en.ts
    translations/kstartup_fr.ts
)

qt6_add_translations(kstartup TS_FILES ${TS_FILES})

add_executable(kstartup ${SOURCES} ${HEADERS})

target_link_libraries(kstartup PRIVATE Qt6::Widgets Qt6::Core)

install(TARGETS kstartup DESTINATION bin)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets/kstartup.desktop")
    install(FILES assets/kstartup.desktop DESTINATION share/applications)
endif()
