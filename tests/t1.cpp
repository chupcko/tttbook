#include <iostream>
#include <vector>
#include <array>
#include <utility>

#include "tttbook.hpp"

using namespace std;
using namespace tttbook;

template <class C1, class C2, class C3> struct triplet
{
  C1 element_1;
  C2 element_2;
  C3 element_3;
};


int main()
{
  triplet<bool, int, char> pera = { true, 2, '3'};

  vector
  <
    pair
    <
      array<int, 3>,
      vector<pair<int, int>>
    >
  > result =
  {
    { {{ 0, 1, 0 }},  { {0, 0}, {0, 2}, {1, 0}, {1, 2}, {2, 0} } },
  };
  table m;



  for(auto& el: result)
  {
    m.init();
    for(auto& igra: el.second)
      m.play(igra.first, igra.second);
    cout << "Ocekivano " << el.first[0] << ' ' << el.first[1] << ' ' << el.first[2] << '\n';
    cout << "Dobio " << m.is_draw() << ' ' << m.is_win(m.GAMER_X) << ' ' << m.is_win(m.GAMER_O) << '\n';
  }

  return 0;
}
