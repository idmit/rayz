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

bool node::intersect(ray ray, dvec3 *intersection_point) const {
  return _geom->intersect(_lcs, ray, intersection_point);
}

double node::get_color(dvec3 point) const { return _geom->get_color(point); }

dvec3 node::get_normal(dvec3 point) const { return _geom->get_normal(point); }

std::vector<const node *> node::children() const {
  std::vector<const node *> children;
  for (auto &pointer : _children) {
    const node *const v = pointer.get();
    children.push_back(v);
  }
  return children;
}

void node::set_lcs(const dmat4 &lcs) { _lcs = lcs; }

dmat4 node::get_lcs() const { return _lcs; }
