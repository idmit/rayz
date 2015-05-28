//
//  geometry.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 28/05/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "geometry.h"

void geometry::set_material(const material &mat) { _material = mat; }

geometry::~geometry() {}
