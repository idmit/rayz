//
//  cone.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 17/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include <algorithm>
#include "cone.h"

cone::cone(num_t bottom_rad, num_t top_rad, num_t height)
    : _bottom_rad(bottom_rad), _top_rad(top_rad), _height(height) {}

geometry::ray_path cone::intersect(ray ray) const {
  num_t ts[4] = { INFINITY, INFINITY, INFINITY, INFINITY };

  num_t tan = (_bottom_rad - _top_rad) / _height;
  num_t tan2 = tan * tan;
  num_t height = _top_rad * _height / (_bottom_rad - _top_rad);

  vec3 n({ 0, 0, 1 });
  vec3 disk_centers[] = { { 0, 0, -height }, { 0, 0, -_height - height } };
  num_t rads[] = { _top_rad, _bottom_rad };

  for (unsigned i = 0; i < 2; ++i) {
    num_t t =
        -glm::dot((ray.origin - disk_centers[i]), n) / glm::dot(ray.dir, n);
    vec3 plane_intersection = ray.origin + ray.dir * t;
    if (glm::dot(plane_intersection - disk_centers[i],
                 plane_intersection - disk_centers[i]) <= rads[i] * rads[i]) {
      ts[i] = t;
    }
  }

  glm::dvec2 origin(ray.origin), dir(ray.dir);
  num_t a = glm::dot(dir, dir) - tan2 * ray.dir.z * ray.dir.z;
  num_t b = glm::dot(origin, dir) - 2 * tan2 * ray.origin.z * ray.dir.z;
  num_t c = glm::dot(origin, origin) - tan2 * ray.origin.z * ray.origin.z;

  num_t d = b * b - a * c;
  if (d >= 0) {
    num_t e = glm::sqrt(d);

    num_t t = (-b - e) / a;
    for (unsigned i = 0; i < 2; ++i) {
      if (t > 0) {
        vec3 side_intersection = ray.origin + ray.dir * t;
        if (-_height - height <= side_intersection.z &&
            side_intersection.z <= -height) {
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

num_t cone::get_color(const vec3 &point) const { return 0; }

vec3 cone::get_normal(const vec3 &point) const { return { 0, 0, 0 }; }
