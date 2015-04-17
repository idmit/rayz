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
#include "geometry.h"

class node {
public:
  node(std::unique_ptr<geometry> &&geom);
  void add_child(std::unique_ptr<node> &&child);

  bool intersect(ray ray, dvec3 *intersection_point) const;
  double get_color(dvec3 point) const;
  dvec3 get_normal(dvec3 point) const;

  std::vector<const node *> children() const;

  void set_lcs(const dmat4 &lcs);
  dmat4 get_lcs() const;

private:
  dmat4 _lcs;
  std::unique_ptr<geometry> _geom;
  std::vector<std::unique_ptr<node> > _children;
};

#endif /* defined(__rayz__node__) */
