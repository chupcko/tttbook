#include <iostream>
#include <vector>

#include "tttbook.hpp"

using namespace std;
using namespace tttbook;

typedef struct test_t
{
  int            number;
  vector<move_c> moves;
  struct
  {
    bool is_playable;
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
    { test_number++, {                                                                        }, { true,  false, false, false } },
    { test_number++, { {0, 0}, {0, 2}                                                         }, { true,  false, false, false } },
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}                                         }, { true,  false, false, false } },
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 0}                                 }, { false, false, true,  false } },
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 1}, {2, 2}                         }, { false, false, false, true  } },
    { test_number++, { {0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}, {0, 2}         }, { true,  false, false, false } },
    { test_number++, { {0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}, {0, 2}, {2, 2} }, { false, true,  false, false } }
  };
  board_c board;

  for(auto& test: tests)
  {
    board.init();
    try
    {
      for(auto& move: test.moves)
        board.play(move.get_x(), move.get_y());
      if
      (
        board.is_playable() != test.except.is_playable ||
        board.is_draw() != test.except.is_draw ||
        board.is_win_x() != test.except.is_win_x ||
        board.is_win_o() != test.except.is_win_o
      )
        cout <<
          boolalpha <<
          "FAIL file=" << __FILE__ <<
          " test=" << test.number <<
          " except={ " <<
          board.is_playable() << ", " <<
          board.is_draw() << ", " <<
          board.is_win_x() << ", " <<
          board.is_win_o() <<
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
