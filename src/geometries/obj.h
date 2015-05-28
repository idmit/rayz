//
//  obj.h
//  rayz
//
//  Created by Иван Дмитриевский on 25/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__obj__
#define __rayz__obj__

#include "geometry.h"

#include <vector>
#include "triangle.h"
#include "box.h"

class obj : public geometry {
public:
  obj(const char *filename);
  virtual ray_path intersect(ray ray) const override;
  virtual num_t get_color(const vec3 &point) const override;
  virtual vec3 get_normal(const vec3 &point) const override;

  virtual material get_material() const override;

private:
  std::vector<std::vector<triangle> > _triangles;
  std::vector<std::vector<material> > _materials;
  std::vector<box> _boxes;
  mutable material _first_material;
  mutable vec3 _first_normal;
};

#endif /* defined(__rayz__obj__) */
