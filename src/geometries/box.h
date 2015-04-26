//
//  box.h
//  rayz
//
//  Created by Иван Дмитриевский on 26/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__box__
#define __rayz__box__

#include "geometry.h"

class box : public geometry {
public:
  box(vec3 min, vec3 max);
  virtual ray_path intersect(ray ray) const override;
  virtual num_t get_color(vec3 point) const override;
  virtual vec3 get_normal(vec3 point) const override;

private:
  vec3 _params[2];
};

#endif /* defined(__rayz__box__) */
