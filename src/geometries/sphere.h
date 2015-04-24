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
  sphere(double rad);
  virtual ray_path intersect(ray ray) const override;
  virtual double get_color(dvec3 point) const override;
  virtual dvec3 get_normal(dvec3 point) const override;

private:
  double _rad;
};

#endif /* defined(__rayz__sphere__) */
