#include "tttbook.hpp"

namespace tttbook
{

  void page_c::init_page(void) noexcept
  {
    for(move_coordinate_t x = 0; x < size; x++)
      for(move_coordinate_t y = 0; y < size; y++)
        go_to_indexes[x][y] = null_page_index;
    page_index = null_page_index;
    shuffle_index = null_page_index;
    do_play = true;
  }

  std::ostream& operator<<(std::ostream& out, const page_c& self)
  {
    out << (board_c)self;

    for(move_coordinate_t y = 0; y < self.size; y++)
    {
      if(y != 0)
        out << std::endl << "-------+-------+-------" << std::endl;
      for(move_coordinate_t x = 0; x < self.size; x++)
      {
        if(x != 0)
          out << " |";
        out << ' ' << std::setw(5) << self.go_to_indexes[x][y];
      }
    }
    out <<
      std::endl <<
      "Page index: " << self.page_index << std::endl <<
      "Shuffle index: " << self.shuffle_index << std::endl <<
      "Do play: " << std::boolalpha << self.do_play << std::endl <<
      "Last move: " << self.last_move << std::endl;

    return out;
  }

}
