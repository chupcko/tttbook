#include "tttbook.hpp"

namespace tttbook
{

  bool board_c::recalculate_status_is_draw() const noexcept
  {
    for(move_coordinate_t y = 0; y < size; y++)
      for(move_coordinate_t x = 0; x < size; x++)
        if(fields[x][y].is_empty())
          return false;
    return true;
  }

  bool board_c::recalculate_status_is_win(field_c::field_t field_value) const noexcept
  {
    bool all;

    for(move_coordinate_t p = 0; p < size; p++)
    {
      all = true;
      for(move_coordinate_t q = 0; q < size; q++)
        if(!fields[p][q].is(field_value))
        {
          all = false;
          break;
        }
      if(all)
        return true;
      all = true;
      for(move_coordinate_t q = 0; q < size; q++)
        if(!fields[q][p].is(field_value))
        {
          all = false;
          break;
        }
      if(all)
        return true;
    }
    all = true;
    for(move_coordinate_t t = 0; t < size; t++)
      if(!fields[t][t].is(field_value))
      {
        all = false;
        break;
      }
    if(all)
      return true;
    all = true;
    for(move_coordinate_t t = 0; t < size; t++)
      if(!fields[t][size-1-t].is(field_value))
      {
        all = false;
        break;
      }
    if(all)
      return true;
    return false;
  }

  void board_c::recalculate_status() noexcept
  {
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
    if(recalculate_status_is_draw())
    {
      status.set_draw();
      return;
    }
    status.set_play();
  }

  board_c::board_c(const board_c& board_init) noexcept
  {
    status = board_init.status;
    for(move_coordinate_t y = 0; y < size; y++)
      for(move_coordinate_t x = 0; x < size; x++)
        fields[x][y] = board_init.fields[x][y];
    next_player = board_init.next_player;
  }

  void board_c::init() noexcept
  {
    status.set_new();
    for(move_coordinate_t y = 0; y < size; y++)
      for(move_coordinate_t x = 0; x < size; x++)
        fields[x][y].set_empty();
    next_player.set_x();
  }

  const status_c& board_c::play(move_c move)
  {
    if
    (
      move.x < 0 ||
      move.x >= size ||
      move.y < 0 ||
      move.y >= size
    )
      throw error_bad_index();
    if(!status.is_playable())
      throw error_not_playable();
    if(!fields[move.x][move.y].is_empty())
      throw error_already_filled();
    fields[move.x][move.y].fill(next_player);
    next_player.next();
    recalculate_status();
    return status;
  }

  board_hash_t board_c::hash() const noexcept
  {
    board_hash_t result = 0;
    for(move_coordinate_t y = 0; y < size; y++)
      for(move_coordinate_t x = 0; x < size; x++)
      {
        result *= size;
        result += fields[x][y].field;
      }
    return result;
  }

  std::ostream& operator<<(std::ostream& out, const board_c& self)
  {
    out << "Status: " << self.status << std::endl;
    if(self.status.is_playable())
      out << "Next player: " << self.next_player << std::endl;
    for(move_coordinate_t y = 0; y < self.size; y++)
    {
      if(y != 0)
        out << std::endl << "---+---+---" << std::endl;
      for(move_coordinate_t x = 0; x < self.size; x++)
      {
        if(x != 0)
          out << " |";
        out << ' ' << self.fields[x][y];
      }
    }
    out << std::endl;
    return out;
  }

}
