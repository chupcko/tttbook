#include <exception>
#include <iostream>
#include <vector>

#include "tttbook.hpp"

using namespace std;
using namespace tttbook;

int main(void)
{
  solver_c solver;
  int input;

  solver.set_fast_speed();
  solver.set_random_select();
  for(;;)
  {
    cout << solver << endl;
    if(!solver.status.is_playable())
      break;

    cin >> input;
    if(input <= 0)
    {
      move_c* move = solver.best_move();
      solver.play(*move);
      delete move;
    }
    else if(input <= 9)
    {
      input--;
      solver.play(new move_c(input%solver_c::size, input/solver_c::size));
    }
  }
  return 0;
}
