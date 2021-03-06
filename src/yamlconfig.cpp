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

#include "lights/point_light.h"

#include "yamlconfig.h"

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

mat4 parse_lcs(YAML::Node lcs_config);

std::unique_ptr<node> parse_plain_node(YAML::Node node_config) {
  if (!node_config) {
    return nullptr;
  }

  std::unique_ptr<node> parsed_node = nullptr;
  std::unique_ptr<geometry> geom = nullptr;

  geom || (geom = parse_triangle(node_config[1]["triangle"]));
  geom || (geom = parse_cylinder(node_config[1]["cylinder"]));
  geom || (geom = parse_cone(node_config[1]["cone"]));
  geom || (geom = parse_torus(node_config[1]["torus"]));
  geom || (geom = parse_sphere(node_config[1]["sphere"]));
  geom || (geom = parse_obj(node_config[1]["obj_model"]));
  geom || (geom = parse_box(node_config[1]["box"]));
  geom || (geom = parse_plane(node_config[1]["plane"]));

  auto mat = parse_material(node_config[2]["material"]);

  if (geom && mat) {
    geom->set_material(*mat);
    parsed_node = make_unique<plain_node>(std::move(geom));
  }

  if (parsed_node) {
    parsed_node->set_lcs(parse_lcs(node_config[0]["lcs"]));
    for (unsigned long i = 3; i < node_config.size(); ++i) {
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

std::unique_ptr<box> parse_box(YAML::Node box_config) {
  if (!box_config) {
    return nullptr;
  }

  if (!box_config["min"] || !box_config["max"]) {
    return nullptr;
  }

  vec3 min(box_config["min"]["x"].as<num_t>(),
           box_config["min"]["y"].as<num_t>(),
           box_config["min"]["z"].as<num_t>());

  vec3 max(box_config["max"]["x"].as<num_t>(),
           box_config["max"]["y"].as<num_t>(),
           box_config["max"]["z"].as<num_t>());

  return make_unique<box>(min, max);
}

std::unique_ptr<triangle> parse_triangle(YAML::Node triangle_config) {
  if (!triangle_config) {
    return nullptr;
  }

  std::unique_ptr<triangle> parsed_node = nullptr;
  std::array<vec3, 3> args;
  std::array<std::string, 3> keys = { "p0", "p1", "p2" };

  for (unsigned long i = 0; i < args.size(); ++i) {
    auto point_config = triangle_config[keys[i]];
    if (!point_config) {
      return nullptr;
    } else {
      args[i].x = point_config["x"].as<num_t>();
      args[i].y = point_config["y"].as<num_t>();
      args[i].z = point_config["z"].as<num_t>();
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

  return make_unique<cylinder>(cylinder_config["radius"].as<num_t>(),
                               cylinder_config["height"].as<num_t>());
}

std::unique_ptr<cone> parse_cone(YAML::Node cone_config) {
  if (!cone_config) {
    return nullptr;
  }

  if (!cone_config["bottom_radius"] || !cone_config["top_radius"] ||
      !cone_config["height"]) {
    return nullptr;
  }

  return make_unique<cone>(cone_config["bottom_radius"].as<num_t>(),
                           cone_config["top_radius"].as<num_t>(),
                           cone_config["height"].as<num_t>());
}

std::unique_ptr<torus> parse_torus(YAML::Node torus_config) {
  if (!torus_config) {
    return nullptr;
  }

  if (!torus_config["radius"] || !torus_config["tube_radius"]) {
    return nullptr;
  }

  return make_unique<torus>(torus_config["radius"].as<num_t>(),
                            torus_config["tube_radius"].as<num_t>());
}

std::unique_ptr<sphere> parse_sphere(YAML::Node sphere_config) {
  if (!sphere_config) {
    return nullptr;
  }

  if (!sphere_config["radius"]) {
    return nullptr;
  }

  return make_unique<sphere>(sphere_config["radius"].as<num_t>());
}

std::unique_ptr<plane> parse_plane(YAML::Node plane_config) {
  if (!plane_config) {
    return nullptr;
  }

  return make_unique<plane>();
}

std::pair<std::unique_ptr<light>, std::unique_ptr<node> > parse_light(
    YAML::Node light_config) {
  if (!light_config) {
    return { nullptr, nullptr };
  }

  std::pair<std::unique_ptr<light>, std::unique_ptr<node> > parsed_light = {
    nullptr, nullptr
  };

  parsed_light.first ||
      (parsed_light = parse_point_light(light_config["point_light"])).first;

  return parsed_light;
}

std::pair<std::unique_ptr<light>, std::unique_ptr<node> > parse_point_light(
    YAML::Node light_config) {
  if (!light_config) {
    return { nullptr, nullptr };
  }

  if (!light_config["ambient"] || !light_config["diffuse"] ||
      !light_config["specular"] || !light_config["attenuation"] ||
      !light_config["position"]) {
    return { nullptr, nullptr };
  }

  const char *names[3] = { "ambient", "diffuse", "specular" };
  vec4 comps[3];

  for (unsigned i = 0; i < 3; ++i) {
    comps[i].x = light_config[names[i]]["r"].as<num_t>();
    comps[i].y = light_config[names[i]]["g"].as<num_t>();
    comps[i].z = light_config[names[i]]["b"].as<num_t>();
    comps[i].w = light_config[names[i]]["a"].as<num_t>();
  }

  vec3 pos;
  pos.x = light_config["position"]["x"].as<num_t>();
  pos.y = light_config["position"]["y"].as<num_t>();
  pos.z = light_config["position"]["z"].as<num_t>();

  vec3 att;
  att.x = light_config["attenuation"]["x"].as<num_t>();
  att.y = light_config["attenuation"]["y"].as<num_t>();
  att.z = light_config["attenuation"]["z"].as<num_t>();

  material mat;
  mat.amb = color{ 100, 100, 100, 100 };
  mat.diff = color{ 1, 1, 1, 1 };
  mat.emiss = color{ 1, 1, 1, 1 };
  mat.spec = color{ 1, 1, 1, 1 };
  mat.pow = 0.1;

  auto placeholder = make_unique<sphere>(1);
  placeholder->set_material(mat);
  auto rep = make_unique<plain_node>(std::move(placeholder));
  mat4 lcs;
  rep->set_lcs(glm::translate(lcs, pos));
  return { make_unique<point_light>(color(comps[0]), color(comps[1]),
                                    color(comps[2]), rep.get(), att, pos),
           std::move(rep) };
}

std::unique_ptr<material> parse_material(YAML::Node material_config) {
  if (!material_config) {
    return nullptr;
  }

  if (!material_config["ambient"] || !material_config["diffuse"] ||
      !material_config["emissive"] || !material_config["specular"] ||
      !material_config["power"]) {
    return nullptr;
  }

  const char *names[4] = { "ambient", "diffuse", "emissive", "specular" };
  vec4 comps[4];

  for (unsigned i = 0; i < 4; ++i) {
    comps[i].x = material_config[names[i]]["r"].as<num_t>();
    comps[i].y = material_config[names[i]]["g"].as<num_t>();
    comps[i].z = material_config[names[i]]["b"].as<num_t>();
    comps[i].w = material_config[names[i]]["a"].as<num_t>();
  }

  num_t pow = material_config["power"].as<num_t>();

  material mat{ color{ comps[0] }, color{ comps[1] }, color{ comps[2] },
                color{ comps[3] }, pow };

  return make_unique<material>(mat);
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

  std::unique_ptr<node> parsed_node = nullptr;

  parsed_node || (parsed_node = parse_plain_node(node_config["node"]));
  parsed_node || (parsed_node = parse_csg_union(node_config["csg_union"]));
  parsed_node ||
      (parsed_node = parse_csg_intersection(node_config["csg_intersection"]));
  parsed_node ||
      (parsed_node = parse_csg_difference(node_config["csg_difference"]));

  return parsed_node;
}

mat4 parse_lcs(YAML::Node lcs_config) {
  mat4 lcs;
  vec3 t, r, s;

  if (!lcs_config) {
    return lcs;
  }

  t.x = lcs_config["x"].as<num_t>();
  t.y = lcs_config["y"].as<num_t>();
  t.z = lcs_config["z"].as<num_t>();

  r.x = glm::radians(lcs_config["h"].as<num_t>());
  r.y = glm::radians(lcs_config["p"].as<num_t>());
  r.z = glm::radians(lcs_config["r"].as<num_t>());

  s.x = lcs_config["sx"].as<num_t>();
  s.y = lcs_config["sy"].as<num_t>();
  s.z = lcs_config["sz"].as<num_t>();

  lcs = glm::translate(lcs, t) * glm::eulerAngleYXZ(r.x, r.y, r.z) *
        glm::scale(lcs, s);

  return lcs;
}

std::unique_ptr<camera> parse_camera(YAML::Node camera_config) {
  vec3 pos, orient;
  num_t fovx = 0, fovy = 0;

  if (!camera_config) {
    return nullptr;
  }

  auto position_config = camera_config["position"];
  if (!position_config) {
    return nullptr;
  } else {
    pos.x = position_config["x"].as<num_t>();
    pos.y = position_config["y"].as<num_t>();
    pos.z = position_config["z"].as<num_t>();
  }

  auto orient_config = camera_config["orientation"];
  if (!orient_config) {
    return nullptr;
  } else {
    orient.x = orient_config["h"].as<num_t>();
    orient.y = orient_config["p"].as<num_t>();
    orient.z = orient_config["r"].as<num_t>();
  }

  auto fx_config = camera_config["fov_x"];
  if (!fx_config) {
    return nullptr;
  } else {
    fovx = fx_config.as<num_t>();
  }

  auto fy_config = camera_config["fov_y"];
  if (!fy_config) {
    return nullptr;
  } else {
    fovy = fy_config.as<num_t>();
  }

  return make_unique<camera>(pos, fovx, fovy, orient.x, orient.y, orient.z);
}
