//
//  cylinder.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "cylinder.h"

cylinder::cylinder(double rad, double height) : _rad(rad), _height(height){};

bool cylinder::intersect(dmat4 lcs, ray ray, dvec3 *intersectionPoint) const {
  //  dvec3 dist = -_pos + ray.origin;
  //  double b = glm::dot(dist, ray.dir);
  //  double c = glm::dot(dist, dist) - _rad * _rad;
  //
  //  double d = b * b - c;
  //
  //  if (d < 0) {
  //    return false;
  //  }
  //
  //  double e = glm::sqrt(d);
  //
  //  double t = (-b - e);
  //  if (t > 0) {
  //    *intersection_point = ray.origin + ray.dir * t;
  //    return true;
  //  }
  //
  //  t = (-b + e);
  //  if (t > 0) {
  //    *intersection_point = ray.origin + ray.dir * t;
  //    return true;
  //  }

  return false;
}

double cylinder::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 cylinder::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
