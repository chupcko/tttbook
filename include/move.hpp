#ifndef __MOVE__HPP__
#define __MOVE__HPP__

namespace TTTbook
{

  class move_c
  {
    public:

      typedef int coordinate_t;

      coordinate_t x;
      coordinate_t y;

      move_c() noexcept
      {
        x = -1;
        y = -1;
      }

      move_c(coordinate_t x_init, coordinate_t y_init) noexcept
      {
        x = x_init;
        y = y_init;
      }

      move_c(const move_c& move_init)
      {
        x = move_init.x;
        y = move_init.y;
      }

      void set(coordinate_t x_init, coordinate_t y_init) noexcept
      {
        x = x_init;
        y = y_init;
      }

      void set(const move_c& move_init) noexcept
      {
        x = move_init.x;
        y = move_init.y;
      }

      bool is(coordinate_t x_init, coordinate_t y_init) const noexcept
      {
        return
          x == x_init &&
          y == y_init;
      }

      static coordinate_t normalize(coordinate_t size, coordinate_t xy) noexcept
      {
        if(xy < 0)
          return 0;
        if(xy >= size)
          return size-1;
        return xy;
      }

      void normalize(coordinate_t size) noexcept
      {
        x = normalize(size, x);
        y = normalize(size, y);
      }

      friend std::ostream& operator<<(std::ostream&, const move_c&);
  };

}

#endif
