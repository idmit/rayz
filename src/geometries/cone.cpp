//
//  cone.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 17/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "cone.h"

cone::cone(double bottom_rad, double top_rad, double height)
    : _bottom_rad(bottom_rad), _top_rad(top_rad), _height(height){};

geometry::ray_path cone::intersect(ray ray) const { return {}; }

double cone::get_color(dvec3 point) const { return 0; }

dvec3 cone::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
