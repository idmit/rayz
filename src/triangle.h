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
  triangle(std::array<fvec3, 3> vertices);
  virtual bool intersect(ray ray, fvec3 *intersection_point) const override;
  virtual float get_color(fvec3 point) const override;
  virtual fvec3 get_normal(fvec3 point) const override;

private:
  std::array<fvec3, 3> _vertices;
};

#endif /* defined(__rayz__triangle__) */
