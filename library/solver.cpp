#include "tttbook.hpp"

namespace TTTbook
{

  int solver_c::rate(const board_c& board, move_c* (solver_c::*caller)(const board_c&) const) const noexcept
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
    move_c* move = (this->*caller)(board_copy);
    board_copy.play(*move);
    delete move;
    int new_rate = rate(board_copy, caller);
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

  move_c* solver_c::best_move(const board_c& board) const
  {
    if(!board.status.is_playable())
      throw error_not_playable();

    int scores[board.size][board.size];
    for(move_c& move : board.all_moves_on_empty)
    {
      board_c board_copy(board);
      board_copy.play(move);
      scores[move.x][move.y] = rate(board_copy, &solver_c::best_move);
    }

    move_c moves[board.size*board.size];
    int moves_number = 0;
    for(move_c& move : board.all_moves_on_empty)
      if(moves_number == 0)
      {
        moves[0].set(move);
        moves_number = 1;
      }
      else
      {
        if(scores[move.x][move.y] > scores[moves[0].x][moves[0].y])
        {
          moves[0].set(move);
          moves_number = 1;
        }
        else if(scores[move.x][move.y] == scores[moves[0].x][moves[0].y])
        {
          moves[moves_number].set(move);
          moves_number++;
        }
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

  move_c* solver_c::modest_move(const board_c& board) const
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

  move_c* solver_c::lose_move(const board_c& board) const
  {
    if(!board.status.is_playable())
      throw error_not_playable();

    int scores[board.size][board.size];
    for(move_c& move : board.all_moves_on_empty)
    {
      board_c board_copy(board);
      board_copy.play(move);
      scores[move.x][move.y] = rate(board_copy, &solver_c::lose_move);
    }

    move_c moves[board.size*board.size];
    int moves_number = 0;
    for(move_c& move : board.all_moves_on_empty)
      if(moves_number == 0)
      {
        moves[0].set(move);
        moves_number = 1;
      }
      else
      {
        if(scores[move.x][move.y] < scores[moves[0].x][moves[0].y])
        {
          moves[0].set(move);
          moves_number = 1;
        }
        else if(scores[move.x][move.y] == scores[moves[0].x][moves[0].y])
        {
          moves[moves_number].set(move);
          moves_number++;
        }
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
    double bid = util_c::random_double(0.0, best_weight+modest_weight+worst_weight+lose_weight);
    if(bid < best_weight)
      return best_move(board);
    if(bid < best_weight+modest_weight)
      return modest_move(board);
    if(bid < best_weight+modest_weight+worst_weight)
      return worst_move(board);
    return lose_move(board);
  }

  void solver_c::info(std::ostream& out) const noexcept
  {
    out << "Type: ";
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
      "\nGuaranteed best: " << guaranteed_best <<
      std::fixed << std::setprecision(5) <<
      "\nBest weitgh: " << best_weight <<
      "\nModest weitgh: " << modest_weight <<
      "\nWorst weitgh: " << worst_weight <<
      "\nLose weitgh: " << lose_weight <<
      "\nSelect: ";
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
    out << "\nSpeed: ";
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

}
