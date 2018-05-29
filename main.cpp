#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>
#include <chrono>
#include <thread>

#include "World.h"
#include "Ortographic.h"
#include "Jittered.h"
#include "MultiJittered.h"
#include "Hammersley.h"
#include "Halton.h"
#include "NRooks.h"
#include "PinHole.h"
#include "Sphere.h"
#include "Plane.h"
#include "Matte.h"
#include "Ambient.h"
#include "PointLight.h"
#include "Phong.h"
#include "Reflective.h"
#include "Directional.h"
#include "AmbientOccluder.h"
#include "AreaLighting.h"
#include "AreaLight.h"
#include "Emissive.h"
#include "Rectangle.h"
#include "PathTrace.h"
#include "EnvironmentLight.h"

#define SINGLE_THREAD (0)
#define SINGLE_THREAD_TILED (0)
#define MULTI_THREAD_TILED (1)

#define AMBIENT (1)
#define AMBIENT_OCCLUSION (0)

#define POINT_LIGHTS (0)
#define AREA_LIGHTS (0)
#define PATH_TRACE (1)

const int width = 1280;
const int height = 720;
const int tileSize = 16;

void threadFunc(int id, int numThreads, pm::World &world, pm::Camera &camera, pm::RGBColor *frame)
{
	bool hasFinished = false;
	int iteration = 0;
	int startY = (id * tileSize) % height;
	int startX = ((id * tileSize) / height) * tileSize;

	while(hasFinished == false)
	{
		camera.renderScene(world, frame, startX, startY, tileSize);
		iteration++;
		const int index = (iteration * numThreads) + id;
		startY = (index * tileSize) % height;
		startX = ((index * tileSize) / height) * tileSize;

		if (startX > width)
			hasFinished = true;
	}
}

void savePbm(const char *filename, pm::RGBColor *frame)
{
	const float invGamma = 1.0f / 2.2f;

	std::ofstream file;
	file.open (filename);
	file << "P3\n" << width << " " << height << "\n" << 255 << "\n";
	for (int i = 0 ; i < height; i++)
	{
		for (int j = 0 ; j < width; j++)
		{
			const pm::RGBColor &pixel = frame[i * width + j];

			// Tonemapping
			pm::RGBColor tonemapped = pixel * 16.0f;
			tonemapped = tonemapped / (pm::RGBColor(1.0f, 1.0f, 1.0f) + tonemapped);
			tonemapped.pow(invGamma);

			file << unsigned(tonemapped.r * 255) << " ";
			file << unsigned(tonemapped.g * 255) << " ";
			file << unsigned(tonemapped.b * 255) << " ";
		}
		file << "\n";
	}
	file.close();
}

std::unique_ptr<pm::Rectangle> rectangleFromVertices(const pm::Vector3 pA, const pm::Vector3 pB, const pm::Vector3 pC)
{
	auto rect = std::make_unique<pm::Rectangle>(pA, pB - pA, pC - pA, cross(pB - pA, pC - pA).normalize());
	return rect;
}

void setupWorld(pm::World &world)
{
	//world.setTracer(std::make_unique<pm::AreaLighting>(world));
	world.setTracer(std::make_unique<pm::PathTrace>(world));

	auto vpSampler = world.createSampler<pm::NRooks>(256);

	world.viewPlane().setDimensions(width, height);
	world.viewPlane().setSampler(vpSampler);
	world.viewPlane().setMaxDepth(5);

	auto hammersley = world.createSampler<pm::Hammersley>(256);

#if AMBIENT
	auto ambient = std::make_unique<pm::Ambient>();
	ambient->setRadianceScale(0.01f);
	world.setAmbientLight(std::move(ambient));
#elif AMBIENT_OCCLUSION
	auto ambient = std::make_unique<pm::AmbientOccluder>();
	ambient->setRadianceScale(0.01f);
	ambient->setColor(0.25f, 0.25f, 0.25f);
	ambient->setMinAmount(0.0f);
	ambient->setSampler(std::make_unique<pm::MultiJittered>(64));
	world.setAmbientLight(std::move(ambient));
#endif

	auto plane = std::make_unique<pm::Plane>(pm::Vector3(0.0, 0.0, 0.0), pm::Vector3(0.0, 1.0, 0.0));
	auto white = std::make_unique<pm::Phong>();
	white->setCd(1.0f, 1.0f, 1.0f);
	white->setKa(0.25f);
	white->setKd(0.45f);
	//white->setKs(0.25f);
	//white->setSpecularExp(32.0f);
	white->diffuse().setSampler(hammersley);
	plane->setMaterial(white.get());
	world.addObject(std::move(plane));
	world.addMaterial(std::move(white));

	auto sphere1 = std::make_unique<pm::Sphere>(pm::Vector3(0.0, 1.0, 0.0), 1.0);
	auto red = std::make_unique<pm::Phong>();
	red->setCd(1.0f, 0.0f, 0.0f);
	red->setKa(0.25f);
	red->setKd(0.65f);
	red->setKs(0.15f);
	red->setSpecularExp(32.0f);
	red->diffuse().setSampler(hammersley);
	sphere1->setMaterial(red.get());
	world.addObject(std::move(sphere1));
	world.addMaterial(std::move(red));

	auto sphere2 = std::make_unique<pm::Sphere>(pm::Vector3(2.0, 0.5, 0.0), 0.5);
	auto green = std::make_unique<pm::Phong>();
	green->setCd(0.0f, 1.0f, 0.0f);
	green->setKa(0.1f);
	green->setKd(0.45f);
	green->setKs(0.5f);
	green->setSpecularExp(32.0f);
	green->diffuse().setSampler(hammersley);
	sphere2->setMaterial(green.get());
	world.addObject(std::move(sphere2));
	world.addMaterial(std::move(green));

	auto sphere3 = std::make_unique<pm::Sphere>(pm::Vector3(-2.0, 2.0, 0.0), 0.75);
	auto blue = std::make_unique<pm::Phong>();
	blue->setCd(0.0f, 0.0f, 1.0f);
	blue->setKa(0.1f);
	blue->setKd(0.75f);
	blue->setKs(0.25f);
	blue->setSpecularExp(24.0f);
	blue->diffuse().setSampler(hammersley);
	sphere3->setMaterial(blue.get());
	world.addObject(std::move(sphere3));
	world.addMaterial(std::move(blue));

#if POINT_LIGHTS
	auto light1 = std::make_unique<pm::PointLight>(0.0, 2.0, -2.0);
	//light1->setColor(1.0f, 0.0f, 1.0f);
	light1->setRadianceScale(0.1f);
	world.addLight(std::move(light1));

	auto light2 = std::make_unique<pm::PointLight>(3.0, 3.0, -2.0);
	light2->setRadianceScale(0.1f);
	//light2->setCastShadows(false);
	//world.addLight(std::move(light2));

	auto light3 = std::make_unique<pm::PointLight>(-3.0, 3.0, -2.0);
	light3->setRadianceScale(0.1f);
	//light3->setColor(0.5f, 1.0f, 0.33f);
	//light3->setCastShadows(false);
	//world.addLight(std::move(light3));

	auto light4 = std::make_unique<pm::Directional>(-1.0, 1.0, 0.0);
	light4->setRadianceScale(0.0001f);
	light4->setColor(0.5f, 1.0f, 0.33f);
	//light4->setCastShadows(false);
	//world.addLight(std::move(light4));
#elif AREA_LIGHTS
	auto light1 = std::make_unique<pm::AreaLight>();
	auto object = std::make_unique<pm::Rectangle>(pm::Vector3(-1, 3.0, -1), pm::Vector3(2.0, 0.0, 0.0), pm::Vector3(0.0, 0.0, 2.0), pm::Vector3(0.0, -1.0, 0.0));
	object->setSampler(std::make_unique<pm::Hammersley>(64));
	light1->setObject(std::move(object));
	auto emissive = std::make_unique<pm::Emissive>();
	emissive->setRadianceScale(0.25f);
	//emissive->setCe(1.0f, 0.0f, 0.0f);
	light1->setMaterial(std::move(emissive));
	world.addLight(std::move(light1));
/*
	auto objectW = std::make_unique<pm::Rectangle>(pm::Vector3(-1, 3.0, -1), pm::Vector3(2.0, 0.0, 0.0), pm::Vector3(0.0, 0.0, 2.0), pm::Vector3(0.0, -1.0, 0.0));
	auto mat = std::make_unique<pm::Matte>();
	objectW->setMaterial(std::move(mat));
	objectW->setCastShadows(false);
	world.addObject(std::move(objectW));
*/
	auto light2 = std::make_unique<pm::AreaLight>();
	auto object2 = std::make_unique<pm::Rectangle>(pm::Vector3(-4, 0.0, 0.5), pm::Vector3(0.0, 1.0, 0.0), pm::Vector3(0.0, 0.0, 1.0), pm::Vector3(1.0, 0.0, 0.0));
	object2->setSampler(std::make_unique<pm::Hammersley>(64));
	light2->setObject(std::move(object2));
	auto emissive2 = std::make_unique<pm::Emissive>();
	emissive2->setRadianceScale(0.2f);
	//emissive2->setCe(1.0f, 0.0f, 0.0f);
	light2->setMaterial(std::move(emissive2));
	world.addLight(std::move(light2));
/*
	auto objectW2 = std::make_unique<pm::Rectangle>(pm::Vector3(-4, 0.0, 0.5), pm::Vector3(0.0, 1.0, 0.0), pm::Vector3(0.0, 0.0, 1.0), pm::Vector3(1.0, 0.0, 0.0));
	auto mat2 = std::make_unique<pm::Matte>();
	objectW2->setMaterial(std::move(mat2));
	objectW2->setCastShadows(false);
	world.addObject(std::move(objectW2));
*/
	auto envlight = std::make_unique<pm::EnvironmentLight>();
	auto envEmissive = std::make_unique<pm::Emissive>();
	envEmissive->setRadianceScale(0.1f);
	envEmissive->setCe(1.0f, 1.0f, 0.6f);
	envlight->setMaterial(std::move(envEmissive));
	world.addLight(std::move(envlight));
#elif PATH_TRACE
	auto object = std::make_unique<pm::Rectangle>(pm::Vector3(-1, 3.0, -1), pm::Vector3(2.0, 0.0, 0.0), pm::Vector3(0.0, 0.0, 2.0), pm::Vector3(0.0, -1.0, 0.0));
	object->setSampler(hammersley);
	auto emissive = std::make_unique<pm::Emissive>();
	emissive->setRadianceScale(0.25f);
	//emissive->setCe(1.0f, 0.0f, 0.0f);
	object->setMaterial(emissive.get());
	world.addObject(std::move(object));
	world.addMaterial(std::move(emissive));

	auto object2 = std::make_unique<pm::Rectangle>(pm::Vector3(-4, 0.0, 0.5), pm::Vector3(0.0, 1.0, 0.0), pm::Vector3(0.0, 0.0, 1.0), pm::Vector3(1.0, 0.0, 0.0));
	object2->setSampler(hammersley);
	auto emissive2 = std::make_unique<pm::Emissive>();
	emissive2->setRadianceScale(0.2f);
	//emissive2->setCe(1.0f, 0.0f, 0.0f);
	object2->setMaterial(emissive2.get());
	world.addObject(std::move(object2));
	world.addMaterial(std::move(emissive2));
#endif
}

void setupCornellBox(pm::World &world)
{
	world.setTracer(std::make_unique<pm::PathTrace>(world));

	auto vpSampler = world.createSampler<pm::NRooks>(16);

	world.viewPlane().setDimensions(width, height);
	world.viewPlane().setSampler(vpSampler);
	world.viewPlane().setMaxDepth(5);

	auto hammersley = world.createSampler<pm::Hammersley>(256);

	// Materials
	auto white = world.createMaterial<pm::Matte>();
	white->setCd(1.0f, 1.0f, 1.0f);
	white->diffuse().setSampler(hammersley);

	auto red = world.createMaterial<pm::Matte>();
	red->setCd(1.0f, 0.0f, 0.0f);
	red->diffuse().setSampler(hammersley);

	auto green = world.createMaterial<pm::Matte>();
	green->setCd(0.0f, 1.0f, 0.0f);
	green->diffuse().setSampler(hammersley);

	auto emissive = world.createMaterial<pm::Emissive>();

	// Light
	auto light = world.createObject<pm::Rectangle>(pm::Vector3(213.0, 548.0, 227.0), pm::Vector3(343.0-213.0, 0.0, 0.0), pm::Vector3(0.0, 0.0, 332.0-227.0), pm::Vector3(0.0, -1.0, 0.0));
	light->setSampler(hammersley);
	light->setMaterial(emissive);

	// Walls
	auto floor = world.createObject<pm::Rectangle>(pm::Vector3(0.0, 0.0, 0.0), pm::Vector3(552.8, 0.0, 0.0), pm::Vector3(0.0, 0.0, 559.2), pm::Vector3(0.0, 1.0, 0.0));
	floor->setMaterial(white);

	auto ceiling = world.createObject<pm::Rectangle>(pm::Vector3(0.0, 548.8, 0.0), pm::Vector3(556.0, 0.0, 0.0), pm::Vector3(0.0, 0.0, 559.2), pm::Vector3(0.0, -1.0, 0.0));
	ceiling->setMaterial(white);

	auto leftWall = world.createObject<pm::Rectangle>(pm::Vector3(552.8, 0.0, 0.0), pm::Vector3(0.0, 548.8, 0.0), pm::Vector3(0.0, 0.0, 559.2), pm::Vector3(-1.0, 0.0, 0.0));
	leftWall->setMaterial(red);

	auto rightWall = world.createObject<pm::Rectangle>(pm::Vector3(0.0, 0.0, 0.0), pm::Vector3(0.0, 548.8, 0.0), pm::Vector3(0.0, 0.0, 559.2), pm::Vector3(1.0, 0.0, 0.0));
	rightWall->setMaterial(green);

	auto backWall = world.createObject<pm::Rectangle>(pm::Vector3(0.0, 0.0, 559.2), pm::Vector3(0.0, 548.8, 0.0), pm::Vector3(556.0, 0.0, 0.0), pm::Vector3(0.0, 0.0, -1.0));
	backWall->setMaterial(white);

	// Short object
	auto short1 = rectangleFromVertices(pm::Vector3(130.0, 165.0, 65.0), pm::Vector3(82.0, 165.0, 225.0), pm::Vector3(290.0, 165.0, 114.0));
	short1->setMaterial(white);
	world.addObject(std::move(short1));

	auto short2 = rectangleFromVertices(pm::Vector3(290.0, 0.0, 114.0), pm::Vector3(290.0, 165.0, 114.0), pm::Vector3(240.0, 0.0, 272.0));
	short2->setMaterial(white);
	world.addObject(std::move(short2));

	auto short3 = rectangleFromVertices(pm::Vector3(130, 0.0, 65.0), pm::Vector3(130.0, 165.0, 65.0), pm::Vector3(290.0, 0.0, 114.0));
	short3->setMaterial(white);
	world.addObject(std::move(short3));

	auto short4 = rectangleFromVertices(pm::Vector3(82.0, 0.0, 225.0), pm::Vector3(82.0, 165.0, 225.0), pm::Vector3(130.0, 0.0, 65.0));
	short4->setMaterial(white);
	world.addObject(std::move(short4));

	auto short5 = rectangleFromVertices(pm::Vector3(240.0, 0.0, 272.0), pm::Vector3(240.0, 165.0, 272.0), pm::Vector3(82.0, 0.0, 225.0));
	short5->setMaterial(white);
	world.addObject(std::move(short5));

	// Tall object
	auto tall1 = rectangleFromVertices(pm::Vector3(423.0, 330.0, 247.0), pm::Vector3(265.0, 330.0, 296.0), pm::Vector3(472.0, 330.0, 406.0));
	tall1->setMaterial(white);
	world.addObject(std::move(tall1));

	auto tall2 = rectangleFromVertices(pm::Vector3(423.0, 0.0, 247.0), pm::Vector3(423.0, 330.0, 247.0), pm::Vector3(472.0, 0.0, 406.0));
	tall2->setMaterial(white);
	world.addObject(std::move(tall2));

	auto tall3 = rectangleFromVertices(pm::Vector3(472.0, 0.0, 406.0), pm::Vector3(472.0, 330.0, 406.0), pm::Vector3(314.0, 0.0, 456.0));
	tall3->setMaterial(white);
	world.addObject(std::move(tall3));

	auto tall4 = rectangleFromVertices(pm::Vector3(314.0, 0.0, 456.0), pm::Vector3(314.0, 330.0, 456.0), pm::Vector3(265.0, 0.0, 296.0));
	tall4->setMaterial(white);
	world.addObject(std::move(tall4));

	auto tall5 = rectangleFromVertices(pm::Vector3(265.0, 0.0, 296.0), pm::Vector3(265.0, 330.0, 296.0), pm::Vector3(423.0, 0.0, 247.0));
	tall5->setMaterial(white);
	world.addObject(std::move(tall5));
}

void validateWorld(const pm::World world)
{
	if (world.viewPlane().samplerState().sampler() == nullptr)
	{
		std::cout << "Missing viewplane sampler!\n";
		exit(-1);
	}

	for (const auto &object : world.objects())
	{
		if (object->material() == nullptr)
		{
			std::cout << "Missing material!\n";
			exit(-1);
		}
	}
}

int main()
{
	std::cout << "Setting up the scene...\n" << std::flush;
	auto startTime = std::chrono::high_resolution_clock::now();

	std::unique_ptr<pm::RGBColor []> frame = std::make_unique<pm::RGBColor []>(width * height);

	pm::World world;
	//setupWorld(world);

	setupCornellBox(world);
	world.viewPlane().setPixelSize(0.004f);

	pm::PinHole camera;
	camera.setEye(278.0, 273.0, -800);
	camera.setUp(0, -1, 0);
	camera.setLookAt(278.0, 273.0, 0);
	camera.setViewDistance(4.0f);
	camera.computeUvw();

/*
	//pm::Ortographic camera;
	world.viewPlane().setPixelSize(0.005f);

	pm::PinHole camera;
	camera.setEye(0, 1.0, -5);
	camera.setUp(0, -1, 0);
	camera.setLookAt(0, 1, 0);
	camera.setViewDistance(4.0f);
	camera.computeUvw();
	camera.setExposureTime(1.0f);
*/

	const unsigned int numThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	threads.reserve(numThreads);

	auto endTime = std::chrono::high_resolution_clock::now();
	std::cout << "Scene setting time: ";
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms\n" << std::flush;;

	std::cout << "Rendering started...\n" << std::flush;;
	startTime = std::chrono::high_resolution_clock::now();

#if SINGLE_THREAD
	camera.renderScene(world, frame.get());
#elif SINGLE_THREAD_TILED
	for (int i = 0; i < height; i += tileSize)
		for (int j = 0 ; j < width; j += tileSize)
			camera.renderScene(world, frame.get(), j, i, tileSize);
#elif MULTI_THREAD_TILED
	for (int i = 0; i < numThreads; i++)
		threads.emplace_back(threadFunc, i, numThreads, std::ref(world), std::ref(camera), frame.get());
	for (int i = 0; i < numThreads; i++)
		threads[i].join();
#endif

	endTime = std::chrono::high_resolution_clock::now();
	std::cout << "Rendering time: ";
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms\n" << std::flush;;

	// Save output to PBM ascii format
	startTime = std::chrono::high_resolution_clock::now();
	savePbm("image.pbm", frame.get());
	endTime = std::chrono::high_resolution_clock::now();
	std::cout << "File save time: ";
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms\n" << std::flush;;

	return EXIT_SUCCESS;
}
