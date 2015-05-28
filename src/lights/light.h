//
//  light.h
//  rayz
//
//  Created by Иван Дмитриевский on 26/05/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__light__
#define __rayz__light__

#include "color.h"
#include "../nodes/node.h"

struct light_components {
  color amb;
  color diff;
  color spec;
};

class light {
public:
  light();
  light(color amb, color diff, color spec, const node *rep);
  virtual ~light();

  virtual void enable();
  virtual void disable();
  virtual void set_state(bool state);
  virtual bool get_state(void) const;
  virtual void set_ambient(const color &ambient);
  virtual void set_diffuse(const color &diffuse);
  virtual void set_specular(const color &specular);

  virtual color get_ambient() const;
  virtual color get_diffuse() const;
  virtual color get_specular() const;

  virtual vec3 get_dir(const vec3 &point) const = 0;
  virtual num_t get_dist(const vec3 &point) const = 0;

  virtual vec3 get_att() const = 0;

  const node *rep = nullptr;

protected:
  light_components _comps;
  bool _enabled;
};

#endif /* defined(__rayz__light__) */
