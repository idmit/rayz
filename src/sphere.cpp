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
  fvec3 dist = _pos - ray.origin;
  float B = glm::dot(ray.dir, dist);
  double D = B * B - glm::dot(dist, dist) + _rad * _rad;

  if (D < 0.0f) {
    return false;
  }
  float t0 = B - glm::sqrt(D);
  float t1 = B + glm::sqrt(D);

  if ((t0 > 0.1f)) { // && (t0 < t)) {
    *intersection_point = ray.origin + ray.dir * t0;
    return true;
  }
  if ((t1 > 0.1f)) {
    *intersection_point = ray.origin + ray.dir * t1;
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
