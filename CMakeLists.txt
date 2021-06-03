# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)
set(EXTRA_COMPONENT_DIRS ../esp-idf-lib/components/esp_idf_lib_helpers ../esp-idf-lib/components/onewire ../esp-idf-lib/components/ds18x20 ../esp-idf-lib/components/i2cdev ../esp-idf-lib/components/pcf8574 ../esp-idf-lib/components/hd44780 $ENV{SYSPROGS_COMPONENTS_DIR})
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(VE4TLA-Amp-Controller)
