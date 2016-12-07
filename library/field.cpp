#include "tttbook.hpp"

namespace tttbook
{

  void field_c::fill(player_c player) noexcept
  {
    if(player.is_x())
      set_x();
    if(player.is_o())
      set_o();
  }

  std::ostream& operator<< (std::ostream& out, const field_c& self)
  {
    switch(self.field)
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

  bool operator== (const field_c& self, const field_c& other)
  {
    return self.field == other.field;
  }

  bool operator!= (const field_c& self, const field_c& other)
  {
    return !(self == other);
  }

}
