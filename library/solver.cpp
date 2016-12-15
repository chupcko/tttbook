#include "tttbook.hpp"

namespace TTTbook
{

  int solver_c::best_rate(const board_c& board) const noexcept
  {
    if(board.status.is_draw())
      return 0;
    switch(best_speed)
    {
      case BEST_SPEED_FAST:
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
      case BEST_SPEED_SLOW:
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
    int new_rate = best_rate(board_copy);
    switch(best_speed)
    {
      case BEST_SPEED_FAST:
        if(new_rate > 0)
          new_rate--;
        else if(new_rate < 0)
          new_rate++;
        break;
      case BEST_SPEED_SLOW:
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
          scores[x][y] = best_rate(board_copy);
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
    for(move_coordinate_t y = 0; y < board.size; y++)
      for(move_coordinate_t x = 0; x < board.size; x++)
        if(board.fields[x][y].is_empty())
        {
          board_c board_copy(board);
          board_copy.play(move_c(x, y));
          switch(board.next_player.player)
          {
            case player_c::PLAYER_X:
              if(board_copy.status.is_win_x())
              {
                moves[moves_number].set(x, y);
                moves_number++;
              }
              break;
            case player_c::PLAYER_O:
              if(board_copy.status.is_win_o())
              {
                moves[moves_number].set(x, y);
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
    for(move_coordinate_t y = 0; y < board.size; y++)
      for(move_coordinate_t x = 0; x < board.size; x++)
        if(board.fields[x][y].is_empty())
        {
          board_c board_copy(board);
          board_copy.next();
          board_copy.play(move_c(x, y));
          switch(board.next_player.player)
          {
            case player_c::PLAYER_X:
              if(board_copy.status.is_win_o())
              {
                moves[moves_number].set(x, y);
                moves_number++;
              }
              break;
            case player_c::PLAYER_O:
              if(board_copy.status.is_win_x())
              {
                moves[moves_number].set(x, y);
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
    double bid = util_c::random_double(0.0, best_weight+modest_weight+worst_weight);
    if(bid < best_weight)
      return best_move(board);
    if(bid < modest_weight)
      return modest_move(board);
    return worst_move(board);
  }

  void solver_c::info(std::ostream& out) const noexcept
  {
    out << std::fixed << std::setprecision(5) <<
      "Best weitgh: " << best_weight <<
      "\nModest weitgh: " << modest_weight <<
      "\nWorst weitgh: " << worst_weight <<
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
    out << "\nBest speed: ";
    switch(best_speed)
    {
      case BEST_SPEED_FAST:
        out << "fast";
        break;
      case BEST_SPEED_SLOW:
        out << "slow";
        break;
    }
    out << '\n';
  }

}
