#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>

#include "tttbook.hpp"

using namespace std;
using namespace TTTbook;

int main()
{
  vector<move_c> moves = { {0, 0}, {0, 2}, {1, 0}, {1, 2} };
  board_c board;
  solver_c solver;

  solver.set_guaranteed_best(2);
  solver.set_best_weight(1.0);
  solver.set_modest_weight(0.0);
  solver.set_worst_weight(0.0);
  solver.set_select_first();
  solver.set_speed_slow();

  try
  {
    for(move_c& move: moves)
      board.play(move);
    cout << board << '\n';
    move_c* move = solver.calculate_move(board);
    cout << *move << "\n\n";
    board.play(*move);
    cout << board << '\n';
  }
  catch(const exception& e)
  {
    cout << "ERROR " << e.what() << '\n';
  }
  return EXIT_SUCCESS;
}
