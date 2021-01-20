
#include <core/image.h>
#include <core/color.h>
#include <core/random.h>

#include <rt/world.h>   
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/integrators/recraytrace.h>

#include <rt/groups/simplegroup.h>
#include <rt/groups/bvh.h>

#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/solids/triangle.h>
#include <rt/solids/environment.h>

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/textures/perlin.h>

#include <rt/materials/flatmaterial.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/glass.h>
#include <rt/materials/phong.h>
#include <rt/materials/combine.h>
#include <rt/materials/cooktorrance.h>
#include <rt/materials/mirror.h>

#include <rt/lights/arealight.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>

#include <rt/coordmappers/environment.h>

#include <algorithm>

using namespace rt;


MatLib* getTableMatlib() {
    // https://sketchfab.com/3d-models/japanese-house-20-5ae0121e33b54b7789c6b9113da444bf
    MatLib* matlib = new MatLib;    
    Texture* black1 = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* box4 = new ImageTexture("models/table_top.png");
    ImageTexture* box5 = new ImageTexture("models/table_bot.png");
    Texture* light = new ConstantTexture(RGBColor(0.6f, 0.6f, 0.9f) * 0.6);
    matlib->insert(std::pair<std::string, Material*>("Bot", new CookTorranceMaterial(box5, 0.1, 0.8, 0.2,0.3)));
    matlib->insert(std::pair<std::string, Material*>("Top", new CookTorranceMaterial(box4, 0.6, 0.4, 0.2,0.3) ));
   
    return matlib;
}
MatLib* getTeapotMatlib() {
    MatLib* matlib = new MatLib;
    Texture* black1 = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* box4 = new ImageTexture("models/default.png");
    ImageTexture* box5 = new ImageTexture("models/default.png");
    Texture* light = new ConstantTexture(RGBColor(0.6f, 0.6f, 0.9f) * 0.6);


    matlib->insert(std::pair<std::string, Material*>("Default", new CookTorranceMaterial(box5, 0.1, 0.8, 0.2,0.3)));

    matlib->insert(std::pair<std::string, Material*>("default", new CookTorranceMaterial(box5, 0.1, 0.8, 0.2,0.3)));
   
    return matlib;
}
void a_scene() {
        Image img(200,140);

    std::cout << "Resolution is " << img.width() << ", " << img.height() << std::endl;
    World world;
    // SimpleGroup* scene = new SimpleGroup();
    BVH* scene = new BVH();
    world.scene = scene;
  

    // Main Camera
    PerspectiveCamera* cam = new PerspectiveCamera(Point(-0.48f, 2.04f, -0.36f), Vector(0.605, -1.6, 1.27), Vector(-0.004, 0.62, 0.78), pi/2, pi/4);
    

    RGBColor yellow_clr =  RGBColor(0.467f, 0.14f, 0.09f);
    RGBColor blue_clr = RGBColor(0.035f, 0.252f, 1.0f);
    RGBColor red_clr = RGBColor(1.0f, 0.02f, 0.02f);
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.1f));
    Texture* greytex = new ConstantTexture(RGBColor::rep(0.2f));
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));

    MatLib* matlib_table = getTableMatlib();
    loadOBJ(scene, "models/", "Wooden_Table.obj", matlib_table);
    MatLib* matlib_pot = getTeapotMatlib();
    loadOBJ(scene,"models/","teapot.obj",matlib_pot);

    //env mapper
    world.envSolid = new Environment(new EnvironmentMapper(), new FlatMaterial(new ConstantTexture(blue_clr)));
    

    //lighting
    world.light.push_back(new PointLight(Point(-0.35f, 2.18f, 2.6f), RGBColor(1, 1, 1))); // BL1 yellow
    world.light.push_back(new PointLight(Point(0.35f, 0.18f, 0.6f), yellow_clr * 0.25)); // BL1 yellow
    world.light.push_back(new DirectionalLight(Vector(0.2f ,-0.5f , 1.0f).normalize(), RGBColor(1.0f, 1.0f, 1.0f) * 0.15f)); // white
    world.light.push_back(new DirectionalLight(Vector(-0.2f ,-0.5f , 1.0f).normalize(), yellow_clr * 1.f)); // yellow

    RecursiveRayTracingIntegrator integrator(&world);
    scene->rebuildIndex();

    Renderer engine(cam, &integrator);
    // engine.setSamples(25);
    engine.render(img);
    img.writePNG("scene.png");
}