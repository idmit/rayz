//
//  cylinder.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "cylinder.h"

cylinder::cylinder(double rad, double height) : _rad(rad), _height(height){};

bool cylinder::intersect(ray ray, dvec3 *intersectionPoint) const {
  return false;
}

double cylinder::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 cylinder::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
