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
  virtual bool intersect(ray ray, fvec3 *intersection_point) const = 0;
  virtual float get_color(fvec3 point) const = 0;
  virtual fvec3 get_normal(fvec3 point) const = 0;
  virtual ~geometry(){};
};

#endif
