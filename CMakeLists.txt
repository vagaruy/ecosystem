cmake_minimum_required(VERSION 3.6)

project(ecosystem)

# CMake Modules Paths to use over default CMake Modules
list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/tools
        )

find_package(CURL)
find_package(JsonCpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        private/NaturalLightSimulator.cpp
        private/DarkSkyAPI.cpp
        private/LightningGenerator.cpp)

SET(HEADER_FILES
        public/NaturalLightSimulator.h
        public/DarkSkyAPI.h
        public/LightningGenerator.h)

add_library(${PROJECT_NAME}
        ${SOURCE_FILES}
        ${HEADER_FILES})

target_include_directories(${PROJECT_NAME}
        PUBLIC public
        PRIVATE private
        PUBLIC ${JSONCPP_INCLUDE_DIRS}
        )

target_link_libraries(${PROJECT_NAME}
        ${JSONCPP_LIBRARIES}
        ${CURL_LIBRARIES}
        )

add_executable(weather_test
        test/TestWeatherData.cpp)

target_link_libraries(weather_test
        ecosystem)

add_executable(lightning_random_test
        test/TestRandomLightningGenerator.cpp)

target_link_libraries(lightning_random_test
        ecosystem)