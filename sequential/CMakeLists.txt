cmake_minimum_required(VERSION 2.8)

project(sequential)
find_package( OpenCV REQUIRED )

add_subdirectory(sba-1.6)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/sba-1.6)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/sba-1.6 ${LAPACKBLAS_DIR})

add_executable(sequential main.cpp costframe.cpp cameraparameters.h)
TARGET_LINK_LIBRARIES(sequential sba -lm ${LAPACK_LIB} ${BLAS_LIB})

install(TARGETS sequential RUNTIME DESTINATION bin)
