//
//  triangle.h
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__triangle__
#define __rayz__triangle__

#include "geometry.h"
#include <array>

class triangle : public geometry {
public:
  triangle(std::array<vec3, 3> vertices);
  virtual ray_path intersect(ray ray) const override;
  virtual num_t get_color(const vec3 &point) const override;
  virtual vec3 get_normal(const vec3 &point) const override;

private:
  std::array<vec3, 3> _vertices;
};

#endif /* defined(__rayz__triangle__) */
