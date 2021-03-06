//
//  geometry.h
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef rayz_geometry_h
#define rayz_geometry_h

#include <list>
#include <utility>
#include "../types.h"
#include "../lights/material.h"

class geometry {
public:
  enum mode { IN, OUT };

  using ray_path = std::list<std::pair<num_t, geometry::mode> >;

  virtual ray_path intersect(ray ray) const = 0;
  virtual num_t get_color(const vec3 &point) const = 0;
  virtual vec3 get_normal(const vec3 &point) const = 0;
  virtual material get_material() const { return _material; };
  virtual ~geometry();

  void set_material(const material &mat);

protected:
  material _material;
};

#endif
