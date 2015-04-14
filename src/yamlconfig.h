//
//  yamlconfig.h
//  rayz
//
//  Created by Иван Дмитриевский on 14/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef __rayz__yamlconfig__
#define __rayz__yamlconfig__

#include <memory>
#include "node.h"

#include "yaml-cpp/yaml.h"

#include "triangle.h"
#include "cylinder.h"
#include "torus.h"
#include "sphere.h"

std::unique_ptr<node> parse_node(YAML::Node node_config);
std::unique_ptr<triangle> parse_triangle(YAML::Node node_config);
std::unique_ptr<cylinder> parse_cylinder(YAML::Node cylinder_config);
std::unique_ptr<torus> parse_torus(YAML::Node torus_config);
std::unique_ptr<sphere> parse_sphere(YAML::Node sphere_config);

#endif /* defined(__rayz__yamlconfig__) */
