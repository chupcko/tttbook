#ifndef __PLAYER__HPP__
#define __PLAYER__HPP__

namespace TTTbook
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

      player_c() noexcept
      {
        set_x();
      }

      void set_x() noexcept
      {
        player = PLAYER_X;
      }

      void set_o() noexcept
      {
        player = PLAYER_O;
      }

      bool is_x() const noexcept
      {
        return player == PLAYER_X;
      }

      bool is_o() const noexcept
      {
        return player == PLAYER_O;
      }

      void next() noexcept;

      friend std::ostream& operator<<(std::ostream&, const player_c&);
  };

}

#endif
