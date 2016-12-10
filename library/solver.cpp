#include "tttbook.hpp"

namespace TTTbook
{

  int solver_c::rate(const board_c& board) const noexcept
  {
    if(board.status.is_draw())
      return 0;
    switch(best_speed)
    {
      case BEST_FAST:
        switch(board.next_player.player)
        {
          case player_c::PLAYER_X:
            if(board.status.is_win_x())
              return -board.size*board.size;
            else if(board.status.is_win_o())
              return board.size*board.size;
            break;
          case player_c::PLAYER_O:
            if(board.status.is_win_x())
              return board.size*board.size;
            else if(board.status.is_win_o())
              return -board.size*board.size;
            break;
        }
        break;
      case BEST_SLOW:
        switch(board.next_player.player)
        {
          case player_c::PLAYER_X:
            if(board.status.is_win_x())
              return -1;
            else if(board.status.is_win_o())
              return 1;
            break;
          case player_c::PLAYER_O:
            if(board.status.is_win_x())
              return 1;
            else if(board.status.is_win_o())
              return -1;
            break;
        }
        break;
    }
    board_c board_copy(board);
    move_c* move = best_move(board_copy);
    board_copy.play(*move);
    delete move;
    int new_rate = rate(board_copy);
    switch(best_speed)
    {
      case BEST_FAST:
        if(new_rate > 0)
          new_rate--;
        else if(new_rate < 0)
          new_rate++;
        break;
      case BEST_SLOW:
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
    for(move_coordinate_t y = 0; y < board.size; y++)
      for(move_coordinate_t x = 0; x < board.size; x++)
        if(board.fields[x][y].is_empty())
        {
          board_c board_copy(board);
          board_copy.play(move_c(x, y));
          scores[x][y] = rate(board_copy);
        }

    move_c moves[board.size*board.size];
    int moves_number = 0;
    for(move_coordinate_t y = 0; y < board.size; y++)
      for(move_coordinate_t x = 0; x < board.size; x++)
        if(board.fields[x][y].is_empty())
          if(moves_number == 0)
          {
            moves[0].set(x, y);
            moves_number = 1;
          }
          else
          {
            if(scores[x][y] > scores[moves[0].x][moves[0].y])
            {
              moves[0].set(x, y);
              moves_number = 1;
            }
            else if(scores[x][y] == scores[moves[0].x][moves[0].y])
            {
              moves[moves_number].set(x, y);
              moves_number++;
            }
          }

    move_c* move;
    switch(select)
    {
      case RANDOM:
        move = new move_c(moves[util_c::random_int(0, moves_number-1)]);
        break;
      case FIRST:
        move = new move_c(moves[0]);
        break;
      case LAST:
        move = new move_c(moves[moves_number-1]);
        break;
    }
    return move;
  }

  move_c* solver_c::worst_move(const board_c& board) const
  {
    if(!board.status.is_playable())
      throw error_not_playable();

    move_c moves[board.size*board.size];
    int moves_number = 0;
    for(move_coordinate_t y = 0; y < board.size; y++)
      for(move_coordinate_t x = 0; x < board.size; x++)
        if(board.fields[x][y].is_empty())
        {
          moves[moves_number].set(x, y);
          moves_number++;
        }

    move_c* move;
    switch(select)
    {
      case RANDOM:
        move = new move_c(moves[util_c::random_int(0, moves_number-1)]);
        break;
      case FIRST:
        move = new move_c(moves[0]);
        break;
      case LAST:
        move = new move_c(moves[moves_number-1]);
        break;
    }
    return move;
  }

  move_c* solver_c::calculate_move(const board_c& board) const
  {
    if(util_c::random_double(0.0, 1.0) < worst_best_gate)
      return worst_move(board);
    else
      return best_move(board);
  }

}
