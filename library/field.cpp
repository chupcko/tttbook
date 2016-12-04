#include "tttbook.hpp"

namespace tttbook
{

  std::ostream& operator<< (std::ostream& out, const field_c& self)
  {
    switch(self.value)
    {
      case field_c::FIELD_EMPTY:
        out << ' ';
        break;
      case field_c::FIELD_X:
        out << 'x';
        break;
      case field_c::FIELD_O:
        out << 'o';
        break;
    }
    return out;
  }

}
