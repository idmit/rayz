//
//  triangle.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "triangle.h"

triangle::triangle(std::array<vec3, 3> vertices) : _vertices(vertices) {}

geometry::ray_path triangle::intersect(ray ray) const {
  vec3 n = glm::normalize(
      glm::cross((_vertices[1] - _vertices[0]), _vertices[2] - _vertices[0]));
  num_t t = -glm::dot((ray.origin - _vertices[0]), n) / glm::dot(ray.dir, n);

  ray_path list;

  vec3 intersection_point = ray.origin + ray.dir * t;

  if (glm::dot(glm::cross(_vertices[1] - _vertices[0],
                          intersection_point - _vertices[0]),
               n) < 0) {
    return list;
  }
  if (glm::dot(glm::cross(_vertices[2] - _vertices[1],
                          intersection_point - _vertices[1]),
               n) < 0) {
    return list;
  }
  if (glm::dot(glm::cross(_vertices[0] - _vertices[2],
                          intersection_point - _vertices[2]),
               n) < 0) {
    return list;
  }

  list.push_back({ t, geometry::IN });
  list.push_back({ t, geometry::OUT });

  return list;
}

num_t triangle::get_color(vec3 point) const { return 0; }

vec3 triangle::get_normal(vec3 point) const {
  return glm::normalize(
      glm::cross((_vertices[1] - _vertices[0]), _vertices[2] - _vertices[0]));
}
