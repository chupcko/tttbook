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

  private:

    player_t value;

  public:

    player_c() noexcept
    {
      set_x();
    };

    void set_x() noexcept
    {
      value = PLAYER_X;
    };

    void set_o() noexcept
    {
      value = PLAYER_O;
    };

    player_t get_value() const noexcept
    {
      return value;
    };

    bool is_x() const noexcept
    {
      return value == PLAYER_X;
    };

    bool is_o() const noexcept
    {
      return value == PLAYER_O;
    };

    void next() noexcept
    {
      switch(value)
      {
        case PLAYER_X:
          value = PLAYER_O;
          break;
        case PLAYER_O:
          value = PLAYER_X;
          break;
      }
    };

    friend std::ostream& operator<< (std::ostream&, const player_c&);
  };

}

#endif
