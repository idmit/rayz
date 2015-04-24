//
//  cylinder.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "cylinder.h"

#include <algorithm>

cylinder::cylinder(double rad, double height) : _rad(rad), _height(height){};

cylinder::ray_path cylinder::intersect(ray ray) const {

  double ts[4] = { INFINITY, INFINITY, INFINITY, INFINITY };

  dvec3 n({ 0, 0, 1 });
  dvec3 disk_centers[] = { { 0, 0, _height / 2 }, { 0, 0, -_height / 2 } };

  for (unsigned i = 0; i < 2; ++i) {
    double t =
        -glm::dot((ray.origin - disk_centers[i]), n) / glm::dot(ray.dir, n);
    dvec3 plane_intersection = ray.origin + ray.dir * t;
    if (glm::dot(plane_intersection - disk_centers[i],
                 plane_intersection - disk_centers[i]) <= _rad * _rad) {
      ts[i] = t;
    }
  }

  glm::dvec2 origin(ray.origin), dir(ray.dir);
  double a = glm::dot(dir, dir);
  double b = glm::dot(origin, dir);
  double c = glm::dot(origin, origin) - _rad * _rad;

  double d = b * b - a * c;
  if (d >= 0) {
    double e = glm::sqrt(d);

    double t = (-b - e) / a;
    for (unsigned i = 0; i < 2; ++i) {
      if (t > 0) {
        dvec3 side_intersection = ray.origin + ray.dir * t;
        if (-_height / 2 <= side_intersection.z &&
            side_intersection.z <= _height / 2) {
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

double cylinder::get_color(dvec3 point) const { return 0; }

dvec3 cylinder::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
