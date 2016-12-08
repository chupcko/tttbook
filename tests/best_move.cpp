#include <exception>
#include <iostream>
#include <vector>

#include "tttbook.hpp"

using namespace std;
using namespace tttbook;

typedef struct test_t
{
  int            number;
  vector<move_c> moves;
} test_t;

int main(void)
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
  solver.set_slow_speed();
  solver.set_first_select();

  for(auto& test: tests)
  {
    board.init_board();
    try
    {
      for(auto& move: test.moves)
        board.play(move);
      cout << test.number << ' ' << board << endl;
      move_c* move = solver.best_move(board);
      cout << *move << endl;
      board.play(*move);
      cout << board << endl;
    }
    catch(const exception& e)
    {
      cout <<
        "ERROR file=" << __FILE__ <<
        " test=" << test.number << ' ' <<
        e.what() << endl;
    }
  }

  return 0;
}
