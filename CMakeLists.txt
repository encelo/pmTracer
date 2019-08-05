cmake_minimum_required (VERSION 3.0)
project(pmTracer)

find_package(Threads)

set(HEADERS
	include/Ray.h
	include/Random.h
	include/Vector2.h
	include/Vector3.h
	include/RGBColor.h
	include/Geometry.h
	include/Plane.h
	include/Sphere.h
	include/Rectangle.h
	include/World.h
	include/Tracer.h
	include/RayCast.h
	include/Whitted.h
	include/AreaLighting.h
	include/PathTrace.h
	include/GlobalTrace.h
	include/Sampler.h
	include/SamplerState.h
	include/Regular.h
	include/PureRandom.h
	include/Jittered.h
	include/MultiJittered.h
	include/NRooks.h
	include/Hammersley.h
	include/Halton.h
	include/ViewPlane.h
	include/Camera.h
	include/Ortographic.h
	include/PinHole.h
	include/ShadeRecord.h
	include/Material.h
	include/BRDF.h
	include/Matte.h
	include/Phong.h
	include/Lambertian.h
	include/Reflective.h
	include/PerfectSpecular.h
	include/GlossySpecular.h
	include/Emissive.h
	include/AmbientOccluder.h
	include/Light.h
	include/Directional.h
	include/PointLight.h
	include/Ambient.h
	include/AreaLight.h
	include/EnvironmentLight.h
)

set(SOURCES
	src/Random.cpp
	src/Plane.cpp
	src/Sphere.cpp
	src/Rectangle.cpp
	src/World.cpp
	src/RayCast.cpp
	src/Whitted.cpp
	src/AreaLighting.cpp
	src/PathTrace.cpp
	src/GlobalTrace.cpp
	src/Sampler.cpp
	src/SamplerState.cpp
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
	src/BRDF.cpp
	src/Matte.cpp
	src/Phong.cpp
	src/Reflective.cpp
	src/Emissive.cpp
	src/AmbientOccluder.cpp
	src/AreaLight.cpp
	src/EnvironmentLight.cpp
)

add_library(pmTracer ${HEADERS} ${SOURCES})
target_include_directories(pmTracer PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_executable(trace main.cpp)
target_link_libraries (trace pmTracer ${CMAKE_THREAD_LIBS_INIT})

if(CMAKE_BUILD_TYPE MATCHES "Release")
	if(MSVC)
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox /Qpar")
		#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Qvec-report:2 /Qpar-report:2")
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -funsafe-loop-optimizations -ftree-loop-if-convert-stores")
		#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fopt-info-vec-optimized")
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -fslp-vectorize-aggressive")
		#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize")
	endif()
endif()
