//
//  triangle.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "triangle.h"

triangle::triangle(std::array<dvec3, 3> vertices) : _vertices(vertices){};

bool triangle::intersect(ray ray, dvec3 *close_intersection_point,
                         dvec3 *far_intersection_point,
                         std::pair<double, double> *param_vals) const {
  dvec3 n =
      glm::cross((_vertices[1] - _vertices[0]), _vertices[2] - _vertices[0]);
  double t = -glm::dot((ray.origin - _vertices[0]), n) / glm::dot(ray.dir, n);

  *close_intersection_point = ray.origin + ray.dir * t;
  if (far_intersection_point) {
    *far_intersection_point = *close_intersection_point;
  }
  if (param_vals) {
    param_vals->first = param_vals->second = t;
  }

  if (glm::dot(glm::cross(_vertices[1] - _vertices[0],
                          *close_intersection_point - _vertices[0]),
               n) < 0) {
    return false;
  }
  if (glm::dot(glm::cross(_vertices[2] - _vertices[1],
                          *close_intersection_point - _vertices[1]),
               n) < 0) {
    return false;
  }
  if (glm::dot(glm::cross(_vertices[0] - _vertices[2],
                          *close_intersection_point - _vertices[2]),
               n) < 0) {
    return false;
  }
  return true;
}

double triangle::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 triangle::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
