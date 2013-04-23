#ifndef __TABLE_STATUS__HPP__
#define __TABLE_STATUS__HPP__

namespace tttbook
{
  class table_status
  {
  public:

    enum status_t
    {
      STATUS_IN_GAME,
      STATUS_DRAW,
      STATUS_WIN_X,
      STATUS_WIN_O
    };

  private:

    status_t value;

  public:

    table_status() noexcept
    {
      set_in_game();
    };

    void set_in_game() noexcept
    {
      value = STATUS_IN_GAME;
    };

    void set_draw() noexcept
    {
      value = STATUS_DRAW;
    }

    void set_win_x() noexcept
    {
      value = STATUS_WIN_X;
    }

    void set_win_o() noexcept
    {
      value = STATUS_WIN_O;
    }

    status_t get_value() const noexcept
    {
      return value;
    };

    bool is_in_game() const noexcept
    {
      return value == STATUS_IN_GAME;
    };

    bool is_draw() const noexcept
    {
      return value == STATUS_DRAW;
    };

    bool is_win_x() const noexcept
    {
      return value == STATUS_WIN_X;
    };

    bool is_win_o() const noexcept
    {
      return value == STATUS_WIN_O;
    };

    friend std::ostream& operator<< (std::ostream&, const table_status&);

  };
}

#endif
