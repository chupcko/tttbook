#include "tttbook.hpp"

namespace tttbook
{

  int solver_c::rate(void) const noexcept
  {
    if(status.is_draw())
      return 0;
    switch(player.player)
    {
      case player_c::PLAYER_X:
        if(status.is_win_x())
          return -1;
        else if(status.is_win_o())
          return 1;
        break;
      case player_c::PLAYER_O:
        if(status.is_win_x())
          return 1;
        else if(status.is_win_o())
          return -1;
        break;
    }
    solver_c solver_copy(this);
    move_c* move = solver_copy.best_move();
    solver_copy.play(*move);
    delete move;
    int new_rate = solver_copy.rate();
    if(new_rate > 0)
      new_rate++;
    else if(new_rate < 0)
      new_rate--;
    return -new_rate;
  }

  int solver_c::random(int low, int high) const noexcept
  {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(low, high);
    return distribution(generator);
  }

  move_c* solver_c::best_move(void) const
  {
    if(!status.is_playable())
      throw error_not_playable();
    int scores[size][size];
    for(coordinate_t x = 0; x < size; x++)
      for(coordinate_t y = 0; y < size; y++)
        if(fields[x][y].is_empty())
        {
          solver_c solver_copy(this);
          solver_copy.play(move_c(x, y));
          switch(speed)
          {
            case FAST:
              /*#*/
              scores[x][y] = (size*size)+1-solver_copy.rate();
              break;
            case SLOW:
              scores[x][y] = solver_copy.rate();
              break;
          }
        }

    move_c moves[size*size];
    int moves_number = 0;
    for(coordinate_t x = 0; x < size; x++)
      for(coordinate_t y = 0; y < size; y++)
        if(fields[x][y].is_empty())
          if(moves_number == 0)
          {
            moves[0].x = x;
            moves[0].y = y;
            moves_number = 1;
          }
          else
          {
            if(scores[x][y] > scores[moves[0].x][moves[0].y])
            {
              moves[0].x = x;
              moves[0].y = y;
              moves_number = 1;
            }
            else if(scores[x][y] == scores[moves[0].x][moves[0].y])
            {
              moves[moves_number].x = x;
              moves[moves_number].y = y;
              moves_number++;
            }
          }

/*#*/
    std::cout << *this;
    for(coordinate_t y = 0; y < size; y++)
    {
      for(coordinate_t x = 0; x < size; x++)
        if(fields[x][y].is_empty())
          std::cout << scores[x][y] << ' ';
        else
          std::cout << ". ";
      std::cout << std::endl;
    }
    for(int i = 0; i < moves_number; i++)
      std::cout << moves[i] << '(' << scores[moves[i].x][moves[i].y] << ") ";
    std::cout << std::endl << std::endl;
/*#*/

    move_c* move;
    switch(select)
    {
      case FIRST:
        move = new move_c(&moves[0]);
        break;
      case RANDOM:
        move = new move_c(&moves[random(0, moves_number-1)]);
        break;
      case LAST:
        move = new move_c(&moves[moves_number-1]);
        break;
    }
    return move;
  }

}
