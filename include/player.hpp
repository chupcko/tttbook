#ifndef __PLAYER__HPP__
#define __PLAYER__HPP__

namespace tttbook
{

  class player_c
  {
    public:

      enum player_t
      {
        PLAYER_X = 1,
        PLAYER_O = 2
      };

      player_t player;

      player_c(void) noexcept
      {
        set_x();
      };

      void set_x(void) noexcept
      {
        player = PLAYER_X;
      };

      void set_o(void) noexcept
      {
        player = PLAYER_O;
      };

      bool is_x(void) const noexcept
      {
        return player == PLAYER_X;
      };

      bool is_o(void) const noexcept
      {
        return player == PLAYER_O;
      };

      void next(void) noexcept;

      friend std::ostream& operator<<(std::ostream&, const player_c&);
  };

}

#endif
