//
//  csg_difference.h
//  rayz
//
//  Created by Иван Дмитриевский on 18/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__csg_difference__
#define __rayz__csg_difference__

#include "node.h"

class csg_difference : public node {
public:
  csg_difference(std::unique_ptr<node> &&lhs, std::unique_ptr<node> &&rhs);
  virtual geometry::ray_path intersect(ray ray) const override;
  virtual color get_color(const vec3 &point) const override;
  virtual vec3 get_normal(const vec3 &point) const override;
  virtual material get_material() const override;

private:
  std::unique_ptr<node> _lhs, _rhs;
};

#endif /* defined(__rayz__csg_difference__) */
