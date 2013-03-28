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
    field();
    void clean();
    void play_as_x();
    void play_as_o();
    field_t get_value() const;
    bool is_clean() const;
    friend std::ostream& operator<< (std::ostream&, const field&);
  };
}

#endif
