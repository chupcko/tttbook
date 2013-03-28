#include <iostream>
#include <vector>
#include <array>
#include <utility>

#include "tttbook.hpp"
#include "triple.hpp"

using namespace std;
using namespace tttbook;
using namespace test_utility;

typedef vector<pair<int, int>> moves_t;
typedef array<bool, 3> except_t;
typedef triplet<int, moves_t, except_t> test_t;

int main()
{
  int test_number = 0;
  vector<test_t> tests =
  {
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 0} }, { { false, true, false } } },
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 0} }, { { false, true, true } } },
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 0} }, { { false, true, true } } },
    { test_number++, { {0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 0} }, { { false, true, true } } },
  };
  table test_table;

  for(auto& test: tests)
  {
    test_table.init();
    auto& number = get<0>(test);
    auto& moves = get<1>(test);
    auto& except = get<2>(test);
    for(auto& move: moves)
      test_table.play(move.first, move.second);
    if
    (
      test_table.is_draw() != except[0] ||
      test_table.is_win(table::GAMER_X) != except[1] ||
      test_table.is_win(table::GAMER_O) != except[2]
    )
      cout <<
        boolalpha <<
        "FAIL file=" <<
        __FILE__ <<
        " test=" <<
        number <<
        " except={ " <<
        test_table.is_draw() <<
        ", " <<
        test_table.is_win(table::GAMER_X) <<
        ", " <<
        test_table.is_win(table::GAMER_O) <<
        " }" <<
        endl <<
        test_table;
  }

  return 0;
}
