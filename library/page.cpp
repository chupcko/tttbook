#include "tttbook.hpp"

namespace tttbook
{

  void page_c::init_next_indexes(void) noexcept
  {
    for(move_coordinate_t x = 0; x < size; x++)
      for(move_coordinate_t y = 0; y < size; y++)
        next_indexes[x][y] = null_page_index;
  }

  std::ostream& operator<< (std::ostream& out, const page_c& self)
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
        out << ' ' << std::setw(5) << self.next_indexes[x][y];
      }
    }
    out << std::endl;
    return out;
  }

}
