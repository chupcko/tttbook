#ifndef __GAME__HPP__
#define __GAME__HPP__

namespace tttbook
{

  class game_c
  {
  private:

    board_c board;

  public:

    game_c() noexcept
    {
      init();
    };

    void init() noexcept;
    const move_c* best_move();

    friend std::ostream& operator<< (std::ostream&, const game_c&);
  };

}

#endif
