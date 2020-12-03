#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/solids/sphere.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>
#include <rt/groups/simplegroup.h>
// #include <chrono> 

using namespace std::chrono; 

using namespace rt;

void a_indexing() {
    Image img(800, 600);

    BVH* scene = new BVH();
    scene->add(new Sphere(Point(2.5f,  .5f,  -1), 0.5  , nullptr, nullptr));
    scene->add(new Sphere(Point(2.5f,  -1.f,  -1), 0.5, nullptr, nullptr));
    scene->add(new Sphere(Point(4.5f,  .5f,  -1), 0.5 , nullptr, nullptr));

    loadOBJ(scene, "models/", "cow.obj");
    // loadOBJ(scene, "models/", "bunny.obj");
    // loadOBJ(scene, "models/", "dragon.obj");
  
    // auto start = high_resolution_clock::now(); 

	scene->rebuildIndex();
    World world;
    world.scene = scene;
    RayCastingIntegrator integrator(&world);

    PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f), Vector(1.0f,1.0f,-0.6f), Vector(0, 0, 1), pi/8, pi/6);
    PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f)-Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi/8, pi/6);

    Renderer engine1(&cam1, &integrator);
    engine1.render(img);
    img.writePNG("a3-1.png");

    Renderer engine2(&cam2, &integrator);
    engine2.render(img);
    img.writePNG("a3-2.png");

    //bunny
    // PerspectiveCamera cam2(Point(-0.15f, 0.83f, 6.1f), Point(-0.15f, 0.83f, 0.07f)-Point(-0.15f, 0.83f, 6.1f), Vector(0, 1, 0), pi/8, pi/6);
    // Renderer engine2(&cam2, &integrator);
    // engine2.render(img);
    // img.writePNG("a3-bunny.png");

    //dragon
    // PerspectiveCamera cam2(Point(-2.5f, 0.06f, 0.03f), Point(-0.02f, 0.06f, 0.03f)-Point(-2.5f, 0.06f, 0.03f), Vector(0, 1, 0), pi/8, pi/6);
    // Renderer engine2(&cam2, &integrator);
    // engine2.render(img);
    // img.writePNG("a3-dragon.png");


    // auto stop = high_resolution_clock::now(); 
    // auto duration = duration_cast<milliseconds>(stop - start); 

    // std::cout << duration.count() << std::endl; 
}