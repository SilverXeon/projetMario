cmake_minimum_required(VERSION 3.3)
project(projetMario)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Programme.hpp src/Menu.hpp src/Application.hpp src/Niveau.hpp src/Bloc.hpp src/Personnage.hpp src/HUD.hpp src/Mario.hpp src/Monstre.hpp src/EcranMort.hpp)
add_executable(projetMario ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(projetMario ${SFML_LIBRARIES})
endif()

