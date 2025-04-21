cmake_minimum_required (VERSION 3.11)
 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)
 
# Set project name and language
project(VaultVizier LANGUAGES CXX VERSION 1.0.0)

# Specify the source files
file(GLOB SOURCES
    "src/main.cpp"               # Add main.cpp
    "src/classes/*.cpp"          # Add all .cpp files in the src/classes folder
)

# Specify include directories (where headers are located)
include_directories(src/classes)  # Include 'src/classes' for headers like Patient.hpp

# Create the executable from the source files
add_executable(VaultVizier ${SOURCES})

# Link the FTXUI library to your project
target_link_libraries(VaultVizier
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component  # Include this only if using components
)