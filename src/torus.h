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
  torus(double rad, double tube_rad);
  virtual bool intersect(ray ray, dvec3 *intersection_point) const override;
  virtual double get_color(dvec3 point) const override;
  virtual dvec3 get_normal(dvec3 point) const override;

private:
  double _rad, _tube_rad;
};

#endif /* defined(__rayz__torus__) */
