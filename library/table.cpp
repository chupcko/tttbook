#include "tttbook.hpp"

namespace tttbook
{

  bool table::is_win_helper(field::field_t field_value) const
  {
    bool all;

    for(int x = 0; x < size; x++)
    {
      all = true;
      for(int y = 0; y < size; y++)
        if(fields[x][y].get_value() != field_value)
        {
          all = false;
          break;
        }
      if(all)
        return true;
      all = true;
      for(int y = 0; y < size; y++)
        if(fields[y][x].get_value() != field_value)
        {
          all = false;
          break;
        }
      if(all)
        return true;
    }
    all = true;
    for(int x = 0; x < size; x++)
      if(fields[x][x].get_value() != field_value)
      {
        all = false;
        break;
      }
    if(all)
      return true;
    for(int x = 0; x < size; x++)
      if(fields[x][size-1-x].get_value() != field_value)
      {
        all = false;
        break;
      }
    if(all)
      return true;
    return false;
  }

  table::table()
  {
    init();
  };

  void table::init()
  {
    for(int x = 0; x < size; x++)
      for(int y = 0; y < size; y++)
        fields[x][y].clean();
    on_move = GAMER_X;
  }

  bool table::play(int x, int y)
  {
    if
    (
      x < 0 ||
      x >= size ||
      y < 0 ||
      y >= size ||
      !fields[x][y].is_clean()
    )
      return false;

    switch(on_move)
    {
      case GAMER_X:
        fields[x][y].play_as_x();
        on_move = GAMER_O;
        break;
      case GAMER_O:
        fields[x][y].play_as_o();
        on_move = GAMER_X;
        break;
    }
    return true;
  }

  bool table::is_draw() const
  {
    for(int x = 0; x < size; x++)
      for(int y = 0; y < size; y++)
        if(fields[x][y].is_clean())
          return false;
    return true;
  }

  bool table::is_win(table::gamer_t who) const
  {
    switch(who)
    {
      case GAMER_X:
        return is_win_helper(field::FIELD_X);
      case GAMER_O:
        return is_win_helper(field::FIELD_O);
    }
  }

  bool table::is_win_x() const
  {
    return is_win_helper(field::FIELD_X);
  }

  bool table::is_win_o() const
  {
    return is_win_helper(field::FIELD_O);
  }

  std::ostream& operator<< (std::ostream& out, const table& self)
  {
    for(int x = 0; x < self.size; x++)
    {
      for(int y = 0; y < self.size; y++)
      {
        out << " " << self.fields[x][y];
        if(y != self.size-1)
          out << " |";
      }
      if(x != self.size-1)
        out << "\n---+---+---\n";
    }
    out << "\n";
    return out;
  }

}
