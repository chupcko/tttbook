#include "tttbook.hpp"

namespace tttbook
{

  std::ostream& operator<< (std::ostream& out, const status_c& self)
  {
    switch(self.status)
    {
      case status_c::STATUS_NEW:
        out << "New";
        break;
      case status_c::STATUS_PLAY:
        out << "Play";
        break;
      case status_c::STATUS_DRAW:
        out << "Draw";
        break;
      case status_c::STATUS_WIN_X:
        out << "Win X";
        break;
      case status_c::STATUS_WIN_O:
        out << "Win O";
        break;
    }
    return out;
  }

}
