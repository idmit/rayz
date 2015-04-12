//
//  sphere.h
//  rayz
//
//  Created by Иван Дмитриевский on 12/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__sphere__
#define __rayz__sphere__

#include "object.h"

class Sphere : public Object {
public:
  virtual bool intersect(const fvec3 rayStartPoint, const fvec3 ray,
                         fvec3 intersectionPoint) override;

  virtual float getColor(fvec3 intersectionPoint) override;

  virtual fvec3 getNormal(fvec3 intersectionPoint) override;

private:
  fvec3 pos;
  float rad;
};

#endif /* defined(__rayz__sphere__) */
