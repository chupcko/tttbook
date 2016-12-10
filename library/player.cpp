#include "tttbook.hpp"

namespace TTTbook
{

  void player_c::next() noexcept
  {
    switch(player)
    {
      case PLAYER_X:
        player = PLAYER_O;
        break;
      case PLAYER_O:
        player = PLAYER_X;
        break;
    }
  };

  std::ostream& operator<<(std::ostream& out, const player_c& self)
  {
    switch(self.player)
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
