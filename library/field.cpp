#include "tttbook.hpp"

namespace tttbook
{

  std::ostream& operator<< (std::ostream& out, const field& self)
  {
    switch(self.value)
    {
      case field::FIELD_EMPTY:
        out << ' ';
        break;
      case field::FIELD_X:
        out << 'x';
        break;
      case field::FIELD_O:
        out << 'o';
        break;
    }
    return out;
  }

}
