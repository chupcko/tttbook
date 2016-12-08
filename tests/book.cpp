#include <exception>
#include <iostream>

#include "tttbook.hpp"

using namespace std;
using namespace tttbook;

int main(void)
{
  book_c book;
  book.set_slow_speed();
  book.set_random_select();
//  book.set_book_as_first();
  book.set_book_as_second();
  book.fill();
  cout << endl << endl;
  cout << book;
  return 0;
}
