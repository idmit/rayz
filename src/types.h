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

using dvec3 = glm::dvec3;
using dmat4 = glm::dmat4;

struct ray {
  dvec3 origin;
  dvec3 dir;
};

#endif /* defined(__rayz__types__) */
