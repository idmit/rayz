//
//  geometry.h
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef rayz_geometry_h
#define rayz_geometry_h

#include "types.h"

class geometry {
public:
  virtual bool intersect(ray ray, dvec3 *intersection_point) const = 0;
  virtual double get_color(dvec3 point) const = 0;
  virtual dvec3 get_normal(dvec3 point) const = 0;
  virtual ~geometry(){};
};

#endif
