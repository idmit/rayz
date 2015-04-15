//
//  triangle.h
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__triangle__
#define __rayz__triangle__

#include "geometry.h"
#include <array>

class triangle : public geometry {
public:
  triangle(std::array<dvec3, 3> vertices);
  virtual bool intersect(ray ray, dvec3 *intersection_point) const override;
  virtual double get_color(dvec3 point) const override;
  virtual dvec3 get_normal(dvec3 point) const override;

private:
  std::array<dvec3, 3> _vertices;
};

#endif /* defined(__rayz__triangle__) */
