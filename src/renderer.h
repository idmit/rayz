//
//  renderer.h
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__renderer__
#define __rayz__renderer__

#include "png++/png.hpp"
#include "scene.h"

class renderer {
public:
  png::image<png::rgb_pixel> run(const scene& scene, unsigned long resX,
                                 unsigned long resY);
};

#endif /* defined(__rayz__renderer__) */
