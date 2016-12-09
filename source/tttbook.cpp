#include <exception>
#include <iostream>

#include "tttbook.hpp"

using namespace std;
using namespace tttbook;

int main(void)
{
  book_c book;
  book.set_best_speed_fast();
  book.set_select_first();
  book.set_worst_best_gate(0.0);
  book.set_book_as_second();

  book.fill();
//  book.shuffle(5);

  book.write_ps(cout);
  return 0;
}
