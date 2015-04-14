//
//  cylinder.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "cylinder.h"

cylinder::cylinder(float rad, float height) : _rad(rad), _height(height){};

bool cylinder::intersect(ray ray, fvec3 *intersectionPoint) const {
  return false;
}

float cylinder::get_color(fvec3 intersectionPoint) const { return 0; }

fvec3 cylinder::get_normal(fvec3 point) const { return { 0, 0, 0 }; }
