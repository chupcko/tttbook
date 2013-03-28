#include "tttbook.hpp"

namespace tttbook
{

  field::field()
  {
    value = FIELD_EMPTY;
  }

  void field::clean()
  {
    value = FIELD_EMPTY;
  }

  void field::play_as_x()
  {
    value = FIELD_X;
  }

  void field::play_as_o()
  {
    value = FIELD_O;
  }

  field::field_t field::get_value() const
  {
    return value;
  }

  bool field::is_clean() const
  {
    return value == FIELD_EMPTY;
  }

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
