//
//  camera.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 14/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "camera.h"
#include "glm/gtx/rotate_vector.hpp"

camera::camera(const vec3 &pos, num_t fovx, num_t fovy, const vec3 &lookat)
    : _eye(pos),
      _lookat(lookat),
      _up({ 0, 0, 1 }),
      _w(glm::normalize(_eye - _lookat)),
      _u(glm::normalize(glm::cross(_up, _w))),
      _v(glm::cross(_w, _u)),
      _dist(1),
      _fovx(fovx),
      _fovy(fovy) {}

camera::camera(const vec3 &pos, num_t fovx, num_t fovy, num_t heading,
               num_t pitch, num_t roll)
    : camera(pos, fovx, fovy, pos + vec3(0, 1, 0)) {

  num_t dist = glm::distance(_lookat, _eye);

  _w = glm::rotate(_w, -glm::radians(heading), _v);
  _u = glm::rotate(_u, -glm::radians(heading), _v);

  _w = glm::rotate(_w, glm::radians(pitch), _u);
  _v = glm::rotate(_v, glm::radians(pitch), _u);

  _u = glm::rotate(_u, -glm::radians(roll), _w); //
  _v = glm::rotate(_v, -glm::radians(roll), _w); //

  _lookat = _eye - _w * dist;
}

bitmap_image camera::render(const scene &scene, long resX, long resY) {
  bitmap_image img(static_cast<unsigned>(resX), static_cast<unsigned>(resY));
  std::vector<std::vector<color> > closest_points(
      resY, std::vector<color>(resX, color{}));

  num_t pxw = 2 * _dist * glm::tan(glm::radians(_fovx / 2)) / resX;
  num_t pxh = 2 * _dist * glm::tan(glm::radians(_fovy / 2)) / resY;

  num_t x = -(resX * pxw / 2);
  num_t y = -(resY * pxh / 2);

  for (long i = resY - 1; i >= 0; --i) {
    for (long j = 0; j < resX; ++j) {
      const node *id = nullptr;
      num_t distance = INFINITY;
      vec3 id_point;

      if (i == 480 && j == 435) {
        printf("");
      }

      for (auto &node : scene.nodes()) {
        ray world_ray;
        world_ray.origin = _eye;
        world_ray.dir = glm::normalize(x * _u + y * _v - _dist * _w);

        vec3 closest_point;
        auto intersected = node->intersect(world_ray);
        if (!intersected.empty()) {
          closest_point =
              world_ray.origin + world_ray.dir * intersected.front().first;

          if (glm::distance(_eye, closest_point) < distance) {
            distance = glm::distance(_eye, closest_point);
            id = node;
            id_point = closest_point;
          }
        }
      }

      if (id) {
        for (auto &light : scene.lights()) {

          vec3 norm = glm::normalize(id->get_normal(id_point));
          material material = id->get_material();

          vec3 vtoe = glm::normalize(_eye - id_point);
          vec3 vtol = glm::normalize(light->get_dir(id_point));

          num_t d = glm::max(glm::dot(vtol, norm), 0.0);
          num_t s = 0;
          if (d > 0) {
            s = glm::pow(
                glm::max(glm::dot(norm, glm::normalize(vtoe + vtol)), 0.0),
                material.pow);
          }

          vec4 amb = material.amb.rgba * light->get_ambient().rgba;
          vec4 diff = d * (material.diff.rgba * light->get_diffuse().rgba);
          vec4 spec = s * (material.spec.rgba * light->get_specular().rgba);

          num_t dis = light->get_dist(id_point);
          num_t alpha = light->get_att().x + light->get_att().y * dis +
                        light->get_att().z * dis * dis;

          color out{ (amb + diff + spec) / alpha };
          closest_points[i][j].rgba =
              glm::clamp(closest_points[i][j].rgba + out.rgba, 0.0, 1.0);
        }
      }
      x += pxw;
    }
    x = -(resX * pxw / 2);
    y += pxh;
  }

  for (unsigned i = 0; i < resY; ++i) {
    for (unsigned j = 0; j < resX; ++j) {
      img.set_pixel(j, i, closest_points[i][j].r(), closest_points[i][j].g(),
                    closest_points[i][j].b());
    }
  }

  return img;
}
