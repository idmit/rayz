//
//  obj.h
//  rayz
//
//  Created by Иван Дмитриевский on 25/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__obj__
#define __rayz__obj__

#include "geometry.h"

#include <vector>
#include "triangle.h"

class obj : public geometry {
public:
  obj(const char *filename);
  virtual ray_path intersect(ray ray) const override;
  virtual double get_color(dvec3 point) const override;
  virtual dvec3 get_normal(dvec3 point) const override;

private:
  std::vector<triangle> _triangles;
  dvec3 _min, _max;
};

#endif /* defined(__rayz__obj__) */
