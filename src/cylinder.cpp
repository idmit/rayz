//
//  cylinder.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "cylinder.h"

cylinder::cylinder(double rad, double height) : _rad(rad), _height(height){};

bool cylinder::intersect(dmat4 lcs, ray ray, dvec3 *intersection_point) const {
  glm::dvec2 origin(ray.origin), dir(ray.dir);
  double a = glm::dot(dir, dir);
  double b = glm::dot(origin, dir);
  double c = glm::dot(origin, origin) - _rad * _rad;

  dvec3 n({ 0, 0, 1 });
  dvec3 top({ 0, 0, _height / 2 }), bottom({ 0, 0, -_height / 2 });

  double t_top = -glm::dot((ray.origin - top), n) / glm::dot(ray.dir, n);
  double t_bottom = -glm::dot((ray.origin - bottom), n) / glm::dot(ray.dir, n);

  double t_disk = glm::min(t_top, t_bottom);
  bool disk_int = true;
  dvec3 disk_center = (t_top < t_bottom) ? top : bottom;
  dvec3 disk_int_point = ray.origin + ray.dir * t_disk;
  if (glm::dot(disk_int_point - disk_center, disk_int_point - disk_center) >
      _rad * _rad) {
    disk_int = false;
    t_disk = INFINITY;
  }

  bool side_int = false;
  double d = b * b - a * c;

  if (d < 0) {
    return false;
  }

  double e = glm::sqrt(d);

  double t = (-b - e) / a, t_side = 0;
  if (t > 0) {
    *intersection_point = ray.origin + ray.dir * t;
    side_int = -_height / 2 <= intersection_point->z &&
               intersection_point->z <= _height / 2;
    t_side = (side_int) ? t : INFINITY;
  }

  t = (-b + e) / a;
  if (t > 0 && !side_int) {
    *intersection_point = ray.origin + ray.dir * t;
    side_int = -_height / 2 <= intersection_point->z &&
               intersection_point->z <= _height / 2;
    t_side = (side_int) ? t : INFINITY;
  }

  if (disk_int || side_int) {
    double t = glm::min(t_side, t_disk);
    *intersection_point = ray.origin + ray.dir * t;
    return true;
  }

  return false;
}

double cylinder::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 cylinder::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
