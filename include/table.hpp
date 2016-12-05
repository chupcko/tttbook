#ifndef __TABLE__HPP__
#define __TABLE__HPP__

namespace tttbook
{

  class table_c
  {
  public:

    static const coordinate_t size = 3;

  private:

    status_c status;
    field_c fields[size][size];
    player_c player;
    move_c moves[size*size];
    int moves_number;

    bool recalculate_status_is_draw() const noexcept;
    bool recalculate_status_is_win(field_c::field_t field_value) const noexcept;
    void recalculate_status() noexcept;

  public:

    table_c() noexcept
    {
      init();
    };

    void init() noexcept;

    bool is_playable() const noexcept
    {
      return status.is_playable();
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

    const status_c& play(coordinate_t x, coordinate_t y);
    friend std::ostream& operator<< (std::ostream&, const table_c&);
  };

}

#endif
