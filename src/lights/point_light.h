//
//  point_light.h
//  rayz
//
//  Created by Иван Дмитриевский on 26/05/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__point_light__
#define __rayz__point_light__

#include "light.h"

class point_light : public light {
public:
  using light::light;
  point_light(color amb, color diff, color spec, const node *rep, vec3 att,
              vec3 pos);

  void set_pos(const vec3 &pos);
  vec3 get_dir(const vec3 &point) const override;
  num_t get_dist(const vec3 &point) const override;

  vec3 get_att() const override;

private:
  vec3 _att;
  vec3 _pos;
};

#endif /* defined(__rayz__point_light__) */
