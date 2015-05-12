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

torus::torus(num_t rad, num_t tube_rad) : _rad(rad), _tube_rad(tube_rad) {}

geometry::ray_path torus::intersect(ray ray) const {
  num_t alpha = glm::dot(ray.dir, ray.dir);
  num_t beta = 2 * glm::dot(ray.origin, ray.dir);
  num_t gamma =
      glm::dot(ray.origin, ray.origin) - _tube_rad * _tube_rad - _rad * _rad;

  num_t a4 = alpha * alpha;
  num_t a3 = 2 * alpha * beta;
  num_t a2 =
      beta * beta + 2 * alpha * gamma + 4 * _rad * _rad * ray.dir.z * ray.dir.z;
  num_t a1 = 2 * beta * gamma + 8 * _rad * _rad * ray.origin.z * ray.dir.z;
  num_t a0 =
      gamma * gamma +
      4 * _rad * _rad * (ray.origin.z * ray.origin.z - _tube_rad * _tube_rad);

  num_t x[4];
  int num = SolveP4(x, a3 / a4, a2 / a4, a1 / a4, a0 / a4);

  ray_path list;

  if (num < 2) {
    return list;
  }

  if (num == 2) {
    list.push_back({ x[0], geometry::IN });
    list.push_back({ x[1], geometry::OUT });
  }

  if (num == 4) {
    std::sort(std::begin(x), std::end(x));
    list.push_back({ x[0], geometry::IN });
    list.push_back({ x[1], geometry::OUT });

    list.push_back({ x[2], geometry::IN });
    list.push_back({ x[3], geometry::OUT });
  }

  return list;
}

num_t torus::get_color(const vec3 &point) const { return 0; }

vec3 torus::get_normal(const vec3 &point) const { return { 0, 0, 0 }; }
