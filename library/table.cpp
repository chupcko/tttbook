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

  void table::init()
  {
    for(int x = 0; x < size; x++)
      for(int y = 0; y < size; y++)
        fields[x][y].clean();
    on_move = GAMER_X;
    moves_number = 0;
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
    moves[moves_number] = std::make_pair(x, y);
    moves_number++;
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

  std::ostream& operator<< (std::ostream& out, const table& self)
  {
    out << "[ ";
    for(int i = 0; i < self.moves_number; i++)
    {
      if(i != 0)
        out << ", ";
      out << "(" << self.moves[i].first << "," << self.moves[i].second << ")";
    }
    out << " ]" << std::endl;
    for(int x = 0; x < self.size; x++)
    {
      for(int y = 0; y < self.size; y++)
      {
        out << " " << self.fields[x][y];
        if(y != self.size-1)
          out << " |";
      }
      if(x != self.size-1)
        out << std::endl << "---+---+---" << std::endl;
    }
    out << std::endl;
    return out;
  }

}
