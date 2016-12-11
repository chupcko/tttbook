#include "tttbook.hpp"

namespace TTTbook
{

  field_c& board_fields_iterator_c::operator*() const noexcept
  {
    return board->fields[position%board_c::size][position/board_c::size];
  }

  const board_fields_iterator_c& board_fields_iterator_c::operator++() noexcept
  {
    position++;
    return *this;
  }

  bool board_c::is_win_in_row(move_coordinate_t y, field_c::field_t field_value) const noexcept
  {
    for(move_coordinate_t x = 0; x < size; x++)
      if(!fields[x][y].is(field_value))
        return false;
    return true;
  }

  bool board_c::is_win_in_column(move_coordinate_t x, field_c::field_t field_value) const noexcept
  {
    for(move_coordinate_t y = 0; y < size; y++)
      if(!fields[x][y].is(field_value))
        return false;
    return true;
  }

  bool board_c::is_win_in_diagonal(move_coordinate_t t, field_c::field_t field_value) const noexcept
  {
    if(t == 0)
    {
      for(move_coordinate_t xy = 0; xy < size; xy++)
        if(!fields[xy][xy].is(field_value))
          return false;
    }
    else
    {
      for(move_coordinate_t xy = 0; xy < size; xy++)
        if(!fields[xy][size-1-xy].is(field_value))
          return false;
    }
    return true;
  }

  bool board_c::recalculate_status_is_draw() const noexcept
  {
    for(field_c& field : *this)
      if(field.is_empty())
        return false;
    return true;
  }

  bool board_c::recalculate_status_is_win(field_c::field_t field_value) const noexcept
  {
    for(move_coordinate_t xy = 0; xy < size; xy++)
    {
      if(is_win_in_row(xy, field_value))
        return true;
      if(is_win_in_column(xy, field_value))
        return true;
    }
    if(is_win_in_diagonal(0, field_value))
      return true;
    if(is_win_in_diagonal(1, field_value))
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
    for(field_c& field : *this)
      field.set_empty();
    next_player.set_x();
  }

  bool board_c::is_win_in_row(move_coordinate_t y) const noexcept
  {
    return
      is_win_in_row(y, field_c::FIELD_X) ||
      is_win_in_row(y, field_c::FIELD_O);
  }

  bool board_c::is_win_in_column(move_coordinate_t x) const noexcept
  {
    return
      is_win_in_column(x, field_c::FIELD_X) ||
      is_win_in_column(x, field_c::FIELD_O);
  }

  bool board_c::is_win_in_diagonal(move_coordinate_t t) const noexcept
  {
    return
      is_win_in_diagonal(t, field_c::FIELD_X) ||
      is_win_in_diagonal(t, field_c::FIELD_O);
  }

  const status_c& board_c::play(move_c move)
  {
    if(!move.is_valid(size))
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
    for(field_c& field : *this)
    {
      result *= size;
      result += field.field;
    }
    return result;
  }

  std::ostream& operator<<(std::ostream& out, const board_c& self)
  {
    out << "Status: " << self.status << '\n';
    if(self.status.is_playable())
      out << "Next player: " << self.next_player << '\n';
    for(move_coordinate_t y = 0; y < self.size; y++)
    {
      if(y != 0)
        out << "\n---+---+---\n";
      for(move_coordinate_t x = 0; x < self.size; x++)
      {
        if(x != 0)
          out << " |";
        out << ' ' << self.fields[x][y];
      }
    }
    out << '\n';
    return out;
  }

}
