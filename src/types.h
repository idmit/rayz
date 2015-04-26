//
//  types.h
//  rayz
//
//  Created by Иван Дмитриевский on 12/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__types__
#define __rayz__types__

#include "glm/glm.hpp"

using num_t = double;
using vec3 = glm::tvec3<num_t>;
using mat4 = glm::tmat4x4<num_t>;

struct ray {
  vec3 origin;
  vec3 dir;
};

#endif /* defined(__rayz__types__) */
