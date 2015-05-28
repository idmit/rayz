//
//  light.cpp
//  rayz
//
//  Created by Иван Дмитриевский on 26/05/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#include "light.h"

light::light() : _enabled(false) {}
light::light(color amb, color diff, color spec, const node *rep)
    : _comps({ amb, diff, spec }), rep(rep) {}
light::~light() {}

void light::enable() { _enabled = true; }

void light::disable() { _enabled = false; }

void light::set_state(bool state) { _enabled = state; }

bool light::get_state(void) const { return _enabled; }

void light::set_ambient(const color &ambient) { _comps.amb = ambient; }

void light::set_diffuse(const color &diffuse) { _comps.diff = diffuse; }

void light::set_specular(const color &specular) { _comps.spec = specular; }

color light::get_ambient() const { return _comps.amb; }

color light::get_diffuse() const { return _comps.diff; }

color light::get_specular() const { return _comps.spec; }
