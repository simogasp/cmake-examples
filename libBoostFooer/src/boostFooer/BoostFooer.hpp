#pragma once

#include <iostream> // std::cout
#include <fooer/Fooer.hpp>
#include <boost_fooer_export.h>

namespace boostFooer {

class BoostFooer {
 public:
  static void say() {
    foo::Bar::say();
#if (BOOSTERFOOER_DEBUG)
    const char* m = "BoostFooer.hpp (Debug)";
#else
    const char* m = "BoostFooer.hpp (Not debug)";
#endif
    std::cout << m << std::endl;
    cpp_say();
  }

 private:
  static void cpp_say();
};

}


