//
//  cylinder.h
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__cylinder__
#define __rayz__cylinder__

#include "geometry.h"

class cylinder : public geometry {
public:
  cylinder(float rad, float height);
  virtual bool intersect(ray ray, fvec3 *intersection_point) const override;
  virtual float get_color(fvec3 point) const override;
  virtual fvec3 get_normal(fvec3 point) const override;

private:
  float _rad, _height;
};

#endif /* defined(__rayz__cylinder__) */
