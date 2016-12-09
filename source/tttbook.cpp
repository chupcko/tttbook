#include <exception>
#include <iostream>

#include "tttbook.hpp"

using namespace std;
using namespace tttbook;

int main(void)
{
  book_c book;
  book.set_best_speed_fast();
  book.set_select_random();
  book.set_worst_best_gate(0.3);
  book.set_book_as_first();

  book.fill();
  book.shuffle(5);

  book.write_ps(cout);
  return 0;
}
