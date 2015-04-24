//
//  main.cpp
//  tiny
//
//  Created by Иван Дмитриевский on 22/03/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "png++/png.hpp"
#include "opts.h"

#include "scene.h"

#include "tinyobjloader/tiny_obj_loader.h"

int main(int argc, const char* argv[]) {

  std::string scene_desc;
  unsigned long resx, resy;
  std::string output_img;
  unsigned long trace_depth;

  if (!opts::get(argc, argv, &scene_desc, &resx, &resy, &output_img,
                 &trace_depth)) {
    return 1;
  }

  scene s;
  auto cam(scene::create(scene_desc, &s));

  if (!cam) {
    return 1;
  }

  cam->render(s, resx, resy).write(output_img);

  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  tinyobj::LoadObj(shapes, materials, "bunny.obj");

  return 0;
}
