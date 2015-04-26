//
//  yamlconfig.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 14/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/transform.hpp"

#include "nodes/plain_node.h"
#include "nodes/csg_union.h"
#include "nodes/csg_intersection.h"
#include "nodes/csg_difference.h"

#include "yamlconfig.h"

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

dmat4 parse_lcs(YAML::Node lcs_config);

std::unique_ptr<node> parse_plain_node(YAML::Node node_config) {
  std::unique_ptr<node> parsed_node = nullptr;
  std::unique_ptr<geometry> geom = nullptr;

  geom || (geom = parse_triangle(node_config[1]["triangle"]));
  geom || (geom = parse_cylinder(node_config[1]["cylinder"]));
  geom || (geom = parse_cone(node_config[1]["cone"]));
  geom || (geom = parse_torus(node_config[1]["torus"]));
  geom || (geom = parse_sphere(node_config[1]["sphere"]));
  geom || (geom = parse_obj(node_config[1]["obj_model"]));

  !geom || (parsed_node = make_unique<plain_node>(std::move(geom)));

  if (parsed_node) {
    parsed_node->set_lcs(parse_lcs(node_config[0]["lcs"]));
    for (unsigned long i = 2; i < node_config.size(); ++i) {
      auto child = std::move(parse_node(node_config[i]));
      if (child) {
        parsed_node->add_child(std::move(child));
      }
    }
  }

  return parsed_node;
}

std::unique_ptr<obj> parse_obj(YAML::Node obj_config) {
  if (!obj_config) {
    return nullptr;
  }

  if (!obj_config["file_name"]) {
    return nullptr;
  }

  return make_unique<obj>(obj_config["file_name"].as<std::string>().c_str());
}

std::unique_ptr<triangle> parse_triangle(YAML::Node triangle_config) {
  if (!triangle_config) {
    return nullptr;
  }

  std::unique_ptr<triangle> parsed_node = nullptr;
  std::array<dvec3, 3> args;
  std::array<std::string, 3> keys = { "p0", "p1", "p2" };

  for (unsigned long i = 0; i < args.size(); ++i) {
    auto point_config = triangle_config[keys[i]];
    if (!point_config) {
      return nullptr;
    } else {
      args[i].x = point_config["x"].as<double>();
      args[i].y = point_config["y"].as<double>();
      args[i].z = point_config["z"].as<double>();
    }
  }

  return make_unique<triangle>(args);
}

std::unique_ptr<cylinder> parse_cylinder(YAML::Node cylinder_config) {
  if (!cylinder_config) {
    return nullptr;
  }

  if (!cylinder_config["radius"] || !cylinder_config["height"]) {
    return nullptr;
  }

  return make_unique<cylinder>(cylinder_config["radius"].as<double>(),
                               cylinder_config["height"].as<double>());
}

std::unique_ptr<cone> parse_cone(YAML::Node cone_config) {
  if (!cone_config) {
    return nullptr;
  }

  if (!cone_config["bottom_radius"] || !cone_config["top_radius"] ||
      !cone_config["height"]) {
    return nullptr;
  }

  return make_unique<cone>(cone_config["bottom_radius"].as<double>(),
                           cone_config["top_radius"].as<double>(),
                           cone_config["height"].as<double>());
}

std::unique_ptr<torus> parse_torus(YAML::Node torus_config) {
  if (!torus_config) {
    return nullptr;
  }

  if (!torus_config["radius"] || !torus_config["tube_radius"]) {
    return nullptr;
  }

  return make_unique<torus>(torus_config["radius"].as<double>(),
                            torus_config["tube_radius"].as<double>());
}

std::unique_ptr<sphere> parse_sphere(YAML::Node sphere_config) {
  if (!sphere_config) {
    return nullptr;
  }

  if (!sphere_config["radius"]) {
    return nullptr;
  }

  return make_unique<sphere>(sphere_config["radius"].as<double>());
}

std::unique_ptr<node> parse_csg_intersection(YAML::Node csg_config) {
  if (!csg_config) {
    return nullptr;
  }

  if (!csg_config["left_node"] || !csg_config["right_node"]) {
    return nullptr;
  }

  return make_unique<csg_intersection>(
      std::move(parse_node(csg_config["left_node"])),
      std::move(parse_node(csg_config["right_node"])));
}

std::unique_ptr<node> parse_csg_union(YAML::Node csg_config) {
  if (!csg_config) {
    return nullptr;
  }

  if (!csg_config["left_node"] || !csg_config["right_node"]) {
    return nullptr;
  }

  return make_unique<csg_union>(
      std::move(parse_node(csg_config["left_node"])),
      std::move(parse_node(csg_config["right_node"])));
}

std::unique_ptr<node> parse_csg_difference(YAML::Node csg_config) {
  if (!csg_config) {
    return nullptr;
  }

  if (!csg_config["left_node"] || !csg_config["right_node"]) {
    return nullptr;
  }

  return make_unique<csg_difference>(
      std::move(parse_node(csg_config["left_node"])),
      std::move(parse_node(csg_config["right_node"])));
}

std::unique_ptr<node> parse_node(YAML::Node node_config) {
  if (!node_config) {
    return nullptr;
  }

  if (node_config["node"]) {
    return parse_plain_node(node_config["node"]);
  } else if (node_config["csg_union"]) {
    return parse_csg_union(node_config["csg_union"]);
  } else if (node_config["csg_intersection"]) {
    return parse_csg_intersection(node_config["csg_intersection"]);
  } else if (node_config["csg_difference"]) {
    return parse_csg_difference(node_config["csg_difference"]);
  }

  return nullptr;
}

dmat4 parse_lcs(YAML::Node lcs_config) {
  dmat4 lcs;
  dvec3 t, r, s;

  if (!lcs_config) {
    return lcs;
  }

  t.x = lcs_config["x"].as<double>();
  t.y = lcs_config["y"].as<double>();
  t.z = lcs_config["z"].as<double>();

  r.x = glm::radians(lcs_config["h"].as<double>());
  r.y = glm::radians(lcs_config["p"].as<double>());
  r.z = glm::radians(lcs_config["r"].as<double>());

  s.x = lcs_config["sx"].as<double>();
  s.y = lcs_config["sy"].as<double>();
  s.z = lcs_config["sz"].as<double>();

  lcs =
      glm::scale(glm::translate(lcs, t), s) * glm::eulerAngleYXZ(r.x, r.y, r.z);

  return lcs;
}

std::unique_ptr<camera> parse_camera(YAML::Node camera_config) {
  dvec3 pos, orient;
  double fovx = 0, fovy = 0;

  if (!camera_config) {
    return nullptr;
  }

  auto position_config = camera_config["position"];
  if (!position_config) {
    return nullptr;
  } else {
    pos.x = position_config["x"].as<double>();
    pos.y = position_config["y"].as<double>();
    pos.z = position_config["z"].as<double>();
  }

  auto orient_config = camera_config["orientation"];
  if (!orient_config) {
    return nullptr;
  } else {
    orient.x = orient_config["h"].as<double>();
    orient.y = orient_config["p"].as<double>();
    orient.z = orient_config["r"].as<double>();
  }

  auto fx_config = camera_config["fov_x"];
  if (!fx_config) {
    return nullptr;
  } else {
    fovx = fx_config.as<double>();
  }

  auto fy_config = camera_config["fov_y"];
  if (!fy_config) {
    return nullptr;
  } else {
    fovy = fy_config.as<double>();
  }

  return make_unique<camera>(pos, fovx, fovy, orient.x, orient.y, orient.z);
}
