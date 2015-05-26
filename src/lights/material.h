//
//  material.h
//  rayz
//
//  Created by Иван Дмитриевский on 23/05/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef rayz_material_h
#define rayz_material_h

#include "color.h"

struct material {
  color amb;
  color diff;
  color emiss;
  color spec;
  num_t pow;
};

#endif
