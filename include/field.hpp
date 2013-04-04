#ifndef __FIELD_HPP__
#define __FIELD_HPP__

namespace tttbook
{
  class field
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

    field() noexcept
    {
      value = FIELD_EMPTY;
    };

    void clean() noexcept
    {
      value = FIELD_EMPTY;
    };

    void play_as_x() noexcept
    {
      value = FIELD_X;
    };

    void play_as_o() noexcept
    {
      value = FIELD_O;
    };

    field_t get_value() const noexcept
    {
      return value;
    };

    bool is_clean() const noexcept
    {
      return value == FIELD_EMPTY;
    };

    friend std::ostream& operator<< (std::ostream&, const field&);

  };
}

#endif
