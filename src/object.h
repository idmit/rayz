//
//  object.h
//  rayz
//
//  Created by Иван Дмитриевский on 12/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__object__
#define __rayz__object__

#include "types.h"

class Object {
public:
  virtual bool intersect(const fvec3 rayStartPoint, const fvec3 ray,
                         fvec3 intersectionPoint) = 0;

  virtual float getColor(fvec3 intersectionPoint) = 0;

  virtual fvec3 getNormal(fvec3 intersectionPoint) = 0;
};

#endif /* defined(__rayz__object__) */
