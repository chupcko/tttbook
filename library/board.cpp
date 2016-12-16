#include "tttbook.hpp"

namespace TTTbook
{

  field_c& board_c::all_fields_c::iterator_c::operator*() const noexcept
  {
    return board->fields[position%board->size][position/board->size];
  }

  const board_c::all_fields_c::iterator_c& board_c::all_fields_c::iterator_c::operator++() noexcept
  {
    position++;
    return *this;
  }

  move_c& board_c::all_moves_c::iterator_c::operator*() const noexcept
  {
    return (move_c&)move;
  }

  const board_c::all_moves_c::iterator_c& board_c::all_moves_c::iterator_c::operator++() noexcept
  {
    position++;
    make_move();
    return *this;
  }

  void board_c::all_moves_c::iterator_c::make_move() noexcept
  {
    move.set(position%board->size, position/board->size);
  }

  move_c& board_c::all_moves_on_empty_c::iterator_c::operator*() const noexcept
  {
    return (move_c&)move;
  }

  const board_c::all_moves_on_empty_c::iterator_c& board_c::all_moves_on_empty_c::iterator_c::operator++() noexcept
  {
    position++;
    while
    (
      position < board->size*board->size &&
      !board->fields[position%board->size][position/board->size].is_empty()
    )
      position++;
    make_move();
    return *this;
  }

  void board_c::all_moves_on_empty_c::iterator_c::make_move() noexcept
  {
    move.set(position%board->size, position/board->size);
  }

  bool board_c::is_win_in_row(move_c::coordinate_t y, field_c::field_t field_value) const noexcept
  {
    y = move_c::normalize(size, y);
    for(move_c::coordinate_t x = 0; x < size; x++)
      if(!fields[x][y].is(field_value))
        return false;
    return true;
  }

  bool board_c::is_win_in_column(move_c::coordinate_t x, field_c::field_t field_value) const noexcept
  {
    x = move_c::normalize(size, x);
    for(move_c::coordinate_t y = 0; y < size; y++)
      if(!fields[x][y].is(field_value))
        return false;
    return true;
  }

  bool board_c::is_win_in_diagonal(move_c::coordinate_t t, field_c::field_t field_value) const noexcept
  {
    if(t == 0)
    {
      for(move_c::coordinate_t xy = 0; xy < size; xy++)
        if(!fields[xy][xy].is(field_value))
          return false;
    }
    else
    {
      for(move_c::coordinate_t xy = 0; xy < size; xy++)
        if(!fields[xy][size-1-xy].is(field_value))
          return false;
    }
    return true;
  }

  bool board_c::recalculate_status_is_draw() const noexcept
  {
    for(field_c& field : all_fields)
      if(field.is_empty())
        return false;
    return true;
  }

  bool board_c::recalculate_status_is_win(field_c::field_t field_value) const noexcept
  {
    for(move_c::coordinate_t xy = 0; xy < size; xy++)
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

  board_c::board_c(const board_c& board_init) noexcept :
    all_fields(this),
    all_moves(this),
    all_moves_on_empty(this)
  {
    status = board_init.status;
    for(move_c& move : all_moves)
      fields[move.x][move.y] = board_init.fields[move.x][move.y];
    next_player = board_init.next_player;
  }

  void board_c::init() noexcept
  {
    status.set_new();
    for(field_c& field : all_fields)
      field.set_empty();
    next_player.set_x();
  }

  bool board_c::is_win_in_row(move_c::coordinate_t y) const noexcept
  {
    return
      is_win_in_row(y, field_c::FIELD_X) ||
      is_win_in_row(y, field_c::FIELD_O);
  }

  bool board_c::is_win_in_column(move_c::coordinate_t x) const noexcept
  {
    return
      is_win_in_column(x, field_c::FIELD_X) ||
      is_win_in_column(x, field_c::FIELD_O);
  }

  bool board_c::is_win_in_diagonal(move_c::coordinate_t t) const noexcept
  {
    return
      is_win_in_diagonal(t, field_c::FIELD_X) ||
      is_win_in_diagonal(t, field_c::FIELD_O);
  }

  void board_c::next() noexcept
  {
    next_player.next();
  }

  const status_c& board_c::play(move_c move)
  {
    move.normalize(size);
    if(!status.is_playable())
      throw error_not_playable();
    if(!fields[move.x][move.y].is_empty())
      throw error_already_filled();
    fields[move.x][move.y].fill(next_player);
    next_player.next();
    recalculate_status();
    return status;
  }

  board_c::hash_t board_c::hash() const noexcept
  {
    hash_t result = 0;
    for(field_c& field : all_fields)
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
    for(move_c::coordinate_t y = 0; y < self.size; y++)
    {
      if(y != 0)
        out << "\n---+---+---\n";
      for(move_c::coordinate_t x = 0; x < self.size; x++)
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
