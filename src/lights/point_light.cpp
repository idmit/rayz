//
//  point_light.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 26/05/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "point_light.h"

point_light::point_light(color amb, color diff, color spec, const node *rep,
                         vec3 att, vec3 pos)
    : light(amb, diff, spec, rep), _att(att), _pos(pos) {}

void point_light::set_pos(const vec3 &pos) { _pos = pos; }

vec3 point_light::get_dir(const vec3 &point) const { return _pos - point; }

num_t point_light::get_dist(const vec3 &point) const {
  return glm::distance(_pos, point);
}

vec3 point_light::get_att() const { return _att; }
