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

class geometry {
public:
  enum mode { IN, OUT };

  using ray_path = std::list<std::pair<double, geometry::mode> >;

  virtual ray_path intersect(ray ray) const = 0;
  virtual double get_color(dvec3 point) const = 0;
  virtual dvec3 get_normal(dvec3 point) const = 0;
  virtual ~geometry(){};
};

#endif
