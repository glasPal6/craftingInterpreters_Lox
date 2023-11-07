# cmake_minimum_required(VERSION 3.0.0)
# project(slowInterpreter VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()

# add_executable(slowInterpreter main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
cmake_minimum_required(VERSION 3.0.0)
project(slowInterpreter VERSION 0.1.0 LANGUAGES C CXX)

set(
	CMAKE_CXX_STANDARD
	14
)

set (
	CMAKE_BINARY_DIR
	"${CMAKE_SOURCE_DIR}/build"
)

set (
	EXECUTABLE_OUTPUT_PATH
	"${CMAKE_SOURCE_DIR}/bin"
)

add_executable(slowInterpreter 
	lox/Lox.cpp
)
