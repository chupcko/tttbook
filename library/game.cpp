#include "tttbook.hpp"

namespace tttbook
{

  void game_c::init() noexcept
  {
    table.init();
  }

  const move_c* game_c::best_move()
  {
    if(!table.is_playable())
      throw error_not_playable();
    move_c* move = new move_c(0, 0);
    return move;
  }

  std::ostream& operator<< (std::ostream& out, const game_c& self)
  {
    out << self.table;
    return out;
  }

}
