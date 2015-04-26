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
#include "yaml-cpp/yaml.h"

#include "camera.h"

#include "geometries/triangle.h"
#include "geometries/cylinder.h"
#include "geometries/cone.h"
#include "geometries/torus.h"
#include "geometries/obj.h"
#include "geometries/sphere.h"

std::unique_ptr<node> parse_plain_node(YAML::Node node_config);
std::unique_ptr<node> parse_csg_intersection(YAML::Node csg_config);
std::unique_ptr<node> parse_csg_union(YAML::Node csg_config);
std::unique_ptr<node> parse_csg_difference(YAML::Node csg_config);
std::unique_ptr<node> parse_node(YAML::Node node_config);
std::unique_ptr<triangle> parse_triangle(YAML::Node node_config);
std::unique_ptr<cylinder> parse_cylinder(YAML::Node cylinder_config);
std::unique_ptr<cone> parse_cone(YAML::Node cone_config);
std::unique_ptr<torus> parse_torus(YAML::Node torus_config);
std::unique_ptr<sphere> parse_sphere(YAML::Node sphere_config);
std::unique_ptr<obj> parse_obj(YAML::Node obj_config);

std::unique_ptr<camera> parse_camera(YAML::Node camera_config);

#endif /* defined(__rayz__yamlconfig__) */
