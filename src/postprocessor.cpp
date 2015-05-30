//
//  postprocessor.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 30/05/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "postprocessor.h"
#include "types.h"
#include <cmath>

bitmap_image postprocessor::map_tone(
    const std::vector<std::vector<color> > &image) {

  num_t Ldmax = 220;
  num_t Lwmax[] = { 0, 0, 0 };
  num_t b = 0.85;

  bitmap_image result((unsigned)image[0].size(), (unsigned)image.size());

  for (unsigned i = 0; i < image.size(); ++i) {
    for (unsigned j = 0; j < image[i].size(); ++j) {
      num_t tmp[] = { 0, 0, 0 };
      tmp[0] = image[i][j].rgba.x;
      tmp[1] = image[i][j].rgba.y;
      tmp[2] = image[i][j].rgba.z;

      for (unsigned k = 0; k < 3; ++k) {
        if (Lwmax[k] < tmp[k]) {
          Lwmax[k] = tmp[k];
        }
      }
    }
  }

  for (unsigned i = 0; i < image.size(); ++i) {
    for (unsigned j = 0; j < image[i].size(); ++j) {
      num_t tmp[] = { 0, 0, 0 };
      num_t res[] = { 0, 0, 0 };
      tmp[0] = image[i][j].rgba.x;
      tmp[1] = image[i][j].rgba.y;
      tmp[2] = image[i][j].rgba.z;

      for (unsigned k = 0; k < 3; ++k) {
        res[k] = Ldmax * 0.01 / std::log10(Lwmax[k] + 1);
        res[k] *= std::log10(tmp[k] + 1);
        res[k] /= std::log(
            2 + 8 * std::pow(tmp[k] / Lwmax[k], std::log(b) / std::log(0.5)));
      }

      color t{ res[0], res[1], res[2], 0 };

      result.set_pixel(j, i, t.r(), t.g(), t.b());
    }
  }

  return result;
}
