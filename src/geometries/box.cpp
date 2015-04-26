//
//  box.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 26/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "box.h"

box::box(vec3 min, vec3 max) : _params{ min, max } {}

geometry::ray_path box::intersect(ray ray) const {
  vec3 inv_dir{ 1 / ray.dir.x, 1 / ray.dir.y, 1 / ray.dir.z };
  unsigned char sign[3]{ inv_dir.x < 0, inv_dir.y < 0, inv_dir.z < 0 };

  float tmin, tmax, tymin, tymax, tzmin, tzmax;

  tmin = (_params[sign[0]].x - ray.origin.x) * inv_dir.x;
  tmax = (_params[1 - sign[0]].x - ray.origin.x) * inv_dir.x;
  tymin = (_params[sign[1]].y - ray.origin.y) * inv_dir.y;
  tymax = (_params[1 - sign[1]].y - ray.origin.y) * inv_dir.y;

  ray_path list;

  if ((tmin > tymax) || (tymin > tmax)) {
    return list;
  }
  if (tymin > tmin) {
    tmin = tymin;
  }
  if (tymax < tmax) {
    tmax = tymax;
  }

  tzmin = (_params[sign[2]].z - ray.origin.z) * inv_dir.z;
  tzmax = (_params[1 - sign[2]].z - ray.origin.z) * inv_dir.z;

  if ((tmin > tzmax) || (tzmin > tmax)) {
    return list;
  }
  if (tzmin > tmin) {
    tmin = tzmin;
  }
  if (tzmax < tmax) {
    tmax = tzmax;
  }

  list.push_back({ tmin, geometry::IN });
  list.push_back({ tmax, geometry::OUT });

  return list;
}

num_t box::get_color(vec3 point) const { return 0; }

vec3 box::get_normal(vec3 point) const { return glm::normalize(point); }
