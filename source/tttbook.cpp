#include <exception>
#include <iostream>

#include "tttbook.hpp"

using namespace std;
using namespace TTTbook;

int main()
{
  book_c book;
  book.set_best_speed_fast();
  book.set_select_first();
  book.set_worst_best_gate(1.0);
  book.book_play_second();
  book.do_not_show_last_move();

  book.fill();
//  book.shuffle(5);

  book.write_ps(cout);
  return 0;
}
