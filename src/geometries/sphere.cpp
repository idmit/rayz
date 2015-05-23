//
//  sphere.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 12/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "sphere.h"

sphere::sphere(num_t rad) : _rad(rad) {}

geometry::ray_path sphere::intersect(ray ray) const {
  num_t b = glm::dot(ray.origin, ray.dir);
  num_t c = glm::dot(ray.origin, ray.origin) - _rad * _rad;

  num_t d = b * b - c;

  ray_path list;

  if (d < 0) {
    return list;
  }

  num_t e = glm::sqrt(d);

  num_t t = (-b - e);
  if (t > 0) {
    list.push_back({ t, geometry::IN });
  }

  t = (-b + e);
  if (t > 0) {
    list.push_back({ t, geometry::OUT });
  }

  return list;
}

num_t sphere::get_color(const vec3 &point) const { return 0; }

vec3 sphere::get_normal(const vec3 &point) const {
  return glm::normalize(point);
}
