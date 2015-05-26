//
//  plane.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 27/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "plane.h"

#include "glm/gtc/epsilon.hpp"

plane::plane() {}

geometry::ray_path plane::intersect(ray ray) const {
  vec3 n = vec3{ 0, 0, 1 };
  ray_path list;

  if (glm::epsilonEqual(glm::dot(ray.dir, n), 0.0, glm::epsilon<num_t>())) {
    return list;
  }

  num_t t = -glm::dot(ray.origin, n) / glm::dot(ray.dir, n);

  if (t <= glm::epsilon<num_t>()) {
    return list;
  }

  list.push_back({ t, geometry::IN });
  list.push_back({ t, geometry::OUT });

  return list;
}

num_t plane::get_color(const vec3 &point) const { return 0; }

vec3 plane::get_normal(const vec3 &point) const { return { 0, 0, 1 }; }
