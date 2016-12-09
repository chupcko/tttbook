#include <exception>
#include <iostream>

#include "tttbook.hpp"

using namespace std;
using namespace tttbook;

int main()
{
  board_c board;
  solver_c solver;
  int input;

  solver.set_best_speed_slow();
  solver.set_select_first();
  solver.set_worst_best_gate(1.0);
  for(;;)
  {
    cout << board << endl;
    if(!board.status.is_playable())
      break;

    cin >> input;
    if(input <= 0)
    {
      move_c* move = solver.calculate_move(board);
      board.play(*move);
      delete move;
    }
    else if(input <= 9)
    {
      input--;
      board.play(move_c(input%board_c::size, input/board_c::size));
    }
  }
  return 0;
}
