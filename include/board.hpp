#ifndef __BOARD__HPP__
#define __BOARD__HPP__

namespace tttbook
{
  typedef long board_hash_t;

  class board_c
  {
    public:

      static const move_coordinate_t size = 3;

      status_c status;
      field_c fields[size][size];
      player_c player;

    private:

      bool recalculate_status_is_draw(void) const noexcept;
      bool recalculate_status_is_win(field_c::field_t) const noexcept;
      void recalculate_status(void) noexcept;

    public:

      board_c(void) noexcept
      {
        init_board();
      };

      board_c(const board_c&) noexcept;
      void init_board(void) noexcept;
      const status_c& play(move_c);
      board_hash_t hash() const noexcept;

      friend std::ostream& operator<<(std::ostream&, const board_c&);
  };

}

#endif