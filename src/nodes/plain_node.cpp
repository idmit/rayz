//
//  plain_node.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 18/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "plain_node.h"

void transform_point(const mat4 &t, vec3 *v) {
  *v = vec3(t * glm::dvec4(*v, 1));
}

geometry::ray_path transform_point(mat4 t, ray pr, ray lr,
                                   geometry::ray_path list) {
  geometry::ray_path out_list;

  for (const auto &p : list) {
    auto dir =
        vec3(t * glm::dvec4(lr.origin + lr.dir * p.first, 1)) - pr.origin;
    for (unsigned i = 0; i < 3; ++i) {
      if (dir[i] != 0) {
        out_list.push_back({ dir[i] / pr.dir[i], p.second });
        break;
      }
    }
  }

  return out_list;
}

vec3 transform_point(const mat4 &t, vec3 v) {
  return vec3(t * glm::dvec4(v, 1));
}

vec3 transform_vec(const mat4 &t, vec3 v) { return vec3(t * glm::dvec4(v, 0)); }

plain_node::plain_node(std::unique_ptr<geometry> &&geom)
    : _geom(std::move(geom)) {}

geometry::ray_path plain_node::intersect(ray parent_ray) const {
  mat4 to_parent_transform = _lcs;
  mat4 to_node_transform = _ilcs;

  ray lcs_ray;

  lcs_ray.origin = transform_point(to_node_transform, parent_ray.origin);
  lcs_ray.dir = glm::normalize(glm::dmat3(to_node_transform) * parent_ray.dir);

  std::pair<num_t, num_t> lparam_vals;
  auto list = _geom->intersect(lcs_ray);
  list = transform_point(to_parent_transform, parent_ray, lcs_ray, list);

  for (auto &child : _children) {
    auto child_list = child->intersect(lcs_ray);
    child_list =
        transform_point(to_parent_transform, parent_ray, lcs_ray, child_list);
    for (const auto &pair : child_list) {
      list.push_back(pair);
    }
  }
  list.sort();

  return list;
}

color plain_node::get_color(const vec3 &point) const {
  return color{ 0, 0, 0, 0 };
}

vec3 plain_node::get_normal(const vec3 &point) const {
  return transform_vec(_tlcs, _geom->get_normal(transform_point(_ilcs, point)));
}

material plain_node::get_material() const { return _geom->get_material(); }
