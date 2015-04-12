//
//  opts.h
//  rayz
//
//  Created by Иван Дмитриевский on 11/04/15.
//  Copyright (c) 2015 Ivan Dmitrievsky. All rights reserved.
//

#ifndef rayz_opts_h
#define rayz_opts_h

#include <string>

#include "optionparser.h"

namespace opts {
enum index { UNKNOWN, HELP, SCENE, RESX, RESY, OUTPUT, DEPTH };
const option::Descriptor usage[] = {
  { UNKNOWN, 0, "", "", option::Arg::None, "USAGE: rayz options\n\n"
                                           "Options:" },
  { HELP, 0, "h", "help", option::Arg::None,
    "  --help, -h \tPrint usage and exit." },
  { SCENE, 0, "", "scene", option::Arg::Optional,
    "  --scene  \tScene description." },
  { RESX, 0, "", "resolution_x", option::Arg::Optional,
    "  --resolution_x  \tX resolution for output image." },
  { RESY, 0, "", "resolution_y", option::Arg::Optional,
    "  --resolution_y  \tY resolution for output image." },
  { OUTPUT, 0, "", "output", option::Arg::Optional,
    "  --output  \tOutput image." },
  { DEPTH, 0, "", "trace_depth", option::Arg::Optional,
    "  --trace_depth  \tTrace depth." },
  { 0, 0, 0, 0, 0, 0 }

};

bool get(int argc, const char* argv[], std::string* sceneDesc,
         unsigned long* resX, unsigned long* resY, std::string* outputImg,
         unsigned long* traceDepth) {
  argc -= (argc > 0);
  argv += (argc > 0);
  option::Stats stats(opts::usage, argc, argv);
  option::Option* options = new option::Option[stats.options_max],
                  * buffer = new option::Option[stats.buffer_max];
  option::Parser parse(opts::usage, argc, argv, options, buffer);

  if (parse.error())
    return false;

  if (options[opts::HELP] || argc == 0) {
    option::printUsage(std::cout, opts::usage);
    return false;
  }

  if (options[opts::SCENE] && options[opts::RESX] && options[opts::RESY] &&
      options[opts::OUTPUT] && options[opts::DEPTH]) {
  } else {
    printf("%s\n", "Insufficient options, see --help for usage.");
    return false;
  }

  if (options[opts::SCENE].arg && options[opts::RESX].arg &&
      options[opts::RESY].arg && options[opts::OUTPUT].arg &&
      options[opts::DEPTH].arg) {
  } else {
    printf("%s\n", "Insufficient arguments, see --help for usage.");
    return false;
  }

  *sceneDesc = options[opts::SCENE].arg;
  *resX = std::stoul(options[opts::RESX].arg);
  *resY = std::stoul(options[opts::RESY].arg);
  *outputImg = options[opts::OUTPUT].arg;
  *traceDepth = std::stoul(options[opts::DEPTH].arg);

  delete[] options;
  delete[] buffer;

  return true;
}
}

#endif
