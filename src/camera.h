//
//  camera.h
//  rayz
//
//  Created by Иван Дмитриевский on 14/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__camera__
#define __rayz__camera__

#include "png++/png.hpp"
#include "scene.h"

class scene;

class camera {
public:
  camera(dvec3 pos, double fov_x, double fov_y, dvec3 lookat);
  camera(dvec3 pos, double fov_x, double fov_y, double heading, double pitch,
         double roll);

  png::image<png::rgb_pixel> render(const scene& scene, unsigned long resX,
                                    unsigned long resY);

private:
  dvec3 _eye;
  dvec3 _lookat;
  dvec3 _up;

  dvec3 _w;
  dvec3 _u;
  dvec3 _v;

  double _dist;
  double _fovx, _fovy;
};

#endif /* defined(__rayz__camera__) */
