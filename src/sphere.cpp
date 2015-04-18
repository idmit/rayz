//
//  sphere.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 12/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "sphere.h"

sphere::sphere(double rad) : _rad(rad) {}

bool sphere::intersect(ray ray, dvec3 *close_intersection_point,
                       dvec3 *far_intersection_point,
                       std::pair<double, double> *param_vals) const {
  double b = glm::dot(ray.origin, ray.dir);
  double c = glm::dot(ray.origin, ray.origin) - _rad * _rad;

  double d = b * b - c;

  if (d < 0) {
    return false;
  }

  bool intersected = false;
  double e = glm::sqrt(d);

  double t = (-b - e);
  if (t > 0) {
    *close_intersection_point = ray.origin + ray.dir * t;
    intersected = true;
  }

  t = (-b + e);
  if (t > 0) {
    if (intersected) {
      if (far_intersection_point) {
        *far_intersection_point = ray.origin + ray.dir * t;
      }
      if (param_vals) {
        param_vals->first = -b - e;
        param_vals->second = t;
      }
    } else {
      *close_intersection_point = ray.origin + ray.dir * t;
      intersected = true;
    }
  }

  return intersected;
}

double sphere::get_color(dvec3 point) const { return 0; }

dvec3 sphere::get_normal(dvec3 point) const {
  dvec3 n(point);
  glm::normalize(n);
  return n;
}
