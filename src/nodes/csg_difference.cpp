//
//  csg_difference.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 18/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "csg_difference.h"

csg_difference::csg_difference(std::unique_ptr<node> &&lhs,
                               std::unique_ptr<node> &&rhs)
    : _lhs(std::move(lhs)), _rhs(std::move(rhs)) {}

geometry::ray_path csg_difference::intersect(ray ray) const {
  auto lhs = _lhs->intersect(ray);
  auto rhs = _rhs->intersect(ray);

  std::list<std::tuple<double, bool, geometry::mode> > list;

  for (const auto &pair : lhs) {
    list.emplace_back(pair.first, false, pair.second);
  }

  for (const auto &pair : rhs) {
    list.emplace_back(pair.first, true, pair.second);
  }

  list.sort();

  geometry::ray_path out_list;
  bool ina = false;
  bool inb = false;
  for (auto it = list.begin(); it != list.end(); ++it) {
    switch (std::get<2>(*it)) {
      case geometry::IN:
        if (std::get<1>(*it)) {
          inb = true;
          if (ina) {
            out_list.push_back({ std::get<0>(*it), geometry::OUT });
          }
        } else {
          ina = true;
          if (!inb) {
            out_list.push_back({ std::get<0>(*it), geometry::IN });
          }
        }
        break;
      case geometry::OUT:
        if (std::get<1>(*it)) {
          inb = false;
          if (ina) {
            out_list.push_back({ std::get<0>(*it), geometry::IN });
          }
        } else {
          ina = false;
          if (!inb) {
            out_list.push_back({ std::get<0>(*it), geometry::OUT });
          }
        }
        break;
      default:
        break;
    }
  }

  return out_list;
}

double csg_difference::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 csg_difference::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
