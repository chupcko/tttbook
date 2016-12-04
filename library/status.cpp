#include "tttbook.hpp"

namespace tttbook
{

  std::ostream& operator<< (std::ostream& out, const status_c& self)
  {
    switch(self.value)
    {
      case status_c::STATUS_PLAYABLE:
        out << "Playable";
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
