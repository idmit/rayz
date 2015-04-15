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
  cylinder(double rad, double height);
  virtual bool intersect(dmat4 lcs, ray ray,
                         dvec3 *intersection_point) const override;
  virtual double get_color(dvec3 point) const override;
  virtual dvec3 get_normal(dvec3 point) const override;

private:
  double _rad, _height;
};

#endif /* defined(__rayz__cylinder__) */
