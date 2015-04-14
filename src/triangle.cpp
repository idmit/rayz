//
//  triangle.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "triangle.h"

triangle::triangle(std::array<fvec3, 3> vertices) : _vertices(vertices){};

bool triangle::intersect(ray ray, fvec3 *intersectionPoint) const {
  return false;
}

float triangle::get_color(fvec3 intersectionPoint) const { return 0; }

fvec3 triangle::get_normal(fvec3 point) const { return { 0, 0, 0 }; }
