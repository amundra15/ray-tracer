
#include <utility>
#include <map> 
#include <string>

#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>

#include <rt/world.h>
#include <rt/loaders/obj.h>
#include <rt/renderer.h>
#include <rt/integrators/recraytrace.h>

#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>

#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/arealight.h>

#include <rt/textures/constant.h>
#include <rt/textures/texture.h>
#include <rt/textures/imagetex.h>

#include <rt/materials/lambertian.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/glass.h>
#include <rt/materials/combine.h>
#include <rt/materials/dummy.h>

#include <rt/groups/simplegroup.h>
#include <rt/groups/bvh.h>


using namespace rt;


void renderScene(const char* filename)
{
    Image img(100, 100);        
    SimpleGroup* scene = new SimpleGroup();
    

    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    // Material* grey = new LambertianMaterial(blacktex, whitetex);
    Material* grey = new DummyMaterial();
    
    typedef std::map<std::string, Material*> MatLib;
    MatLib matlib;
    matlib.insert(std::make_pair("Cup", grey));
    matlib.insert(std::make_pair("Lid", grey));
    matlib.insert(std::make_pair("Sleeve", grey));


    // loadOBJ(scene, "models/scene1/", "teapot.obj");
    loadOBJ(scene, "models/coffeecup/", "coffeecup.obj");

    World world;
    world.scene = scene;
    
    world.light.push_back(new PointLight(Point(0.0f, 2.43f, 22.69f),RGBColor(800.0f,0,0)));
    
    // PerspectiveCamera* cam = new PerspectiveCamera(Point(-0.15f, 0.83f, 40.93f), Point(-0.15f, 0.83f, 0.07f)-Point(-0.15f, 0.83f, 40.93f), Vector(0, 1, 0), pi/8, pi/6);
    PerspectiveCamera* cam = new PerspectiveCamera(Point(0.0f, 2.43f, 22.69f), Point(0.0f, 2.43f, 0.0f)-Point(0.0f, 2.43f, 22.69f), Vector(0, 1, 0), pi/8, pi/6);
    
    RecursiveRayTracingIntegrator integrator(&world);
    Renderer engine(cam, &integrator);
    // if (numSamples>1)
    //     engine.setSamples(numSamples);
    std::cout << "HERE: 3" << std::endl;
    engine.render(img);
    img.writePNG(filename);

}



void a_renderingcompetition()
{
    renderScene("scene.png");
}