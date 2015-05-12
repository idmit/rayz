//
//  camera.h
//  rayz
//
//  Created by Иван Дмитриевский on 14/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__camera__
#define __rayz__camera__

#include "bitmap_image.hpp"
#include "scene.h"

class scene;

class camera {
public:
  camera(const vec3 &pos, num_t fov_x, num_t fov_y, const vec3 &lookat);
  camera(const vec3 &pos, num_t fov_x, num_t fov_y, num_t heading, num_t pitch,
         num_t roll);

  bitmap_image render(const scene& scene, long resX, long resY);

private:
  vec3 _eye;
  vec3 _lookat;
  vec3 _up;

  vec3 _w;
  vec3 _u;
  vec3 _v;

  num_t _dist;
  num_t _fovx, _fovy;
};

#endif /* defined(__rayz__camera__) */
