# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)
set(EXTRA_COMPONENT_DIRS C:/Users/chris/esp/esp-idf-lib/components/ $ENV{SYSPROGS_COMPONENTS_DIR})
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(VE4TLA-Amp-Controller)