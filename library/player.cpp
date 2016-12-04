#include "tttbook.hpp"

namespace tttbook
{

  std::ostream& operator<< (std::ostream& out, const player_c& self)
  {
    switch(self.value)
    {
      case player_c::PLAYER_X:
        out << 'x';
        break;
      case player_c::PLAYER_O:
        out << 'o';
        break;
    }
    return out;
  }

}
