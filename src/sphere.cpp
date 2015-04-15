//
//  sphere.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 12/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "sphere.h"

sphere::sphere(fvec3 pos, float rad) : _pos(pos), _rad(rad) {}

bool sphere::intersect(ray ray, fvec3 *intersection_point) const {
  dvec3 dist = -_pos + ray.origin;
  double b = glm::dot(dist, ray.dir);
  double c = glm::dot(dist, dist) - _rad * _rad;

  double d = b * b - c;

  if (d < 0) {
    return false;
  }

  double e = glm::sqrt(d);

  double t = (-b - e);
  if (t > 0) {
    *intersection_point = ray.origin + ray.dir * t;
    return true;
  }

  t = (-b + e);
  if (t > 0) {
    *intersection_point = ray.origin + ray.dir * t;
    return true;
  }

  return false;
}

float sphere::get_color(fvec3 point) const { return 0; }

fvec3 sphere::get_normal(fvec3 point) const {
  fvec3 n(point - _pos);
  glm::normalize(n);
  return n;
}
