//
//  scene.h
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__scene__
#define __rayz__scene__

#include <memory>
#include <vector>
#include "nodes/node.h"
#include "camera.h"

class camera;

class scene {
public:
  static std::unique_ptr<camera> create(std::string scene_desc, scene* scene);
  std::vector<const node*> nodes() const;

private:
  std::vector<std::unique_ptr<node> > _nodes;
};

#endif /* defined(__rayz__scene__) */
