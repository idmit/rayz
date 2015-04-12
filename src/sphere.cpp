//
//  sphere.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 12/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "sphere.h"

bool Sphere::intersect(const fvec3 rayStartPoint, const fvec3 ray,
                       fvec3 intersectionPoint) {
  return 0;
}

float Sphere::getColor(fvec3 intersectionPoint) { return 0; }

fvec3 Sphere::getNormal(fvec3 intersectionPoint) {
  fvec3 n(intersectionPoint - pos);
  glm::normalize(n);
  return n;
}
