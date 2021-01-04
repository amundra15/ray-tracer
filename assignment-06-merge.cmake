cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
)

set(ASSIGNMENT_SOURCES
    core/interpolate.cpp
    core/interpolate-impl.h
    core/interpolate.h
    core/random.cpp
    core/random.h
    rt/cameras/dofperspective.cpp
    rt/cameras/dofperspective.h
    rt/coordmappers/coordmapper.h
    rt/coordmappers/cylindrical.cpp
    rt/coordmappers/cylindrical.h
    rt/coordmappers/plane.cpp
    rt/coordmappers/plane.h
    rt/coordmappers/spherical.cpp
    rt/coordmappers/spherical.h
    rt/coordmappers/tmapper.cpp
    rt/coordmappers/tmapper.h
    rt/coordmappers/world.cpp
    rt/coordmappers/world.h
    rt/integrators/recraytrace.cpp
    rt/integrators/recraytrace.h
    rt/lights/arealight.cpp
    rt/lights/arealight.h
    rt/loaders/objmat.cpp
    rt/materials/lambertian.cpp
    rt/materials/lambertian.h
    rt/materials/phong.cpp
    rt/materials/phong.h
    rt/materials/mirror.cpp
    rt/materials/mirror.h
    rt/materials/combine.cpp
    rt/materials/combine.h
    rt/materials/flatmaterial.cpp
    rt/materials/flatmaterial.h
    rt/materials/fuzzymirror.cpp
    rt/materials/fuzzymirror.h
    rt/materials/glass.cpp
    rt/materials/glass.h
    rt/solids/striangle.cpp
    rt/solids/striangle.h
    rt/textures/texture.h
    rt/textures/constant.cpp
    rt/textures/constant.h
    rt/textures/checkerboard.cpp
    rt/textures/checkerboard.h
    rt/textures/imagetex.cpp
    rt/textures/imagetex.h
    rt/textures/perlin.cpp
    rt/textures/perlin.h
    ${MY_ADDITIONAL_SOURCES}
    main/a_materials.cpp
    main/a_textures.cpp
    main/a_local.cpp
    main/a_mappers.cpp
    main/a_distributed.cpp
    main/a_smooth.cpp
)

file(COPY
    models/stones_diffuse.png
    DESTINATION ${CMAKE_BINARY_DIR}/models
)
