#ifndef __MOVE__HPP__
#define __MOVE__HPP__

namespace tttbook
{

  typedef int move_coordinate_t;

  class move_c
  {
    public:

      move_coordinate_t x;
      move_coordinate_t y;

      move_c(void) noexcept
      {
        x = -1;
        y = -1;
      };

      move_c(move_coordinate_t x_init, move_coordinate_t y_init) noexcept
      {
        x = x_init;
        y = y_init;
      };

      move_c(const move_c& move_init)
      {
        x = move_init.x;
        y = move_init.y;
      };

      void set(move_coordinate_t x_init, move_coordinate_t y_init) noexcept
      {
        x = x_init;
        y = y_init;
      };

      bool is(move_coordinate_t x_init, move_coordinate_t y_init) noexcept
      {
        return
          x == x_init &&
          y == y_init;
      };

      friend std::ostream& operator<<(std::ostream&, const move_c&);
  };

}

#endif
