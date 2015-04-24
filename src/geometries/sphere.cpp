//
//  sphere.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 12/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "sphere.h"

sphere::sphere(double rad) : _rad(rad) {}

geometry::ray_path sphere::intersect(ray ray) const {
  double b = glm::dot(ray.origin, ray.dir);
  double c = glm::dot(ray.origin, ray.origin) - _rad * _rad;

  double d = b * b - c;

  ray_path list;

  if (d < 0) {
    return list;
  }

  double e = glm::sqrt(d);

  double t = (-b - e);
  if (t > 0) {
    list.push_back({ t, geometry::IN });
  }

  t = (-b + e);
  if (t > 0) {
    list.push_back({ t, geometry::OUT });
  }

  return list;
}

double sphere::get_color(dvec3 point) const { return 0; }

dvec3 sphere::get_normal(dvec3 point) const { return glm::normalize(point); }
