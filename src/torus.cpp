//
//  torus.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "torus.h"

torus::torus(double rad, double tube_rad) : _rad(rad), _tube_rad(tube_rad){};

bool torus::intersect(dmat4 lcs, ray ray, dvec3 *intersectionPoint) const {
  return false;
}

double torus::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 torus::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
