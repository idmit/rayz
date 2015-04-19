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

std::unique_ptr<camera> scene::create(std::string scene_desc, scene* scene) {
  YAML::Node scene_config = YAML::LoadFile(scene_desc);

  for (unsigned long i = 1; i < scene_config.size(); ++i) {
    if (scene_config[i]["node"]) {
      auto node = parse_plain_node(scene_config[i]["node"]);
      if (node) {
        scene->_nodes.emplace_back(std::move(node));
      }

    } else if (scene_config[i]["csg_intersection"]) {
      auto node = parse_plain_node(scene_config[i]["csg_intersection"]);
      if (node) {
        scene->_nodes.emplace_back(std::move(node));
      }
    } else if (scene_config[i]["csg_union"]) {
      auto node = parse_plain_node(scene_config[i]["csg_union"]);
      if (node) {
        scene->_nodes.emplace_back(std::move(node));
      }
    }
  }

  return parse_camera(scene_config[0]["camera"]);
}

std::vector<const node*> scene::nodes() const {
  std::vector<const node*> nodes;
  for (auto& pointer : _nodes) {
    const node* const v = pointer.get();
    nodes.push_back(v);
  }
  return nodes;
}
