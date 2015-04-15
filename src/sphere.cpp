//
//  sphere.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 12/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "sphere.h"

sphere::sphere(dvec3 pos, double rad) : _pos(pos), _rad(rad) {}

bool sphere::intersect(ray ray, dvec3 *intersection_point) const {
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

double sphere::get_color(dvec3 point) const { return 0; }

dvec3 sphere::get_normal(dvec3 point) const {
  dvec3 n(point - _pos);
  glm::normalize(n);
  return n;
}
