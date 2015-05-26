//
//  node.h
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__node__
#define __rayz__node__

#include <memory>
#include <vector>
#include "../geometries/geometry.h"
#include "../lights/material.h"

class node {
public:
  node();
  node(const material &mat);
  void add_child(std::unique_ptr<node> &&child);

  virtual geometry::ray_path intersect(ray ray) const = 0;
  virtual color get_color(const vec3 &point) const = 0;
  virtual vec3 get_normal(const vec3 &point) const = 0;
  virtual ~node();

  std::vector<const node *> children() const;

  void set_lcs(const mat4 &lcs);
  mat4 get_lcs() const;
  mat4 get_ilcs() const;
  material get_material() const;

protected:
  mat4 _lcs;
  mat4 _ilcs;
  mat4 _tlcs;
  material _material;
  std::vector<std::unique_ptr<node> > _children;
};

#endif /* defined(__rayz__node__) */
