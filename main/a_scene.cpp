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
#include <rt/solids/disc.h>

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
   ImageTexture* box5 = new ImageTexture("models/dmr.png");
       ImageTexture* whitetex = new ImageTexture("models/kettle_texture.png");
           ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
               //LambertianMaterial white(blacktex, whitetex);

    //Texture*   whitetex = new ConstantTexture(RGBColor::rep(1.0f));

    Texture* light = new ConstantTexture(RGBColor(0.6f, 0.6f, 0.9f) * 0.6);
    LambertianMaterial* mat = new LambertianMaterial(blacktex,whitetex);
      CombineMaterial* combined = new CombineMaterial();
    combined->add(new LambertianMaterial(blacktex, whitetex), 0.5f);
    //combined->add( new PhongMaterial(box5, 100.0f),0.5f);
    matlib->insert(std::pair<std::string, Material*>("DefaultMaterial", mat));

    //matlib->insert(std::pair<std::string, Material*>("default", combined));
   
    return matlib;
}
MatLib* getFloorMatlib() {
    MatLib* matlib = new MatLib;
    ImageTexture* box6 = new ImageTexture("models/wood.png");
     MirrorMaterial* mirror = new MirrorMaterial(0.0f, 0.0f);
     Texture*    whitetex = new ConstantTexture(RGBColor::rep(1.0f));

    PhongMaterial* phong = new PhongMaterial(whitetex, 10.0f);
    CombineMaterial* combined = new CombineMaterial();
        Texture* greytex2 = new ConstantTexture(RGBColor::rep(0.7f));
            Material* grey_cook_rain = new CookTorranceMaterial(box6, 0.2f, 0.8f, 0.3f,0.3f);

    combined->add(mirror,0.18f);
    combined->add(phong,0.62f);

    combined->add(grey_cook_rain,0.42f);
    matlib->insert(std::pair<std::string, Material*>("lambert1",combined));

    return matlib;
}
MatLib* getWallMatlib() {
    MatLib* matlib = new MatLib;
    ImageTexture* box6 = new ImageTexture("models/wood.png");
     MirrorMaterial* mirror = new MirrorMaterial(0.0f, 0.0f);
     Texture*    whitetex = new ConstantTexture(RGBColor::rep(1.0f));

    PhongMaterial* phong = new PhongMaterial(whitetex, 10.0f);
    CombineMaterial* combined = new CombineMaterial();
        Texture* greytex2 = new ConstantTexture(RGBColor::rep(0.7f));
            Material* grey_cook_rain = new CookTorranceMaterial(box6, 0.2f, 0.8f, 0.3f,0.3f);

    combined->add(mirror,0.18f);
    combined->add(phong,0.62f);

    combined->add(grey_cook_rain,0.42f);
    matlib->insert(std::pair<std::string, Material*>("lambert1", new CookTorranceMaterial(box6, 0.1, 0.8, 0.2,0.3)));

    return matlib;
}
MatLib* getFrameMatlib() {
    MatLib* matlib = new MatLib;
       Texture* dirt = new ConstantTexture(RGBColor::rep(0.25f));

    matlib->insert(std::pair<std::string, Material*>("Black",new CookTorranceMaterial(dirt, 0.1, 0.8, 0.2,0.3)));
    matlib->insert(std::pair<std::string, Material*>("Blue",new CookTorranceMaterial(dirt, 0.1, 0.8, 0.2,0.3)));
    matlib->insert(std::pair<std::string, Material*>("Cuadro",new CookTorranceMaterial(dirt, 0.1, 0.8, 0.2,0.3)));
    matlib->insert(std::pair<std::string, Material*>("Cuadro.001",new CookTorranceMaterial(dirt, 0.1, 0.8, 0.2,0.3)));
    matlib->insert(std::pair<std::string, Material*>("L.Blue",new CookTorranceMaterial(dirt, 0.1, 0.8, 0.2,0.3)));
    matlib->insert(std::pair<std::string, Material*>("Red",new CookTorranceMaterial(dirt, 0.1, 0.8, 0.2,0.3)));
    matlib->insert(std::pair<std::string, Material*>("White",new CookTorranceMaterial(dirt, 0.1, 0.8, 0.2,0.3)));
    matlib->insert(std::pair<std::string, Material*>("Yellow",new CookTorranceMaterial(dirt, 0.1, 0.8, 0.2,0.3)));
    
    return matlib;
}
MatLib* getBreadMatlib() {
    MatLib* matlib = new MatLib;
       ImageTexture* whitetex = new ImageTexture("models/Bread.png");
           ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
     
    LambertianMaterial* mat = new LambertianMaterial(blacktex,whitetex);
    matlib->insert(std::pair<std::string, Material*>("Material.002", mat));

    //matlib->insert(std::pair<std::string, Material*>("default", combined));
   
   
    return matlib;
}
MatLib* getPlateMatlib() {
    MatLib* matlib = new MatLib;
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    CombineMaterial* combined = new CombineMaterial();
    combined->add(new LambertianMaterial(whitetex, whitetex), 0.5f);
    combined->add( new PhongMaterial(whitetex, 100.0f),0.5f);
    matlib->insert(std::pair<std::string, Material*>("Mat", combined));

    //matlib->insert(std::pair<std::string, Material*>("default", combined));
   
   
    return matlib;
}


MatLib* getWineBottleMatlib() {
    MatLib* matlib = new MatLib;

    //combined material
    // PhongMaterial* phong = new PhongMaterial(new ConstantTexture(RGBColor::rep(0.35f)), 31.999996f);  //Ks, Ns
    // LambertianMaterial* lambertian = new LambertianMaterial(new ConstantTexture(RGBColor::rep(0.0f)), new ConstantTexture(RGBColor(0.8824, 0.3451, 0.7804)));   //Ka, Kd
    // GlassMaterial* glass = new GlassMaterial(1.45f);

    // CombineMaterial* combine = new CombineMaterial();
    // combine->add(phong,0.25f);
    // combine->add(lambertian,0.25f);
    // combine->add(glass,0.5f);

    // matlib->insert(std::pair<std::string, Material*>("wire_225088199",combine));
    matlib->insert(std::pair<std::string, Material*>("wire_225088199", new GlassMaterial(1.45f)));
    return matlib;
}

MatLib* getGlassCups() {
    MatLib* matlib = new MatLib;

    matlib->insert(std::pair<std::string, Material*>("glass", new GlassMaterial(1.45f)));
    matlib->insert(std::pair<std::string, Material*>("glass.001", new GlassMaterial(1.45f)));
    matlib->insert(std::pair<std::string, Material*>("water-air", new GlassMaterial(0.75f)));
    matlib->insert(std::pair<std::string, Material*>("water-glass", new GlassMaterial(1.09f)));
    return matlib;
}


void a_scene() {
    
    // Image img(128,128);
    Image img(256,256);
    // Image img(512,512);

    std::cout << "Resolution is " << img.width() << ", " << img.height() << std::endl;
    World world;
    BVH* scene = new BVH();
    world.scene = scene;
  
    //decreasing y takes it lower
    //decreasing x takes things towards right side of the scene
    //decreasing z takes it away from the back wall

    // Main Camera
    // PerspectiveCamera* cam = new PerspectiveCamera(Point(-0.821, 0.489f, 0.544f), Vector(-0.82+0.861, 0.5043-0.509, 0.54-0.504), Vector(-0.026, 0.997714, 0.062), pi/6, pi/6);
    DOFPerspectiveCamera* cam = new DOFPerspectiveCamera(Point(-0.821, 0.489f, 0.544f), Vector(-0.82+0.861, 0.5043-0.509, 0.54-0.504), Vector(-0.026, 0.997714, 0.062), pi/6, pi/6, 0.725f, 0.006f);  

    // ImageTexture* stonetex = new ImageTexture("models/stones_diffuse.png");
    // ConstantTexture* redtex = new ConstantTexture(RGBColor(.7f,0.f,0.f));
    // ConstantTexture* greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ConstantTexture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    LambertianMaterial white(blacktex, whitetex);

    MatLib* matlib_table = getTableMatlib();
    loadOBJ(scene, "models/", "Wooden_Table.obj", matlib_table);
    MatLib* matlib_pot = getTeapotMatlib();
    // MatLib* bottle = getWineBottleMatlib();
    MatLib* cups = getGlassCups();
    MatLib* bread = getBreadMatlib();
    MatLib* plate = getPlateMatlib();
    loadOBJ(scene,"models/","plate.obj",plate);
    loadOBJ(scene,"models/","kettle.obj",matlib_pot);
    loadOBJ(scene,"models/", "Bread.obj",bread);
    // loadOBJ(scene,"models/", "glass_2.obj",bottle);
    loadOBJ(scene,"models/", "empty_and_filled_cup.obj",cups);

    // MatLib* frame = getFrameMatlib();
    //loadOBJ(scene,"models/","frame.obj",frame);
    // MatLib* wall = getWallMatlib();
    // loadOBJ(scene,"models/","wall.obj",wall);
    // MatLib* floor = getFloorMatlib();
    //loadOBJ(scene,"models/","floor.obj",wall);
    //loadOBJ(scene,"models/","mirror_boundary.obj");
    

    //back wall
    float scale = 0.01f;
    scene->add(new Triangle(Point(-200.f,-100.f,360.f)*scale, Point(-200.f,450.f,360.f)*scale, Point(350.f,-100.f,360.f)*scale, nullptr, &white));
    scene->add(new Triangle(Point(350.f,450.f,360.f)*scale, Point(350.f,-100.f,360.f)*scale, Point(-200.f,450.f,360.f)*scale, nullptr, &white));

    //floor
    scene->add(new Triangle(Point(-200.f,-100.f,000.f)*scale, Point(-200.f,-100.f,560.f)*scale, Point(350.f,-100.f,000.f)*scale, nullptr, &white));
    scene->add(new Triangle(Point(350.f,-100.f,560.f)*scale, Point(350.f,-100.f,000.f)*scale, Point(-200.f,-100.f,560.f)*scale, nullptr, &white));

    //left wall
    scene->add(new Triangle(Point(350.f,-100.f,000.f)*scale, Point(350.f,-100.f,560.f)*scale, Point(350.f,450.f,000.f)*scale, nullptr, &white));
    scene->add(new Triangle(Point(350.f,450.f,560.f)*scale, Point(350.f,450.f,000.f)*scale, Point(350.f,-100.f,560.f)*scale, nullptr, &white));


    //lighting
    RGBColor lightColor = RGBColor(1.0,0.99,0.98);
    // world.light.push_back(new DirectionalLight(Vector(-0.2f ,-0.5f , 1.0f).normalize(), lightColor));
    //area light
    ConstantTexture* lightsrctex = new ConstantTexture(lightColor);
    Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);
    Disc* light = new Disc(Point(-1.2424,0.376,1.105), Point(-0.11,0.3761,1.105)-Point(-1.4424,0.376,1.105), 5, nullptr, lightsource);
    AreaLight als(light);
    world.light.push_back(&als);


    RecursiveRayTracingIntegrator integrator(&world);
    scene->rebuildIndex();

    Renderer engine(cam, &integrator);
    engine.setSamples(10);
    engine.render(img);
    img.writePNG("scene.png");
}