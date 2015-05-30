//
//  color.h
//  rayz
//
//  Created by Иван Дмитриевский on 23/05/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef rayz_color_h
#define rayz_color_h

#include "types.h"

class color {
public:
  explicit color(void) : rgba({ 0, 0, 0, 1 }) {}

  explicit color(const vec4 &rgba) : rgba(rgba) {}

  explicit color(num_t r, num_t g, num_t b, num_t a = 1)
      : rgba({ r, g, b, a }) {}

  explicit color(num_t val) : rgba({ val, val, val, 1 }) {}

  unsigned char r() const { return static_cast<unsigned char>(rgba.x * 255); }
  unsigned char g() const { return static_cast<unsigned char>(rgba.y * 255); }
  unsigned char b() const { return static_cast<unsigned char>(rgba.z * 255); }
  unsigned char a() const { return static_cast<unsigned char>(rgba.w * 255); }

  vec4 rgba;
};

#endif
