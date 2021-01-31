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
#include <rt/primmod/bmap.h>
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
#include <rt/materials/dummy.h>

#include <rt/lights/arealight.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>

#include <algorithm>

using namespace rt;


MatLib* getTableMatlib() {
    MatLib* matlib = new MatLib;    
    Texture* black1 = new ConstantTexture(RGBColor::rep(0.0f));
    ImageTexture* box4 = new ImageTexture("models/table_top.png");
    ImageTexture* box5 = new ImageTexture("models/table_bot.png");
    Texture* light = new ConstantTexture(RGBColor(0.6f, 0.6f, 0.9f) * 0.6);
    matlib->insert(std::pair<std::string, Material*>("Bot.006", new CookTorranceMaterial(box5, 0.1, 0.8, 0.2,0.3)));
    matlib->insert(std::pair<std::string, Material*>("Top.006", new CookTorranceMaterial(box4, 0.6, 0.4, 0.2,0.3) ));
   
    return matlib;
}

MatLib* getFlowerMatlib() {
    //https://sketchfab.com/3d-models/twigs-in-a-glass-c82d93cf80d246a990d166a33680910a
    MatLib* matlib = new MatLib;
       ImageTexture* whitetex = new ImageTexture("models/vetvicka_bobule_albedo.png");
           ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
     
    LambertianMaterial* mat = new LambertianMaterial(blacktex,whitetex);
    matlib->insert(std::pair<std::string, Material*>("vetvicka_bobule", mat));

    return matlib;
}

MatLib* getBreadMatlib() {
    MatLib* matlib = new MatLib;
       ImageTexture* whitetex = new ImageTexture("models/Bread.png");
           ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
     
    LambertianMaterial* mat = new LambertianMaterial(blacktex,whitetex);
    matlib->insert(std::pair<std::string, Material*>("bread.001", mat));
           ImageTexture* whitetex1 = new ImageTexture("models/cuttingboard_base_text.png");
           ConstantTexture* blacktex1 = new ConstantTexture(RGBColor::rep(0.0f));
     
    LambertianMaterial* mat1 = new LambertianMaterial(blacktex1,whitetex1);
    matlib->insert(std::pair<std::string, Material*>("cutting_board.001", mat1));
               ImageTexture* whitetex2 = new ImageTexture("models/cuttingboard_top_text.png");
           ConstantTexture* blacktex2 = new ConstantTexture(RGBColor::rep(0.0f));
     
    LambertianMaterial* mat2 = new LambertianMaterial(blacktex2,whitetex2);
    matlib->insert(std::pair<std::string, Material*>("cuttingboard_top.001", mat2));

    return matlib;
}

MatLib* getVaseMatlib() {
    MatLib* matlib = new MatLib;
    CombineMaterial* combined = new CombineMaterial();
    combined->add(new LambertianMaterial(new ConstantTexture(RGBColor::rep(0.1f)), new ConstantTexture(RGBColor(0.588235, 0.800000, 0.917647))), 0.2f);
    combined->add(new PhongMaterial(new ConstantTexture(RGBColor::rep(1.0f)), 144.0),0.5f);
    combined->add(new MirrorMaterial(0.0f, 0.0f), 0.3f);
    matlib->insert(std::pair<std::string, Material*>("glass.002", combined));   
   
    return matlib;
}

MatLib* getGlassCups() {
    MatLib* matlib = new MatLib;

    matlib->insert(std::pair<std::string, Material*>("glass.003", new GlassMaterial(1.45f)));
    matlib->insert(std::pair<std::string, Material*>("glass.010", new GlassMaterial(1.45f)));

    RGBColor teaColor = RGBColor(38./255, 36./255, 5./255);
    CombineMaterial* combined = new CombineMaterial();
    PhongMaterial* phong = new PhongMaterial(new ConstantTexture(teaColor), 225.0);  //Ks, Ns
    LambertianMaterial* lambertian = new LambertianMaterial(new ConstantTexture(RGBColor::rep(0.0f)), new ConstantTexture(teaColor));   //Ka, Kd
    combined->add(phong, 0.8);
    combined->add(lambertian, 0.2);
 
    matlib->insert(std::pair<std::string, Material*>("water-air.003", combined));
    matlib->insert(std::pair<std::string, Material*>("water-air.004", combined));
    matlib->insert(std::pair<std::string, Material*>("water-glass.003", combined));
    matlib->insert(std::pair<std::string, Material*>("water-glass.004", combined));
    
    return matlib;
}

MatLib* getTeapotMatlib() {
    MatLib* matlib = new MatLib;
    ImageTexture* whitetex = new ImageTexture("models/teapot_baseColor.png");

    ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
     
    LambertianMaterial* mat = new LambertianMaterial(blacktex,whitetex);

    CombineMaterial* combined = new CombineMaterial();
    combined->add(mat, 0.5f);
    combined->add( new PhongMaterial(whitetex, 100.0f),0.5f);

    matlib->insert(std::pair<std::string, Material*>("teapot",combined));

    return matlib;
}

void a_scene() {
    
    Image img(216,144);
    // Image img(1080,720);

    std::cout << "Resolution is " << img.width() << ", " << img.height() << std::endl;
    World world;
    BVH* scene = new BVH();
    world.scene = scene;


    //objects
    ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    ConstantTexture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    LambertianMaterial white(blacktex, whitetex);

    MatLib* matlib_table = getTableMatlib();
    loadOBJ(scene, "models/", "wooden_table.obj", matlib_table);
    MatLib* cups = getGlassCups();
    loadOBJ(scene,"models/", "glass_empty_filled.obj",cups);
    MatLib* bread = getBreadMatlib();
    loadOBJ(scene,"models/", "bread_french.obj",bread);
    MatLib* vase = getVaseMatlib();
    loadOBJ(scene,"models/", "vase.obj",vase);
    MatLib* flower = getFlowerMatlib();
    loadOBJ(scene,"models/", "fl1.obj",flower);
    loadOBJ(scene,"models/", "fl2.obj",flower);
    loadOBJ(scene,"models/", "fl3.obj",flower);
    MatLib* matlib_pot = getTeapotMatlib();
    loadOBJ(scene,"models/","teapot_2obj.obj",matlib_pot);
    loadOBJ(scene,"models/", "wall.obj");       //back wall
    loadOBJ(scene,"models/", "wall2.obj");   //side wall
    
    //floor
    float scale = 0.01f;
    scene->add(new Triangle(Point(-200.f,-100.f,000.f)*scale, Point(-200.f,-100.f,560.f)*scale, Point(350.f,-100.f,000.f)*scale, nullptr, &white));
    scene->add(new Triangle(Point(350.f,-100.f,560.f)*scale, Point(350.f,-100.f,000.f)*scale, Point(-200.f,-100.f,560.f)*scale, nullptr, &white));

  
    //decreasing x takes things towards right side of the scene
    //decreasing y takes it lower
    //decreasing z takes it away from the back wall


    //Lighting
    // RGBColor lightColor = RGBColor(1.0,0.99,0.98);
    RGBColor lightColor = RGBColor(255.0/255,250.0/255,233.0/255);

    //area light
    ConstantTexture* lightsrctex = new ConstantTexture(lightColor*160.0);
    Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);
    Disc* light = new Disc(Point(-0.12, 1.41f, -1.31f), Point(-0.12,0.586,2.059)-Point(-0.12, 0.31f, -1.31f), 0.25, nullptr, lightsource);
    AreaLight als(light);
    world.light.push_back(&als);


    // Main Camera
    // PerspectiveCamera* cam = new PerspectiveCamera(Point(-0.421, 0.509f, 0.657f), Point(0,0.435,1.239)-Point(-0.541, 0.519f, 0.667f), Vector(0,1,0), pi/6, pi/4);
    DOFPerspectiveCamera* cam = new DOFPerspectiveCamera(Point(-0.421, 0.509f, 0.657f), Point(0,0.435,1.239)-Point(-0.541, 0.519f, 0.667f), Vector(0,1,0), pi/6, pi/4, 0.585f, 0.004f);
        
    //debug camera
    // PerspectiveCamera* cam = new PerspectiveCamera(Point(-0.321, 0.489f, -1.444f), Vector(-0.82+0.861, 0.5043-0.509, 0.54+1.404), Vector(-0.026, 0.997714, 0.062), pi/6, pi/6);



    RecursiveRayTracingIntegrator integrator(&world);
    scene->rebuildIndex();

    Renderer engine(cam, &integrator);
    engine.setSamples(1);
    engine.render(img);
    img.writePNG("scene.png");
}