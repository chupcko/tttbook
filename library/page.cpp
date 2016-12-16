#include "tttbook.hpp"

namespace TTTbook
{

  void page_c::init() noexcept
  {
    for(move_c& move : all_moves)
      go_to_indexes[move.x][move.y] = null_index;
    page_index = null_index;
    shuffle_index = null_index;
    last_move_is_set = false;
  }

  std::ostream& operator<<(std::ostream& out, const page_c& self)
  {
    #define LENGTH 5

    out << (board_c)self;
    for(move_c::coordinate_t y : move_c::all_coordinates_c(self.size))
    {
      if(y != 0)
        out << "\n-" REPEAT(LENGTH, "-") "-+-" REPEAT(LENGTH, "-") "-+-" REPEAT(LENGTH, "-") "-\n";
      for(move_c::coordinate_t x : move_c::all_coordinates_c(self.size))
      {
        if(x != 0)
          out << " |";
        out << ' ' << std::setw(LENGTH) << self.go_to_indexes[x][y];
      }
    }
    out << std::boolalpha <<
      "\nPage index: " << self.page_index <<
      "\nShuffle index: " << self.shuffle_index <<
      "\nLast move is set: " << self.last_move_is_set <<
      "\nLast move: " << self.last_move << '\n';
    return out;
  }

}
