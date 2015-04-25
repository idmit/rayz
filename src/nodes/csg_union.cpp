//
//  csg_union.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 18/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "csg_union.h"

csg_union::csg_union(std::unique_ptr<node> &&lhs, std::unique_ptr<node> &&rhs)
    : _lhs(std::move(lhs)), _rhs(std::move(rhs)) {}

geometry::ray_path csg_union::intersect(ray ray) const {
  auto list = _lhs->intersect(ray);
  auto rhs = _rhs->intersect(ray);

  for (const auto &pair : rhs) {
    list.push_back(pair);
  }
  list.sort();

  geometry::ray_path out_list;

  unsigned depth = 0;
  auto left = list.begin();
  for (auto it = list.begin(); it != list.end(); ++it) {
    switch (it->second) {
      case geometry::IN:
        if (depth == 0) {
          left = it;
        }
        ++depth;
        break;
      case geometry::OUT:
        --depth;
        if (depth == 0) {
          out_list.push_back(*left);
          out_list.push_back(*it);
        }
        break;
      default:
        break;
    }
  }

  return out_list;
}

double csg_union::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 csg_union::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
