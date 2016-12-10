#ifndef __STATUS__HPP__
#define __STATUS__HPP__

namespace TTTbook
{

  class status_c
  {
    public:

      enum status_t
      {
        STATUS_NEW,
        STATUS_PLAY,
        STATUS_DRAW,
        STATUS_WIN_X,
        STATUS_WIN_O
      };

      status_t status;

      status_c() noexcept
      {
        set_new();
      }

      void set_new() noexcept
      {
        status = STATUS_NEW;
      }

      void set_play() noexcept
      {
        status = STATUS_PLAY;
      }

      void set_draw() noexcept
      {
        status = STATUS_DRAW;
      }

      void set_win_x() noexcept
      {
        status = STATUS_WIN_X;
      }

      void set_win_o() noexcept
      {
        status = STATUS_WIN_O;
      }

      bool is_new() const noexcept
      {
        return status == STATUS_NEW;
      }

      bool is_play() const noexcept
      {
        return status == STATUS_PLAY;
      }

      bool is_draw() const noexcept
      {
        return status == STATUS_DRAW;
      }

      bool is_win_x() const noexcept
      {
        return status == STATUS_WIN_X;
      }

      bool is_win_o() const noexcept
      {
        return status == STATUS_WIN_O;
      }

      bool is_playable() const noexcept
      {
        return status == STATUS_NEW || status == STATUS_PLAY;
      }

      friend std::ostream& operator<<(std::ostream&, const status_c&);
  };

}

#endif
