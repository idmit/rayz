//
//  node.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "node.h"

node::node(std::unique_ptr<geometry> &&geom) : _geom(std::move(geom)){};

void node::add_child(std::unique_ptr<node> &&child) {
  _children.push_back(std::move(child));
}

bool node::intersect(ray ray, fvec3 *intersection_point)  const{
  return _geom->intersect(ray, intersection_point);
}

float node::get_color(fvec3 point)  const{ return _geom->get_color(point); }

fvec3 node::get_normal(fvec3 point) const { return _geom->get_normal(point); }
