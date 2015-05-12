//
//  plane.h
//  rayz
//
//  Created by Иван Дмитриевский on 27/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__plane__
#define __rayz__plane__

#include "geometry.h"

class plane : public geometry {
public:
  plane();
  virtual ray_path intersect(ray ray) const override;
  virtual num_t get_color(const vec3 &point) const override;
  virtual vec3 get_normal(const vec3 &point) const override;
};

#endif /* defined(__rayz__plane__) */
