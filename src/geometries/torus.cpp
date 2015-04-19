//
//  torus.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "poly34.h"
#include "torus.h"
#include <algorithm>

torus::torus(double rad, double tube_rad) : _rad(rad), _tube_rad(tube_rad){};

bool torus::intersect(ray ray, dvec3 *close_intersection_point,
                      dvec3 *far_intersection_point,
                      std::pair<double, double> *param_vals) const {
  double alpha = glm::dot(ray.dir, ray.dir);
  double beta = 2 * glm::dot(ray.origin, ray.dir);
  double gamma =
      glm::dot(ray.origin, ray.origin) - _tube_rad * _tube_rad - _rad * _rad;

  double a4 = alpha * alpha;
  double a3 = 2 * alpha * beta;
  double a2 =
      beta * beta + 2 * alpha * gamma + 4 * _rad * _rad * ray.dir.z * ray.dir.z;
  double a1 = 2 * beta * gamma + 8 * _rad * _rad * ray.origin.z * ray.dir.z;
  double a0 =
      gamma * gamma +
      4 * _rad * _rad * (ray.origin.z * ray.origin.z - _tube_rad * _tube_rad);

  double x[4];
  int num = SolveP4(x, a3 / a4, a2 / a4, a1 / a4, a0 / a4);
  if (num < 2) {
    return false;
  }

  if (num == 2) {
    *close_intersection_point = ray.origin + glm::min(x[0], x[1]) * ray.dir;
  }

  if (num == 4) {
    std::sort(std::begin(x), std::end(x));
    *close_intersection_point = ray.origin + x[0] * ray.dir;
  }

  return true;
}

double torus::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 torus::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
