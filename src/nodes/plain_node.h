//
//  plain_node.h
//  rayz
//
//  Created by Иван Дмитриевский on 18/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__plain_node__
#define __rayz__plain_node__

#include "node.h"

class plain_node : public node {
public:
  plain_node(std::unique_ptr<geometry> &&geom);

  virtual geometry::ray_path intersect(ray ray) const override;
  virtual double get_color(dvec3 point) const override;
  virtual dvec3 get_normal(dvec3 point) const override;

private:
  std::unique_ptr<geometry> _geom;
};

#endif /* defined(__rayz__plain_node__) */
