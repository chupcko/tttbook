#include "tttbook.hpp"

namespace tttbook
{

  bool table_c::recalculate_status_is_draw() const noexcept
  {
    for(coordinate_t x = 0; x < size; x++)
      for(coordinate_t y = 0; y < size; y++)
        if(fields[x][y].is_empty())
          return false;
    return true;
  }

  bool table_c::recalculate_status_is_win(field_c::field_t field_value) const noexcept
  {
    bool all;

    for(coordinate_t x = 0; x < size; x++)
    {
      all = true;
      for(coordinate_t y = 0; y < size; y++)
        if(fields[x][y].get_value() != field_value)
        {
          all = false;
          break;
        }
      if(all)
        return true;
      all = true;
      for(coordinate_t y = 0; y < size; y++)
        if(fields[y][x].get_value() != field_value)
        {
          all = false;
          break;
        }
      if(all)
        return true;
    }
    all = true;
    for(coordinate_t x = 0; x < size; x++)
      if(fields[x][x].get_value() != field_value)
      {
        all = false;
        break;
      }
    if(all)
      return true;
    for(coordinate_t x = 0; x < size; x++)
      if(fields[x][size-1-x].get_value() != field_value)
      {
        all = false;
        break;
      }
    if(all)
      return true;
    return false;
  }

  void table_c::recalculate_status() noexcept
  {
    if(recalculate_status_is_draw())
    {
      status.set_draw();
      return;
    }
    if(recalculate_status_is_win(field_c::FIELD_X))
    {
      status.set_win_x();
      return;
    }
    if(recalculate_status_is_win(field_c::FIELD_O))
    {
      status.set_win_o();
      return;
    }
  }

  void table_c::init() noexcept
  {
    status.set_playable();
    for(coordinate_t x = 0; x < size; x++)
      for(coordinate_t y = 0; y < size; y++)
        fields[x][y].set_empty();
    player.set_x();
    moves_number = 0;
  }

  const status_c& table_c::play(coordinate_t x, coordinate_t y)
  {
    if
    (
      x < 0 ||
      x >= size ||
      y < 0 ||
      y >= size
    )
      throw error_bad_index();
    if(!status.is_playable())
      throw error_not_playable();
    if(!fields[x][y].is_empty())
      throw error_already_filled();
    fields[x][y].fill(player);
    player.next();
    moves[moves_number].set(x, y);
    moves_number++;
    recalculate_status();
    return status;
  }

  std::ostream& operator<< (std::ostream& out, const table_c& self)
  {
    out << self.status << " [ ";
    for(int i = 0; i < self.moves_number; i++)
    {
      if(i != 0)
        out << ", ";
      out << self.moves[i];
    }
    out << " ]" << std::endl;
    for(coordinate_t y = 0; y < self.size; y++)
    {
      if(y != 0)
        out << std::endl << "---+---+---" << std::endl;
      for(coordinate_t x = 0; x < self.size; x++)
      {
        if(x != 0)
          out << " |";
        out << " " << self.fields[x][y];
      }
    }
    out << std::endl;
    return out;
  }

}
