//
//  csg_intersection.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 18/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "csg_intersection.h"

csg_intersection::csg_intersection(std::unique_ptr<node> &&lhs,
                                   std::unique_ptr<node> &&rhs)
    : _lhs(std::move(lhs)), _rhs(std::move(rhs)) {}

geometry::ray_path csg_intersection::intersect(ray ray) const {
  auto list = _lhs->intersect(ray);
  auto rhs = _rhs->intersect(ray);

  if (list.empty() || rhs.empty()) {
    return {};
  }

  for (const auto &pair : rhs) {
    list.push_back(pair);
  }
  list.sort();

  geometry::ray_path out_list;

  bool in = false;
  for (auto it = list.begin(); it != list.end(); ++it) {
    switch (it->second) {
      case geometry::IN:
        in = true;
        break;
      case geometry::OUT:
        if (in) {
          out_list.push_back(*(--it));
          out_list.push_back(*it);
        }
        in = false;
        break;
      default:
        break;
    }
  }

  return out_list;
}

double csg_intersection::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 csg_intersection::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
