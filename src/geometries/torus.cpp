//
//  torus.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "torus.h"

torus::torus(double rad, double tube_rad) : _rad(rad), _tube_rad(tube_rad){};

bool torus::intersect(ray ray, dvec3 *close_intersection_point,
                      dvec3 *far_intersection_point,
                      std::pair<double, double> *param_vals) const {
  return false;
}

double torus::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 torus::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
