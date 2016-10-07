#include <fooer/Fooer.hpp>

namespace fooer {

void Fooer::cpp_say() {
#ifdef FOOER_BAR_DEBUG
  const char* m = "Fooer.cpp (Debug)";
#else
  const char* m = "Fooer.cpp (Not debug)";
#endif
  std::cout << m << std::endl;
}

} // namespace fooer
