//
//  plain_node.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 18/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "plain_node.h"

void transform(dmat4 t, dvec3 *v) { *v = dvec3(t * glm::dvec4(*v, 1)); }
dvec3 transform(dmat4 t, dvec3 v) { return dvec3(t * glm::dvec4(v, 1)); }

plain_node::plain_node(std::unique_ptr<geometry> &&geom)
    : _geom(std::move(geom)){};

bool plain_node::intersect(ray parent_ray, dvec3 *close_intersection_point,
                           dvec3 *far_intersection_point,
                           std::pair<double, double> *param_vals) const {
  dmat4 to_parent_transform = _lcs;
  dmat4 to_node_transform = glm::inverse(to_parent_transform);

  ray lcs_ray;

  lcs_ray.origin = transform(to_node_transform, parent_ray.origin);
  lcs_ray.dir = glm::normalize(glm::dmat3(to_node_transform) * parent_ray.dir);

  bool intersected = false;
  std::pair<double, double> lparam_vals;
  double min_dist = INFINITY;
  if (_geom->intersect(lcs_ray, close_intersection_point,
                       far_intersection_point, &lparam_vals)) {
    transform(to_parent_transform, close_intersection_point);
    if (far_intersection_point) {
      transform(to_parent_transform, far_intersection_point);
    }

    min_dist = lparam_vals.first;
    intersected = true;
  }

  for (auto &child : _children) {
    bool child_intersected = false;
    dvec3 close_child_point, far_child_point;
    child_intersected = child->intersect(lcs_ray, &close_child_point,
                                         &far_child_point, &lparam_vals);
    transform(to_parent_transform, &close_child_point);
    transform(to_parent_transform, &far_child_point);
    if (child_intersected) {
      intersected = true;
      if (lparam_vals.first < min_dist) {
        *close_intersection_point = close_child_point;
        if (far_intersection_point) {
          transform(to_parent_transform, far_child_point);
        }
        min_dist = lparam_vals.first;
      }
    }
  }

  if (param_vals) {
    *param_vals = lparam_vals;
    param_vals->first = min_dist;
  }

  return intersected;
}

double plain_node::get_color(dvec3 point) const {
  return _geom->get_color(point);
}

dvec3 plain_node::get_normal(dvec3 point) const {
  return _geom->get_normal(point);
}
