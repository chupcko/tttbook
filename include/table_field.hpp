#ifndef __TABLE_FIELD__HPP__
#define __TABLE_FIELD__HPP__

namespace tttbook
{
  class table_field
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

    table_field() noexcept
    {
      set_empty();
    };

    void set_empty() noexcept
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

    bool is_empty() const noexcept
    {
      return value == FIELD_EMPTY;
    };

    friend std::ostream& operator<< (std::ostream&, const table_field&);

  };
}

#endif
