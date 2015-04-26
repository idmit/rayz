//
//  csg_intersection.h
//  rayz
//
//  Created by Иван Дмитриевский on 18/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__csg_intersection__
#define __rayz__csg_intersection__

#include "node.h"

class csg_intersection : public node {
public:
  csg_intersection(std::unique_ptr<node> &&lhs, std::unique_ptr<node> &&rhs);
  virtual geometry::ray_path intersect(ray ray) const override;
  virtual num_t get_color(vec3 point) const override;
  virtual vec3 get_normal(vec3 point) const override;

private:
  std::unique_ptr<node> _lhs, _rhs;
};

#endif /* defined(__rayz__csg_intersection__) */
