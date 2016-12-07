#include "tttbook.hpp"

namespace tttbook
{

  void page_c::init(void) noexcept
  {
    for(move_coordinate_t x = 0; x < board_c::size; x++)
      for(move_coordinate_t y = 0; y < board_c::size; y++)
        next_indexes[x][y] = null_page_index;
  }

  std::ostream& operator<< (std::ostream& out, const page_c& self)
  {
    out << self.board;
    /*#*/
    return out;
  }

}
