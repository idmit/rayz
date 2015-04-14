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

  bool intersect(ray ray, fvec3 *intersection_point) const;
  float get_color(fvec3 point) const;
  fvec3 get_normal(fvec3 point) const;

private:
  fmat4 _lcs;
  std::unique_ptr<geometry> _geom;
  std::vector<std::unique_ptr<node> > _children;
};

#endif /* defined(__rayz__node__) */
