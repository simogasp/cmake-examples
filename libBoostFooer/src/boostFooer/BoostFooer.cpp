#include <boostFooer/BoostFooer.hpp>
#include <boost/filesystem.hpp>

namespace fooer {

void BoostFooer::cpp_say() 
{
  boost::filesystem::path p("/usr/bin");
#if (BOOSTERFOOER_DEBUG)
  const char* m = "BoostFooer.cpp (Debug)";
#else
  const char* m = "BoostFooer.cpp (Not debug)";
#endif
  std::cout << m << std::endl;
  std::cout << p << std::endl;
}

} // namespace fooer
