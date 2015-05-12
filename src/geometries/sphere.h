//
//  sphere.h
//  rayz
//
//  Created by Иван Дмитриевский on 12/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__sphere__
#define __rayz__sphere__

#include "geometry.h"

class sphere : public geometry {
public:
  sphere(num_t rad);
  virtual ray_path intersect(ray ray) const override;
  virtual num_t get_color(const vec3 &point) const override;
  virtual vec3 get_normal(const vec3 &point) const override;

private:
  num_t _rad;
};

#endif /* defined(__rayz__sphere__) */
