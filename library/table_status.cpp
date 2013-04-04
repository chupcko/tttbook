#include "tttbook.hpp"

namespace tttbook
{

  std::ostream& operator<< (std::ostream& out, const table_status& self)
  {
    switch(self.value)
    {
      case table_status::STATUS_IN_GAME:
        out << "In game";
        break;
      case table_status::STATUS_DRAW:
        out << "Draw";
        break;
      case table_status::STATUS_WIN_X:
        out << "Win X";
        break;
      case table_status::STATUS_WIN_O:
        out << "Win O";
        break;
    }
    return out;
  }

}
