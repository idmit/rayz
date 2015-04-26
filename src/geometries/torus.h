//
//  torus.h
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__torus__
#define __rayz__torus__

#include "geometry.h"

class torus : public geometry {
public:
  torus(num_t rad, num_t tube_rad);
  virtual ray_path intersect(ray ray) const override;
  virtual num_t get_color(vec3 point) const override;
  virtual vec3 get_normal(vec3 point) const override;

private:
  num_t _rad, _tube_rad;
};

#endif /* defined(__rayz__torus__) */
