#include <iostream>

class field
{

public:

  enum field_t
  {
    FIELD_EMPTY = 0,
    FIELD_X     = 1,
    FIELD_O     = 2
  };

private:

  field_t value;

public:

  field()
  {
    value = FIELD_EMPTY;
  };

  void clean()
  {
    value = FIELD_EMPTY;
  };

  void play_as_x()
  {
    value = FIELD_X;
  };

  void play_as_o()
  {
    value = FIELD_O;
  };

  field_t get_value()
  {
    return value;
  };

  int is_clean()
  {
    return value == FIELD_EMPTY;
  }

  friend std::ostream& operator<< (std::ostream& out, const field& self)
  {
    switch(self.value)
    {
      case FIELD_EMPTY:
        out << ' ';
        break;
      case FIELD_X:
        out << 'x';
        break;
      case FIELD_O:
        out << 'o';
        break;
    }
    return out;
  };

};
