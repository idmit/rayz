//
//  cone.h
//  rayz
//
//  Created by Иван Дмитриевский on 17/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__cone__
#define __rayz__cone__

#include "geometry.h"

class cone : public geometry {
public:
  cone(double bottom_rad, double top_rad, double height);
  virtual ray_path intersect(ray ray) const override;
  virtual double get_color(dvec3 point) const override;
  virtual dvec3 get_normal(dvec3 point) const override;

private:
  double _bottom_rad, _top_rad, _height;
};

#endif /* defined(__rayz__cone__) */
