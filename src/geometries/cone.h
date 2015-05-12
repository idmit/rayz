//
//  cone.h
//  rayz
//
//  Created by Иван Дмитриевский on 17/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__cone__
#define __rayz__cone__

#include "geometry.h"

class cone : public geometry {
public:
  cone(num_t bottom_rad, num_t top_rad, num_t height);
  virtual ray_path intersect(ray ray) const override;
  virtual num_t get_color(const vec3 &point) const override;
  virtual vec3 get_normal(const vec3 &point) const override;

private:
  num_t _bottom_rad, _top_rad, _height;
};

#endif /* defined(__rayz__cone__) */
