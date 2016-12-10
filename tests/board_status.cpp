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
  struct
  {
    bool is_new;
    bool is_play;
    bool is_draw;
    bool is_win_x;
    bool is_win_o;
  } except;
} test_t;

int main()
{
  int test_number = 0;
  vector<test_t> tests =
  {
    { test_number++, {                                                                        }, { true,  false, false, false, false } },
    { test_number++, { {0, 0}, {0, 2}                                                         }, { false, true,  false, false, false } },
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}                                         }, { false, true,  false, false, false } },
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 0}                                 }, { false, false, false, true,  false } },
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 1}, {2, 2}                         }, { false, false, false, false, true  } },
    { test_number++, { {0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}, {0, 2}         }, { false, true,  false, false, false } },
    { test_number++, { {0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}, {0, 2}, {2, 2} }, { false, false, false, true,  false } }
  };
  board_c board;

  for(test_t& test: tests)
  {
    board.init();
    try
    {
      for(move_c& move: test.moves)
        board.play(move);
      if
      (
        board.status.is_new() != test.except.is_new ||
        board.status.is_play() != test.except.is_play ||
        board.status.is_draw() != test.except.is_draw ||
        board.status.is_win_x() != test.except.is_win_x ||
        board.status.is_win_o() != test.except.is_win_o
      )
        cout <<
          boolalpha <<
          "FAIL file=" << __FILE__ <<
          " test=" << test.number <<
          " except={ " <<
          board.status.is_new() << ", " <<
          board.status.is_play() << ", " <<
          board.status.is_draw() << ", " <<
          board.status.is_win_x() << ", " <<
          board.status.is_win_o() <<
          " }" << endl <<
          board;
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
