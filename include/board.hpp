#ifndef __BOARD__HPP__
#define __BOARD__HPP__

namespace tttbook
{

  class board_c
  {
    public:

      static const coordinate_t size = 3;
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
        init();
      };

      board_c(const board_c* board_init) noexcept
      {
        status = board_init->status;
        for(coordinate_t x = 0; x < size; x++)
          for(coordinate_t y = 0; y < size; y++)
            fields[x][y] = board_init->fields[x][y];
        player = board_init->player;
      }

      void init(void) noexcept;
      const status_c& play(move_c move);

      friend std::ostream& operator<< (std::ostream&, const board_c&);
  };

  bool operator== (const board_c&, const board_c&);
  bool operator!= (const board_c&, const board_c&);

}

#endif
