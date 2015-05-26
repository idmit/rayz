//
//  cylinder.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "cylinder.h"
#include "glm/gtc/epsilon.hpp"
#include <algorithm>

cylinder::cylinder(num_t rad, num_t height)
    : _rad(rad), _height(height), _rad2(rad * rad), _height2(height / 2) {}

cylinder::ray_path cylinder::intersect(ray ray) const {

  num_t ts[4] = { INFINITY, INFINITY, INFINITY, INFINITY };

  vec3 n({ 0, 0, 1 });
  vec3 disk_centers[] = { { 0, 0, _height2 }, { 0, 0, -_height2 } };

  for (unsigned i = 0; i < 2; ++i) {
    num_t t =
        -glm::dot((ray.origin - disk_centers[i]), n) / glm::dot(ray.dir, n);
    vec3 plane_intersection = ray.origin + ray.dir * t;
    if (glm::dot(plane_intersection - disk_centers[i],
                 plane_intersection - disk_centers[i]) <= _rad2) {
      ts[i] = t;
    }
  }

  glm::dvec2 origin(ray.origin), dir(ray.dir);
  num_t a = glm::dot(dir, dir);
  num_t b = glm::dot(origin, dir);
  num_t c = glm::dot(origin, origin) - _rad2;

  num_t d = b * b - a * c;
  if (d >= 0) {
    num_t e = glm::sqrt(d);

    num_t t = (-b - e) / a;
    for (unsigned i = 0; i < 2; ++i) {
      if (t > 0) {
        vec3 side_intersection = ray.origin + ray.dir * t;
        if (-_height2 <= side_intersection.z &&
            side_intersection.z <= _height2) {
          ts[2 + i] = t;
        }
      }
      t += 2 * e / a;
    }
  }

  ray_path list;

  std::sort(std::begin(ts), std::end(ts));
  if (ts[0] < INFINITY) {
    list.push_back({ ts[0], geometry::IN });
  }

  if (ts[1] < INFINITY) {
    list.push_back({ ts[1], geometry::OUT });
  }

  return list;
}

num_t cylinder::get_color(const vec3 &point) const { return 0; }

vec3 cylinder::get_normal(const vec3 &point) const {
  glm::tvec2<num_t> xy(point);
  if (glm::epsilonEqual(point.z, _height2, glm::epsilon<num_t>())) {
    return vec3{ 0, 0, 1 };
  }
  if (glm::epsilonEqual(point.z, -_height2, glm::epsilon<num_t>())) {
    return vec3{ 0, 0, -1 };
  }
  return vec3{ glm::normalize(xy), 0 };
}
