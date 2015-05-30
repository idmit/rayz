//
//  postprocessor.h
//  rayz
//
//  Created by Иван Дмитриевский on 30/05/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__postprocessor__
#define __rayz__postprocessor__

#include "bitmap_image.hpp"
#include <vector>
#include "lights/color.h"

class postprocessor {
public:
  static bitmap_image map_tone(const std::vector<std::vector<color> > &image);
};

#endif /* defined(__rayz__postprocessor__) */
