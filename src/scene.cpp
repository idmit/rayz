//
//  scene.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 13/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "yaml-cpp/yaml.h"

#include "scene.h"
#include "yamlconfig.h"

std::unique_ptr<camera> scene::create(std::string scene_desc, scene *scene) {
  YAML::Node scene_config = YAML::LoadFile(scene_desc);

  for (unsigned long i = 1; i < scene_config.size(); ++i) {
    auto node = parse_node(scene_config[i]);
    if (node) {
      scene->_nodes.emplace_back(std::move(node));
      continue;
    }

    auto pair = parse_light(scene_config[i]);
    if (pair.first) {
      scene->_lights.emplace_back(std::move(pair.first));
      scene->_nodes.emplace_back(std::move(pair.second));
    }
  }
  return parse_camera(scene_config[0]["camera"]);
}

std::vector<const node *> scene::nodes() const {
  std::vector<const node *> nodes;
  for (auto &pointer : _nodes) {
    const node *const v = pointer.get();
    nodes.push_back(v);
  }
  return nodes;
}

std::vector<const light *> scene::lights() const {
  std::vector<const light *> lights;
  for (auto &pointer : _lights) {
    const light *const v = pointer.get();
    lights.push_back(v);
  }
  return lights;
}
