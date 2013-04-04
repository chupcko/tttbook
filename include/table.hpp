#ifndef __TABLE_HPP__
#define __TABLE_HPP__

namespace tttbook
{
  class table
  {
  public:

    class error : std::exception
    {
    };
    
    class error_index : error
    {
      const char* what() const noexcept
      {
        return "Bad index";
      }
    };

    class error_filled : error
    {
      const char* what() const noexcept
      {
        return "Already filled";
      }
    };

    enum gamer_t
    {
      GAMER_X = 1,
      GAMER_O = 2
    };
    static const int size = 3;

  private:

    field fields[size][size];
    gamer_t on_move;
    std::array<std::pair<int, int>, size*size> moves;
    int moves_number;

    bool is_win_helper(field::field_t field_value) const noexcept;

  public:

    table() noexcept
    {
      init();
    };

    void init() noexcept;
    void play(int x, int y);
    bool is_draw() const noexcept;

    bool is_win(gamer_t who) const noexcept
    {
      switch(who)
      {
        case GAMER_X:
          return is_win_helper(field::FIELD_X);
        case GAMER_O:
          return is_win_helper(field::FIELD_O);
      }
    };

    bool is_win_x() const noexcept
    {
      return is_win_helper(field::FIELD_X);
    };

    bool is_win_o() const noexcept
    {
      return is_win_helper(field::FIELD_O);
    };

    friend std::ostream& operator<< (std::ostream&, const table&);

  };
}

#endif
