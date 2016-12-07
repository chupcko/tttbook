#include "tttbook.hpp"

namespace tttbook
{

  bool board_c::recalculate_status_is_draw(void) const noexcept
  {
    for(coordinate_t x = 0; x < size; x++)
      for(coordinate_t y = 0; y < size; y++)
        if(fields[x][y].is_empty())
          return false;
    return true;
  }

  bool board_c::recalculate_status_is_win(field_c::field_t field_value) const noexcept
  {
    bool all;

    for(coordinate_t x = 0; x < size; x++)
    {
      all = true;
      for(coordinate_t y = 0; y < size; y++)
        if(!fields[x][y].is(field_value))
        {
          all = false;
          break;
        }
      if(all)
        return true;
      all = true;
      for(coordinate_t y = 0; y < size; y++)
        if(!fields[y][x].is(field_value))
        {
          all = false;
          break;
        }
      if(all)
        return true;
    }
    all = true;
    for(coordinate_t x = 0; x < size; x++)
      if(!fields[x][x].is(field_value))
      {
        all = false;
        break;
      }
    if(all)
      return true;
    all = true;
    for(coordinate_t x = 0; x < size; x++)
      if(!fields[x][size-1-x].is(field_value))
      {
        all = false;
        break;
      }
    if(all)
      return true;
    return false;
  }

  void board_c::recalculate_status(void) noexcept
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

  board_c::board_c(const board_c* board_init) noexcept
  {
    status = board_init->status;
    for(coordinate_t x = 0; x < size; x++)
      for(coordinate_t y = 0; y < size; y++)
        fields[x][y] = board_init->fields[x][y];
    player = board_init->player;
  }

  void board_c::init(void) noexcept
  {
    status.set_new();
    for(coordinate_t x = 0; x < size; x++)
      for(coordinate_t y = 0; y < size; y++)
        fields[x][y].set_empty();
    player.set_x();
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
    fields[move.x][move.y].fill(player);
    player.next();
    recalculate_status();
    return status;
  }

  board_hash_t board_c::hash() const noexcept
  {
    board_hash_t result = 0;
    for(coordinate_t x = 0; x < size; x++)
      for(coordinate_t y = 0; y < size; y++)
      {
        result *= size;
        result += fields[x][y].field;
      }
    return result;
  }

  std::ostream& operator<< (std::ostream& out, const board_c& self)
  {
    out << self.status;
    if(self.status.is_playable())
      out << " next: " << self.player;
    out << std::endl;
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

  bool operator== (const board_c& self, const board_c& other)
  {
    for(coordinate_t x = 0; x < board_c::size; x++)
      for(coordinate_t y = 0; y < board_c::size; y++)
        if(self.fields[x][y] != other.fields[x][y])
          return false;
    return self.player == other.player;
  }

  bool operator!= (const board_c& self, const board_c& other)
  {
    return !(self == other);
  }

}
