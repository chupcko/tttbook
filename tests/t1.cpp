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
  table_c table;

  for(auto& test: tests)
  {
    table.init();
    try
    {
      for(auto& move: test.moves)
        table.play(move.get_x(), move.get_y());
      if
      (
        table.is_playable() != test.except.is_playable ||
        table.is_draw() != test.except.is_draw ||
        table.is_win_x() != test.except.is_win_x ||
        table.is_win_o() != test.except.is_win_o
      )
        cout <<
          boolalpha <<
          "FAIL file=" << __FILE__ <<
          " test=" << test.number <<
          " except={ " <<
          table.is_playable() << ", " <<
          table.is_draw() << ", " <<
          table.is_win_x() << ", " <<
          table.is_win_o() <<
          " }" << endl <<
          table;
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
