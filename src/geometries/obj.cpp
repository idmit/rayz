//
//  obj.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 25/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "obj.h"
#include "tinyobjloader/tiny_obj_loader.h"

obj::obj(const char *filename) {

  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  auto err = tinyobj::LoadObj(shapes, materials, "bunny.obj");

  if (!err.empty()) {
    printf("%s\n", err.c_str());
  }

  for (size_t i = 0; i < shapes.size(); ++i) {
    for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; ++f) {
      std::array<dvec3, 3> triplet;
      for (int k = 0; k < 3; ++k) {
        size_t idx = 3 * f + k;

        triplet[k] = { shapes[i].mesh.positions[3 * idx + 0],
                       shapes[i].mesh.positions[3 * idx + 1],
                       shapes[i].mesh.positions[3 * idx + 2] };
      }
      _triangles.emplace_back(triplet);

      for (int k = 0; k < 3; ++k) {
        _min = glm::min(_min, triplet[k]);
        _max = glm::max(triplet[k], _max);
      };
    }
  }
}

geometry::ray_path obj::intersect(ray ray) const {
  ray_path list;

  for (const auto &tri : _triangles) {
    for (const auto &point : tri.intersect(ray)) {
      list.push_back(point);
    }
  }

  list.sort();

  return list;
}

double obj::get_color(dvec3 point) const { return 0; }

dvec3 obj::get_normal(dvec3 point) const { return glm::normalize(point); }
