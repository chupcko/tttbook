#include <exception>
#include <iostream>

#include "tttbook.hpp"

using namespace std;
using namespace tttbook;

int main()
{
  book_c book;
  book.set_best_speed_fast();
  book.set_select_random();
  book.set_worst_best_gate(0.001);
  book.book_play_second();

  book.fill();
  book.shuffle(3);

  cout << book;
  return 0;
}
