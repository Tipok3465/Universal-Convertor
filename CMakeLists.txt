cmake_minimum_required(VERSION 3.26)
project(UniCon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(UniCon main.cpp
        App.cpp
        App.h
        Fraction.h
        BigInt.h
        solve.h
        header.h
        MegaInt.h
        MegaFraction.h
)
target_link_libraries(UniCon
        Qt::Core
        Qt::Gui
        Qt::Widgets
)