#include <iostream>

#include "field.cpp"

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

  int is_win_helper(field::field_t field_value)
  {
    int all;
    
    for(int x = 0; x < size; x++)
    {
      all = 1;
      for(int y = 0; y < size; y++)
        if(fields[x][y].get_value() != field_value)
        {
          all = 0;
          break;
        }
      if(all)
        return 1;
      all = 1;
      for(int y = 0; y < size; y++)
        if(fields[y][x].get_value() != field_value)
        {
          all = 0;
          break;
        }
      if(all)
        return 1;
    }
    all = 1;
    for(int x = 0; x < size; x++)
      if(fields[x][x].get_value() != field_value)
      {
        all = 0;
        break;
      }
    if(all)
      return 1;
    for(int x = 0; x < size; x++)
      if(fields[x][size-1-x].get_value() != field_value)
      {
        all = 0;
        break;
      }
    if(all)
      return 1;
    return 0;
  }

public:

  table()
  {
    init();
  };
  
  void init()
  {
    for(int x = 0; x < size; x++)
      for(int y = 0; y < size; y++)
        fields[x][y].clean();
    on_move = GAMER_X;
  }

  int play(int x, int y)
  {
    if
    (
      x < 0 ||
      x >= size ||
      y < 0 ||
      y >= size ||
      !fields[x][y].is_clean()
    )
      return 0;

    switch(on_move)
    {
      case GAMER_X:
        fields[x][y].play_as_x();
        on_move = GAMER_O;
        break;
      case GAMER_O:
        fields[x][y].play_as_o();
        on_move = GAMER_X;
        break;
    }
    return 1;
  }

  int is_draw()
  {
    for(int x = 0; x < size; x++)
      for(int y = 0; y < size; y++)
        if(fields[x][y].is_clean())
          return 0;
    return 1;
  }
  
  int is_win(gamer_t who)
  {
    switch(who)
    {
      case GAMER_X:
        return is_win_helper(field::FIELD_X);
      case GAMER_O:
        return is_win_helper(field::FIELD_O);
    }
  }

  int is_win_x()
  {
    return is_win_helper(field::FIELD_X);
  }

  int is_win_o()
  {
    return is_win_helper(field::FIELD_O);
  }

  friend std::ostream& operator<< (std::ostream& out, const table& self)
  {
    for(int x = 0; x < size; x++)
    {
      for(int y = 0; y < size; y++)
      {
        out << " " << self.fields[x][y];
        if(y != size-1)
          out << " |";
      }
      if(x != size-1)
        out << "\n---+---+---\n";
    }
    out << "\n";
    return out;
  };

};
