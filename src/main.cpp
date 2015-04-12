//
//  main.cpp
//  tiny
//
//  Created by Иван Дмитриевский on 22/03/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "png++/png.hpp"
#include "yaml-cpp/yaml.h"
#include "opts.h"

#include "sphere.h"

int main(int argc, const char* argv[]) {

  png::image<png::rgb_pixel> img(128, 128);
  img.write("test.png");

  std::string sceneDesc;
  unsigned long resX, resY;
  std::string outputImg;
  unsigned long traceDepth;

  if (!opts::get(argc, argv, &sceneDesc, &resX, &resY, &outputImg,
                 &traceDepth)) {
    return 1;
  }

  YAML::Node sceneConfig = YAML::LoadFile(sceneDesc);

  Sphere s;

  return 0;
}
