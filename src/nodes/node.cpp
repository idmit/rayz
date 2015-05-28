//
//  node.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "node.h"

node::~node() {}

void node::add_child(std::unique_ptr<node> &&child) {
  _children.push_back(std::move(child));
}

std::vector<const node *> node::children() const {
  std::vector<const node *> children;
  for (auto &pointer : _children) {
    const node *const v = pointer.get();
    children.push_back(v);
  }
  return children;
}

void node::set_lcs(const mat4 &lcs) {
  _lcs = lcs;
  _ilcs = glm::inverse(_lcs);
  _tlcs = glm::transpose(_lcs);
}

mat4 node::get_lcs() const { return _lcs; }
mat4 node::get_ilcs() const { return _ilcs; }
