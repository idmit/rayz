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

class csg_deifference : public node {
public:
  csg_deifference(std::unique_ptr<node> &&lhs, std::unique_ptr<node> &&rhs);
  virtual bool intersect(
      ray ray, dvec3 *close_intersection_point,
      dvec3 *far_intersection_point = nullptr,
      std::pair<double, double> *param_vals = nullptr) const override;
  virtual double get_color(dvec3 point) const override;
  virtual dvec3 get_normal(dvec3 point) const override;

private:
  std::unique_ptr<node> _lhs, _rhs;
};

#endif /* defined(__rayz__csg_difference__) */
