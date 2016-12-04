#ifndef __MOVE__HPP__
#define __MOVE__HPP__

namespace tttbook
{
  typedef int coordinate_t;

  class move_c
  {
  private:

    coordinate_t x;
    coordinate_t y;

  public:

    move_c() noexcept
    {
      x = -1;
      y = -1;
    };

    move_c(coordinate_t x_init, coordinate_t y_init) noexcept
    {
      x = x_init;
      y = y_init;
    };

    void set(coordinate_t x_init, coordinate_t y_init) noexcept
    {
      x = x_init;
      y = y_init;
    };

    coordinate_t get_x() const noexcept
    {
      return x;
    };

    coordinate_t get_y() const noexcept
    {
      return y;
    };

    friend std::ostream& operator<< (std::ostream&, const move_c&);
  };

}

#endif
