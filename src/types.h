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

using fvec3 = glm::fvec3;
using fmat4 = glm::fmat4;

struct ray {
  fvec3 origin;
  fvec3 dir;
};

#endif /* defined(__rayz__types__) */
