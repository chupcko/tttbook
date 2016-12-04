#ifndef __FIELD__HPP__
#define __FIELD__HPP__

namespace tttbook
{
  class field_c
  {
  public:

    enum field_t
    {
      FIELD_EMPTY = 0,
      FIELD_X     = 1,
      FIELD_O     = 2
    };

  private:

    field_t value;

  public:

    field_c() noexcept
    {
      set_empty();
    };

    void set_empty() noexcept
    {
      value = FIELD_EMPTY;
    };

    void set_x() noexcept
    {
      value = FIELD_X;
    };

    void set_o() noexcept
    {
      value = FIELD_O;
    };

    field_t get_value() const noexcept
    {
      return value;
    };

    bool is_empty() const noexcept
    {
      return value == FIELD_EMPTY;
    };

    bool is_x() const noexcept
    {
      return value == FIELD_X;
    };

    bool is_o() const noexcept
    {
      return value == FIELD_O;
    };

    void fill(player_c player) noexcept
    {
      if(player.is_x())
        set_x();
      if(player.is_o())
        set_o();
    }

    friend std::ostream& operator<< (std::ostream&, const field_c&);
  };

}

#endif
