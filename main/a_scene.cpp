
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
    matlib->insert(std::pair<std::string, Material*>("Bot.006", new CookTorranceMaterial(box5, 0.1, 0.8, 0.2,0.3)));
    matlib->insert(std::pair<std::string, Material*>("Top.006", new CookTorranceMaterial(box4, 0.6, 0.4, 0.2,0.3) ));
   
    return matlib;
}
MatLib* getTeapotMatlib() {
    MatLib* matlib = new MatLib;
    Texture* black1 = new ConstantTexture(RGBColor(0.1f, 0.2f, 0.9f) * 0.6);
    ImageTexture* box4 = new ImageTexture("models/default.png");
   ImageTexture* box5 = new ImageTexture("models/dmr.png");
       ImageTexture* whitetex = new ImageTexture("models/lambert2SG_diffuse.png");
           ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(1.0f));
               LambertianMaterial white(blacktex, blacktex);

    //Texture*   whitetex = new ConstantTexture(RGBColor::rep(1.0f));

    Texture* light = new ConstantTexture(RGBColor(0.6f, 0.6f, 0.9f) * 0.6);
    LambertianMaterial* mat = new LambertianMaterial(blacktex,blacktex);
      CombineMaterial* combined = new CombineMaterial();
    combined->add(new LambertianMaterial(blacktex, whitetex), 0.5f);
    combined->add( new PhongMaterial(blacktex, 50.0f),0.5f);
    matlib->insert(std::pair<std::string, Material*>("Default.001",combined));

    matlib->insert(std::pair<std::string, Material*>("default.001",combined));

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
MatLib* getFlowerMatlib() {
    MatLib* matlib = new MatLib;
       ImageTexture* whitetex = new ImageTexture("models/vetvicka_bobule_albedo.png");
           ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
     
    LambertianMaterial* mat = new LambertianMaterial(blacktex,whitetex);
    matlib->insert(std::pair<std::string, Material*>("vetvicka_bobule", mat));

    //matlib->insert(std::pair<std::string, Material*>("default", combined));
   
   
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


    //matlib->insert(std::pair<std::string, Material*>("default", combined));
   
   
    return matlib;
}
MatLib* getCupMatlib() {
    MatLib* matlib = new MatLib;
       ImageTexture* whitetex = new ImageTexture("models/BHPS_PinkCupSaucer_Cup_HR_Color.png");
           ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
     
    LambertianMaterial* mat = new LambertianMaterial(blacktex,whitetex);
    matlib->insert(std::pair<std::string, Material*>("lambert4", mat));
           ImageTexture* whitetex1 = new ImageTexture("models/BHPS_PinkCupSaucer_Saucer_HR_Color.png");
           ConstantTexture* blacktex1 = new ConstantTexture(RGBColor::rep(0.0f));
     
    LambertianMaterial* mat1 = new LambertianMaterial(blacktex1,whitetex1);
    matlib->insert(std::pair<std::string, Material*>("lambert5", mat1));


    //matlib->insert(std::pair<std::string, Material*>("default", combined));
   
   
    return matlib;
}
MatLib* getPlateMatlib() {
    MatLib* matlib = new MatLib;
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    CombineMaterial* combined = new CombineMaterial();
    combined->add(new LambertianMaterial(whitetex, whitetex), 0.5f);
    combined->add( new PhongMaterial(whitetex, 10.0f),0.5f);

    matlib->insert(std::pair<std::string, Material*>("initialShadingGroup.002", combined));

    //matlib->insert(std::pair<std::string, Material*>("default", combined));
   
   
    return matlib;
}
MatLib* getVaseMatlib() {
    MatLib* matlib = new MatLib;
    Texture* whitetex = new ConstantTexture(RGBColor(.3,.2,.5));
    CombineMaterial* combined = new CombineMaterial();
    combined->add(new LambertianMaterial(whitetex, whitetex), 0.5f);
    combined->add( new PhongMaterial(whitetex, 10.0f),0.5f);
    matlib->insert(std::pair<std::string, Material*>("glass.002", combined));

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

    matlib->insert(std::pair<std::string, Material*>("glass.009", new GlassMaterial(1.45f)));
    matlib->insert(std::pair<std::string, Material*>("glass.010", new GlassMaterial(1.45f)));
    matlib->insert(std::pair<std::string, Material*>("water-air.004", new GlassMaterial(0.75f)));
    matlib->insert(std::pair<std::string, Material*>("water-glass.004", new GlassMaterial(1.09f)));
    return matlib;
}


void a_scene() {
    
    // Image img(128,128);
    Image img(360,360);
    // Image img(512,512);

    std::cout << "Resolution is " << img.width() << ", " << img.height() << std::endl;
    World world;
    BVH* scene = new BVH();
    world.scene = scene;
  
    //decreasing y takes it lower
    //decreasing x takes things towards right side of the scene
    //decreasing z takes it away from the back wall

    // Main Camera
     PerspectiveCamera* cam = new PerspectiveCamera(Point(-0.92, 0.61f, 0.62f), Vector(-0.7+0.91, 0.49-0.54, 0.79-0.66), Vector(0.123, 0.967, 0.2216), pi/6, pi/6);
    //DOFPerspectiveCamera* cam = new DOFPerspectiveCamera(Point(-0.861, 0.509f, 0.504f), Vector(-0.82+0.861, 0.5043-0.509, 0.54-0.504), Vector(-0.026, 0.997714, 0.062), pi/6, pi/6, 0.725f, 0.006f);  
         ImageTexture* bumptex = new ImageTexture("models/stones_bump.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
             Texture* greytex = new ConstantTexture(RGBColor::rep(1.0f));

  Material* grey_cook = new CookTorranceMaterial(greytex, 0.6f, 0.4f, 0.1f,0.3f);

    Material* fuzzy_mat = new FuzzyMirrorMaterial(2.485f, 3.433f, 0.01f);
    Material* glass_mat = new GlassMaterial(2.f);
    CombineMaterial* sea = new CombineMaterial();
    sea->add(grey_cook, 0.5f);
    sea->add(fuzzy_mat, 0.4f);
    sea->add(glass_mat, 0.1f);

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
    MatLib* vase = getVaseMatlib();
    MatLib* flower = getFlowerMatlib();
    MatLib* cup = getCupMatlib();
    //loadOBJ(scene,"models/","plate2.obj",plate);
    //loadOBJ(scene,"models/","teapot.obj",matlib_pot);  
    loadOBJ(scene,"models/","teapot_utah.obj",matlib_pot); 
    //loadOBJ(scene,"models/", "wall.obj");
    //loadOBJ(scene,"models/", "wall2.obj");
    loadOBJ(scene,"models/", "vase.obj",vase);
    loadOBJ(scene,"models/", "fl1.obj",flower);
    loadOBJ(scene,"models/", "fl2.obj",flower);
    loadOBJ(scene,"models/", "fl3.obj",flower);
    //loadOBJ(scene,"models/","cup.obj",cup);
    //loadOBJ(scene,"models/", "bf.obj"); 
    loadOBJ(scene,"models/", "bread_french.obj",bread);
    //loadOBJ(scene,"models/", "bread.obj",bread);
    // loadOBJ(scene,"models/", "glass_2.obj",bottle);
    loadOBJ(scene,"models/", "glass_empty_filled.obj",cups);

    // MatLib* frame = getFrameMatlib();
    //loadOBJ(scene,"models/","frame.obj",frame);
    // MatLib* wall = getWallMatlib();
    // loadOBJ(scene,"models/","wall.obj",wall);
    // MatLib* floor = getFloorMatlib();
    //loadOBJ(scene,"models/","floor.obj",wall);
    //loadOBJ(scene,"models/","mirror_boundary.obj");
    float scale = 0.01f;

    //back wall
  scene->add(
        new BumpMapper(new Triangle(Point(-200.f,-100.f,360.f)*scale, Point(-200.f,450.f,360.f)*scale, Point(350.f,-100.f,360.f)*scale, nullptr, sea),
            bumptex,Point(0.0f,0.0f,0.0f), Point(1.0f, 0.0f, 0.0f), Point(0.0f, 1.0f, 0.0f), 1.0f));
    scene->add(new BumpMapper(new Triangle(Point(350.f,450.f,360.f)*scale, Point(350.f,-100.f,360.f)*scale, Point(-200.f,450.f,360.f)*scale, nullptr, sea),
        bumptex, Point(1.0f,1.0f,0.0f), Point(0.0f, 1.0f, 0.0f), Point(1.0f, 0.0f, 0.0f),  1.0f));

    //floor
    scene->add(new Triangle(Point(-200.f,-100.f,000.f)*scale, Point(-200.f,-100.f,560.f)*scale, Point(350.f,-100.f,000.f)*scale, nullptr, &white));
    scene->add(new Triangle(Point(350.f,-100.f,560.f)*scale, Point(350.f,-100.f,000.f)*scale, Point(-200.f,-100.f,560.f)*scale, nullptr, &white));

    //left wall
    scene->add(new BumpMapper(new Triangle(Point(350.f,-100.f,000.f)*scale, Point(350.f,-100.f,560.f)*scale, Point(350.f,450.f,000.f)*scale, nullptr, sea),
                    bumptex,Point(0.0f,0.0f,0.0f), Point(1.0f, 0.0f, 0.0f), Point(0.0f, 1.0f, 0.0f), 1.0f));
    scene->add(new BumpMapper(new Triangle(Point(350.f,450.f,560.f)*scale, Point(350.f,450.f,000.f)*scale, Point(350.f,-100.f,560.f)*scale, nullptr, sea),
                bumptex, Point(1.0f,1.0f,0.0f), Point(0.0f, 1.0f, 0.0f), Point(1.0f, 0.0f, 0.0f),  1.0f));



    //lighting
    RGBColor lightColor = RGBColor(1.0,0.99,0.98);
    //world.light.push_back(new DirectionalLight(Vector(-0.2f ,-0.5f , 1.0f).normalize(), lightColor));
    //world.light.push_back(new PointLight(Point(-0.37f, 1.79f, -0.47f), lightColor*120 )); // BL1 yellow

    //area light
    //ConstantTexture* lightsrctex = new ConstantTexture(lightColor);   
     ConstantTexture* lightsrctex = new ConstantTexture(lightColor*60.0);

     Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);
    Disc* light = new Disc(Point(-0.37f, 0.89f, -0.07f), Point(0.02,0.35,0.73)-Point(-0.37f, 1.79f, -0.47f), 0.25, nullptr, lightsource);     //front
    AreaLight als(light);
    world.light.push_back(&als);


    RecursiveRayTracingIntegrator integrator(&world);
    scene->rebuildIndex();

    Renderer engine(cam, &integrator);
    engine.setSamples(6);
    engine.render(img);
    img.writePNG("scene.png");
}