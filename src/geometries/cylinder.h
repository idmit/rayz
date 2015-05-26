//
//  cylinder.h
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__cylinder__
#define __rayz__cylinder__

#include "geometry.h"

class cylinder : public geometry {
public:
  cylinder(num_t rad, num_t height);
  virtual ray_path intersect(ray ray) const override;
  virtual num_t get_color(const vec3 &point) const override;
  virtual vec3 get_normal(const vec3 &point) const override;

private:
  num_t _rad, _height;
  num_t _rad2, _height2;
};

#endif /* defined(__rayz__cylinder__) */
