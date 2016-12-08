#include "tttbook.hpp"

namespace tttbook
{

  std::ostream& operator<<(std::ostream& out, const move_c& self)
  {
    out << '(' << self.x << ", " << self.y << ')';
    return out;
  }

}
