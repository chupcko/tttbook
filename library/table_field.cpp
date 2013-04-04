#include "tttbook.hpp"

namespace tttbook
{

  std::ostream& operator<< (std::ostream& out, const table_field& self)
  {
    switch(self.value)
    {
      case table_field::FIELD_EMPTY:
        out << ' ';
        break;
      case table_field::FIELD_X:
        out << 'x';
        break;
      case table_field::FIELD_O:
        out << 'o';
        break;
    }
    return out;
  }

}
