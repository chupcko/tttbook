#include "tttbook.hpp"

namespace TTTbook
{

  solver_c::rate_t solver_c::rate(const board_c& board) const noexcept
  {
    if(board.status.is_draw())
      return 0;
    switch(speed)
    {
      case SPEED_FAST:
        switch(board.next_player.player)
        {
          case player_c::PLAYER_X:
            if(board.status.is_win_o())
              return board.size*board.size;
            break;
          case player_c::PLAYER_O:
            if(board.status.is_win_x())
              return board.size*board.size;
            break;
        }
        break;
      case SPEED_SLOW:
        switch(board.next_player.player)
        {
          case player_c::PLAYER_X:
            if(board.status.is_win_o())
              return 1;
            break;
          case player_c::PLAYER_O:
            if(board.status.is_win_x())
              return 1;
            break;
        }
        break;
    }

    board_c board_copy(board);
    move_c* move = best_move(board_copy);
    board_copy.play(*move);
    delete move;
    rate_t new_rate = rate(board_copy);
    switch(speed)
    {
      case SPEED_FAST:
        if(new_rate > 0)
          new_rate--;
        else if(new_rate < 0)
          new_rate++;
        break;
      case SPEED_SLOW:
        if(new_rate > 0)
          new_rate++;
        else if(new_rate < 0)
          new_rate--;
        break;
    }
    return -new_rate;
  }

  bool solver_c::compare_rate(solver_c::rate_t rate_1, solver_c::rate_t rate_2) const noexcept
  {
    if(type == TYPE_NORMAL)
      return rate_1 > rate_2;
    return rate_1 < rate_2;
  }

  move_c* solver_c::best_move(const board_c& board) const
  {
    if(!board.status.is_playable())
      throw error_not_playable();

    rate_t rates[board.size][board.size];
    for(move_c& move : board.all_moves_on_empty)
    {
      board_c board_copy(board);
      board_copy.play(move);
      rates[move.x][move.y] = rate(board_copy);
    }

    move_c moves[board.size*board.size];
    int moves_number = 0;
    for(move_c& move : board.all_moves_on_empty)
      if(moves_number == 0)
      {
        moves[0].set(move);
        moves_number = 1;
      }
      else if(compare_rate(rates[move.x][move.y], rates[moves[0].x][moves[0].y]))
      {
        moves[0].set(move);
        moves_number = 1;
      }
      else if(rates[move.x][move.y] == rates[moves[0].x][moves[0].y])
      {
        moves[moves_number].set(move);
        moves_number++;
      }

    move_c* move;
    switch(select)
    {
      case SELECT_RANDOM:
        move = new move_c(moves[util_c::random_int(0, moves_number-1)]);
        break;
      case SELECT_FIRST:
        move = new move_c(moves[0]);
        break;
      case SELECT_LAST:
        move = new move_c(moves[moves_number-1]);
        break;
    }
    return move;
  }

  move_c* solver_c::modest_normal_move(const board_c& board) const
  {
    if(!board.status.is_playable())
      throw error_not_playable();

    move_c moves[board.size*board.size];
    int moves_number = 0;
    for(move_c& move : board.all_moves_on_empty)
    {
      board_c board_copy(board);
      board_copy.play(move);
      switch(board.next_player.player)
      {
        case player_c::PLAYER_X:
          if(board_copy.status.is_win_x())
          {
            moves[moves_number].set(move);
            moves_number++;
          }
          break;
        case player_c::PLAYER_O:
          if(board_copy.status.is_win_o())
          {
            moves[moves_number].set(move);
            moves_number++;
          }
          break;
      }
    }

    if(moves_number > 0)
    {
      move_c* move;
      switch(select)
      {
        case SELECT_RANDOM:
          move = new move_c(moves[util_c::random_int(0, moves_number-1)]);
          break;
        case SELECT_FIRST:
          move = new move_c(moves[0]);
          break;
        case SELECT_LAST:
          move = new move_c(moves[moves_number-1]);
          break;
      }
      return move;
    }

    moves_number = 0;
    for(move_c& move : board.all_moves_on_empty)
    {
      board_c board_copy(board);
      board_copy.next();
      board_copy.play(move);
      switch(board.next_player.player)
      {
        case player_c::PLAYER_X:
          if(board_copy.status.is_win_o())
          {
            moves[moves_number].set(move);
            moves_number++;
          }
          break;
        case player_c::PLAYER_O:
          if(board_copy.status.is_win_x())
          {
            moves[moves_number].set(move);
            moves_number++;
          }
          break;
      }
    }

    if(moves_number > 0)
    {
      move_c* move;
      switch(select)
      {
        case SELECT_RANDOM:
          move = new move_c(moves[util_c::random_int(0, moves_number-1)]);
          break;
        case SELECT_FIRST:
          move = new move_c(moves[0]);
          break;
        case SELECT_LAST:
          move = new move_c(moves[moves_number-1]);
          break;
      }
      return move;
    }

    return worst_move(board);
  }

  move_c* solver_c::modest_reverse_move(const board_c& board) const
  {
    if(!board.status.is_playable())
      throw error_not_playable();

    move_c moves[board.size*board.size];
    int moves_number = 0;
    for(move_c& move : board.all_moves_on_empty)
    {
      board_c board_copy(board);
      board_copy.play(move);
      switch(board.next_player.player)
      {
        case player_c::PLAYER_X:
          if(!board_copy.status.is_win_x())
          {
            moves[moves_number].set(move);
            moves_number++;
          }
          break;
        case player_c::PLAYER_O:
          if(!board_copy.status.is_win_o())
          {
            moves[moves_number].set(move);
            moves_number++;
          }
          break;
      }
    }

    if(moves_number > 0)
    {
      move_c* move;
      switch(select)
      {
        case SELECT_RANDOM:
          move = new move_c(moves[util_c::random_int(0, moves_number-1)]);
          break;
        case SELECT_FIRST:
          move = new move_c(moves[0]);
          break;
        case SELECT_LAST:
          move = new move_c(moves[moves_number-1]);
          break;
      }
      return move;
    }

    return worst_move(board);
  }

  move_c* solver_c::worst_move(const board_c& board) const
  {
    if(!board.status.is_playable())
      throw error_not_playable();

    move_c moves[board.size*board.size];
    int moves_number = 0;
    for(move_c& move : board.all_moves_on_empty)
    {
      moves[moves_number].set(move);
      moves_number++;
    }

    move_c* move;
    switch(select)
    {
      case SELECT_RANDOM:
        move = new move_c(moves[util_c::random_int(0, moves_number-1)]);
        break;
      case SELECT_FIRST:
        move = new move_c(moves[0]);
        break;
      case SELECT_LAST:
        move = new move_c(moves[moves_number-1]);
        break;
    }
    return move;
  }

  move_c* solver_c::calculate_move(const board_c& board) const
  {
    if(board.moves_number < guaranteed_best*2)
      return best_move(board);
    double bid = util_c::random_double(0.0, worst_weight+modest_weight+best_weight);
    if(bid < worst_weight)
      return worst_move(board);
    if(bid < worst_weight+modest_weight)
      if(type == TYPE_NORMAL)
        return modest_normal_move(board);
      else
        return modest_reverse_move(board);
    return best_move(board);
  }

  void solver_c::info(std::ostream& out) const noexcept
  {
    out << "Type is ";
    switch(type)
    {
      case TYPE_NORMAL:
        out << "normal";
        break;
      case TYPE_REVERSE:
        out << "reverse";
        break;
    }
    out <<
      "\nGuaranteed best is " << guaranteed_best <<
      std::fixed << std::setprecision(5) <<
      "\nBest weigth is " << best_weight <<
      "\nModest weigth is " << modest_weight <<
      "\nWorst weigth is " << worst_weight <<
      "\nSelect is ";
    switch(select)
    {
      case SELECT_RANDOM:
        out << "random";
        break;
      case SELECT_FIRST:
        out << "first";
        break;
      case SELECT_LAST:
        out << "last";
        break;
    }
    out << "\nSpeed is ";
    switch(speed)
    {
      case SPEED_FAST:
        out << "fast";
        break;
      case SPEED_SLOW:
        out << "slow";
        break;
    }
    out << '\n';
  }

  std::ostream& operator<<(std::ostream& out, const solver_c& self)
  {
    self.info(out);
    return out;
  }

}
