#pragma once

#include <fooer_export.h>
#include <fooer_config.hpp>
#include <iostream> // std::cout
#include <foo/Bar.hpp>


namespace fooer {

class FOOER_EXPORT Fooer {
 public:
  static void say() {
    foo::Bar::say();
#ifdef FOOER_BAR_DEBUG
    const char* m = "Fooer.hpp (Debug)";
#else
    const char* m = "Fooer.hpp (Not debug)";
#endif
    std::cout << m << std::endl;
    cpp_say();
  }

 private:
  static void cpp_say();
};

}


