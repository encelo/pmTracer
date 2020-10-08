cmake_minimum_required (VERSION 3.0)
project(pmTracer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(Threads)

include(pmtracer_headers)
include(pmtracer_sources)

add_library(pmTracer ${PMTRACER_HEADERS} ${PMTRACER_SOURCES})
target_include_directories(pmTracer PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_executable(trace main.cpp)
target_link_libraries(trace pmTracer ${CMAKE_THREAD_LIBS_INIT})

target_compile_definitions(pmTracer PRIVATE "$<$<CONFIG:Debug>:PMTRACER_DEBUG>")

if(MSVC)
	target_compile_options(pmTracer PRIVATE $<$<CONFIG:Release>:/fp:fast /Ox /Qpar>)

	if(LINKTIME_OPTIMIZATION)
		target_compile_options(pmTracer PRIVATE $<$<CONFIG:Release>:/GL>)
		target_link_options(pmTracer PRIVATE $<$<CONFIG:Release>:/LTCG>)
	endif()

	if(AUTOVECTORIZATION_REPORT)
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Qvec-report:2 /Qpar-report:2")
	endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_compile_options(pmTracer PRIVATE -fdiagnostics-color=auto)
	target_compile_options(pmTracer PRIVATE -Wall -pedantic -Wextra -Wold-style-cast -Wno-long-long -Wno-unused-parameter -Wno-ignored-qualifiers -Wno-variadic-macros)
	target_compile_options(pmTracer PRIVATE -fvisibility=hidden -fvisibility-inlines-hidden)

	target_compile_options(pmTracer PRIVATE $<$<CONFIG:Release>:-Ofast -funsafe-loop-optimizations -ftree-loop-if-convert-stores>)

	if(LINKTIME_OPTIMIZATION)
		target_compile_options(pmTracer PRIVATE $<$<CONFIG:Release>:-flto=auto>)
		target_link_options(pmTracer PRIVATE $<$<CONFIG:Release>:-flto=auto>)
	endif()

	if(AUTOVECTORIZATION_REPORT)
		target_link_options(pmTracer PRIVATE $<$<CONFIG:Release>:-fopt-info-vec-optimized>)
	endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
	target_compile_options(pmTracer PRIVATE -fcolor-diagnostics)
	target_compile_options(pmTracer PRIVATE -Wall -pedantic -Wextra -Wold-style-cast -Wno-gnu-zero-variadic-macro-arguments -Wno-unused-parameter -Wno-variadic-macros -Wno-c++11-long-long -Wno-missing-braces)
	target_link_options(pmTracer PRIVATE -Wl,--no-undefined)

	target_compile_options(pmTracer PRIVATE $<$<CONFIG:Release>:-Ofast>)

	if(LINKTIME_OPTIMIZATION)
		target_compile_options(pmTracer PRIVATE $<$<CONFIG:Release>:-flto>)
		target_link_options(pmTracer PRIVATE $<$<CONFIG:Release>:-flto>)
	endif()

	if(AUTOVECTORIZATION_REPORT)
		target_compile_options(pmTracer PRIVATE $<$<CONFIG:Release>:-Rpass=loop-vectorize -Rpass-analysis=loop-vectorize>)
	endif()
endif()
