#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>

#include "tttbook.hpp"

using namespace std;
using namespace TTTbook;

typedef struct test_t
{
  int            number;
  vector<move_c> moves;
} test_t;

int main()
{
  int test_number = 0;
  vector<test_t> tests =
  {
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}                                 } }
/*    { test_number++, { {0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}, {0, 2} } }*/
/*    { test_number++, { {0, 0}, {0, 1}, {1, 0}, {0, 2}, {2, 2}, {1, 2}, {2, 1} } }*/
  };
  board_c board;
  solver_c solver;
  solver.set_best_speed_slow();
  solver.set_select_first();
  solver.set_worst_best_gate(0.0);

  for(test_t& test: tests)
  {
    board.init();
    try
    {
      for(move_c& move: test.moves)
        board.play(move);
      cout << test.number << ' ' << board << '\n';
      move_c* move = solver.calculate_move(board);
      cout << *move << '\n';
      board.play(*move);
      cout << board << '\n';
    }
    catch(const exception& e)
    {
      cout <<
        "ERROR file=" << __FILE__ <<
        " test=" << test.number << ' ' <<
        e.what() << '\n';
    }
  }

  return EXIT_SUCCESS;
}
