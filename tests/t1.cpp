#include <iostream>
#include <vector>
#include <array>
#include <utility>

#include "tttbook.hpp"
#include "triple.hpp"

using namespace std;
using namespace tttbook;
using namespace test_util;

typedef vector<pair<int, int>> moves_t;
typedef triplet<int, array<bool, 3>, moves_t> test_t;

int main()
{
  vector<test_t> tests =
  {
    { 1, {{ false, true, false }},  { {0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 0} } },
  };
  table m;



  for(auto& test: tests)
  {
    m.init();
    auto& number = get<0>(test);
    auto& except = get<1>(test);
    auto& moves = get<2>(test);
    for(auto& move: moves)
      m.play(move.first, move.second);
    cout << "Ocekivano " << except[0] << ' ' << except[1] << ' ' << except[2] << '\n';
    cout << "Dobio " << m.is_draw() << ' ' << m.is_win(m.GAMER_X) << ' ' << m.is_win(m.GAMER_O) << '\n';
  }

  return 0;
}
