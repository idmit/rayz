//
//  torus.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "torus.h"

torus::torus(float rad, float tube_rad) : _rad(rad), _tube_rad(tube_rad){};

bool torus::intersect(ray ray, fvec3 *intersectionPoint) const { return false; }

float torus::get_color(fvec3 intersectionPoint) const { return 0; }

fvec3 torus::get_normal(fvec3 point) const { return { 0, 0, 0 }; }
