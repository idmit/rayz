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

class node {
public:
  void add_child(std::unique_ptr<node> &&child);

  virtual geometry::ray_path intersect(ray ray) const = 0;
  virtual double get_color(dvec3 point) const = 0;
  virtual dvec3 get_normal(dvec3 point) const = 0;

  std::vector<const node *> children() const;

  void set_lcs(const dmat4 &lcs);
  dmat4 get_lcs() const;

protected:
  dmat4 _lcs;
  std::vector<std::unique_ptr<node> > _children;
};

#endif /* defined(__rayz__node__) */
