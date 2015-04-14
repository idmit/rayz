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
  torus(float rad, float tube_rad);
  virtual bool intersect(ray ray, fvec3 *intersection_point) const override;
  virtual float get_color(fvec3 point) const override;
  virtual fvec3 get_normal(fvec3 point) const override;

private:
  float _rad, _tube_rad;
};

#endif /* defined(__rayz__torus__) */
