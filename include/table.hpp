#ifndef __TABLE_HPP__
#define __TABLE_HPP__

namespace tttbook
{

#define MAKE_ERROR(name, text)      \
class name : error                  \
{                                   \
  const char* what() const noexcept \
  {                                 \
    return text;                    \
  }                                 \
}                                   \

  class table
  {
  public:

    class error : std::exception
    {
    };

    MAKE_ERROR(error_index,  "Bad index");
    MAKE_ERROR(error_filled, "Already filled");
    MAKE_ERROR(error_status, "Bad status");

    static const int size = 3;
    enum gamer_t
    {
      GAMER_X = 1,
      GAMER_O = 2
    };

  private:

    table_status status;
    table_field fields[size][size];
    gamer_t on_move;
    std::array<std::pair<int, int>, size*size> moves;
    int moves_number;

    bool helper_is_draw() const noexcept;
    bool helper_is_win(table_field::field_t field_value) const noexcept;
    void calculate_status() noexcept;

  public:

    table() noexcept
    {
      init();
    };

    void init() noexcept;
    const table_status& play(int x, int y);

    bool is_in_game() const noexcept
    {
      return status.is_in_game();
    }

    bool is_draw() const noexcept
    {
      return status.is_draw();
    }

    bool is_win_x() const noexcept
    {
      return status.is_win_x();
    };

    bool is_win_o() const noexcept
    {
      return status.is_win_o();
    };

    friend std::ostream& operator<< (std::ostream&, const table&);

  };
}

#endif
