#ifndef __TABLE_HPP__
#define __TABLE_HPP__

namespace tttbook
{
  class table
  {
  public:

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

    bool is_win_helper(field::field_t field_value) const;

  public:

    table()
    {
      init();
    };

    void init();
    bool play(int x, int y);
    bool is_draw() const;

    bool is_win(gamer_t who) const
    {
      switch(who)
      {
        case GAMER_X:
          return is_win_helper(field::FIELD_X);
        case GAMER_O:
          return is_win_helper(field::FIELD_O);
      }
    };

    bool is_win_x() const
    {
      return is_win_helper(field::FIELD_X);
    };

    bool is_win_o() const
    {
      return is_win_helper(field::FIELD_O);
    };

    friend std::ostream& operator<< (std::ostream&, const table&);

  };
}

#endif
