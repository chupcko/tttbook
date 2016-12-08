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
  book.set_worst_gate(0.5);
  book.set_book_as_second();

  book.fill();
  book.shuffle();

  cout << book;
  return 0;
}
