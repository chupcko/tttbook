#ifndef __STATUS__HPP__
#define __STATUS__HPP__

namespace tttbook
{
  class status_c
  {
  public:

    enum status_t
    {
      STATUS_PLAYABLE,
      STATUS_DRAW,
      STATUS_WIN_X,
      STATUS_WIN_O
    };

  private:

    status_t value;

  public:

    status_c() noexcept
    {
      set_playable();
    };

    void set_playable() noexcept
    {
      value = STATUS_PLAYABLE;
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

    bool is_playable() const noexcept
    {
      return value == STATUS_PLAYABLE;
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

    friend std::ostream& operator<< (std::ostream&, const status_c&);
  };

}

#endif
