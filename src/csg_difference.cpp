//
//  csg_difference.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 18/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "csg_difference.h"

csg_deifference::csg_deifference(std::unique_ptr<node> &&lhs,
                                 std::unique_ptr<node> &&rhs)
    : _lhs(std::move(lhs)), _rhs(std::move(rhs)){};

bool csg_deifference::intersect(ray ray, dvec3 *close_intersection_point,
                                dvec3 *far_intersection_point,
                                std::pair<double, double> *param_vals) const {
  bool li, ri;
  std::pair<dvec3, dvec3> lpoints, rpoints;
  std::pair<double, double> lparams, rparams;

  li = _lhs->intersect(ray, &lpoints.first, &lpoints.second, &lparams);
  ri = _rhs->intersect(ray, &rpoints.first, &rpoints.second, &rparams);

  if (!li || !ri) {
    return false;
  }

  std::pair<dvec3, dvec3> small = rpoints, big = lpoints;
  std::pair<double, double> small_pms = rparams, big_pms = lparams;

  if (lparams.second - lparams.first < rparams.second - rparams.first) {
    small = lpoints;
    big = rpoints;
    small_pms = lparams;
    big_pms = rparams;
  }

  if (small_pms.second < big_pms.first || big_pms.second < small_pms.first) {
    return false;
  }

  if (small_pms.first < big_pms.first) {
    *close_intersection_point = big.first;
    if (far_intersection_point) {
      *far_intersection_point = small.second;
    }
    if (param_vals) {
      param_vals->first = big_pms.first;
      param_vals->second = small_pms.second;
    }
    return true;
  }

  if (big_pms.first < small_pms.first && small_pms.second < big_pms.second) {
    *close_intersection_point = small.first;
    if (far_intersection_point) {
      *far_intersection_point = small.second;
    }
    if (param_vals) {
      param_vals->first = small_pms.first;
      param_vals->second = small_pms.second;
    }
    return true;
  }

  if (big_pms.first < small_pms.first && big_pms.second < small_pms.second) {
    *close_intersection_point = small.first;
    if (far_intersection_point) {
      *far_intersection_point = big.second;
    }
    if (param_vals) {
      param_vals->first = small_pms.first;
      param_vals->second = big_pms.second;
    }
    return true;
  }

  return true;
}

double csg_deifference::get_color(dvec3 intersectionPoint) const { return 0; }

dvec3 csg_deifference::get_normal(dvec3 point) const { return { 0, 0, 0 }; }
