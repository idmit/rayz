//
//  renderer.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "renderer.h"
#include "types.h"
#include "sphere.h"
#include "triangle.h"

png::image<png::rgb_pixel> renderer::run(const scene& scene, unsigned long resX,
                                         unsigned long resY) {
  png::image<png::rgb_pixel> img(resX, resY);

  for (unsigned long y = 0; y < resY; ++y) {
    for (unsigned long x = 0; x < resX; ++x) {
      for (auto& node : scene.nodes()) {
        float fx = float(x), fy = float(y);
        ray ray;
        ray.origin = fvec3(fx, fy, -1000.0f);
        ray.dir = fvec3(0.0f, 0.0f, 1.0f);
        fvec3 ip;
        if (node->intersect(ray, &ip)) {
          unsigned char i = ip.z;
          img.set_pixel(ip.x, ip.y, { i, i, i });
        }
      }
    }
  }

  return img;
}
