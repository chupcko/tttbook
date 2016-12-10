#ifndef __FIELD__HPP__
#define __FIELD__HPP__

namespace TTTbook
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

      field_t field;

      field_c() noexcept
      {
        set_empty();
      }

      void set_empty() noexcept
      {
        field = FIELD_EMPTY;
      }

      void set_x() noexcept
      {
        field = FIELD_X;
      }

      void set_o() noexcept
      {
        field = FIELD_O;
      }

      bool is_empty() const noexcept
      {
        return field == FIELD_EMPTY;
      }

      bool is_x() const noexcept
      {
        return field == FIELD_X;
      }

      bool is_o() const noexcept
      {
        return field == FIELD_O;
      }

      bool is(field_t value) const noexcept
      {
        return field == value;
      }

      void fill(player_c) noexcept;

      friend std::ostream& operator<<(std::ostream&, const field_c&);
  };

}

#endif
