cmake_minimum_required (VERSION 3.0)
project(pmTracer)

find_package(Threads)

set(SOURCES
	src/Plane.cpp
	src/Sphere.cpp
	src/Rectangle.cpp
	src/World.cpp
	src/RayCast.cpp
	src/Whitted.cpp
	src/AreaLighting.cpp
	src/PathTrace.cpp
	src/Sampler.cpp
	src/Regular.cpp
	src/PureRandom.cpp
	src/Jittered.cpp
	src/MultiJittered.cpp
	src/NRooks.cpp
	src/Hammersley.cpp
	src/Halton.cpp
	src/Camera.cpp
	src/Ortographic.cpp
	src/PinHole.cpp
	src/Matte.cpp
	src/Phong.cpp
	src/Reflective.cpp
	src/Emissive.cpp
	src/AmbientOccluder.cpp
	src/AreaLight.cpp
	src/EnvironmentLight.cpp
)

add_library(pmTracer ${SOURCES})
target_include_directories(pmTracer PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_executable(trace main.cpp)
target_link_libraries (trace pmTracer ${CMAKE_THREAD_LIBS_INIT})
