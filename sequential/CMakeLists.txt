cmake_minimum_required(VERSION 2.8)

project(sequential)
find_package( OpenCV REQUIRED )
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_subdirectory(sba-1.6)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/sba-1.6 include)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/sba-1.6 ${LAPACKBLAS_DIR})

add_executable(sequential src/main.cpp)
TARGET_LINK_LIBRARIES(sequential sba -lm ${LAPACK_LIB} ${BLAS_LIB})

install(TARGETS sequential RUNTIME DESTINATION bin)

add_executable(testSynthData test/testSynthData.cpp)
TARGET_LINK_LIBRARIES(testSynthData ${Boost_LIBRARIES})
enable_testing()
add_test(synthdata testSynthData)
