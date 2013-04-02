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

    field()
    {
      value = FIELD_EMPTY;
    };

    void clean()
    {
      value = FIELD_EMPTY;
    };

    void play_as_x()
    {
      value = FIELD_X;
    };

    void play_as_o()
    {
      value = FIELD_O;
    };

    field_t get_value() const
    {
      return value;
    };

    bool is_clean() const
    {
      return value == FIELD_EMPTY;
    };

    friend std::ostream& operator<< (std::ostream&, const field&);

  };
}

#endif
