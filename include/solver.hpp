#ifndef __SOLVER__HPP__
#define __SOLVER__HPP__

namespace tttbook
{

  class solver_c : public board_c
  {
    public:

      enum speed_t
      {
        FAST = 0,
        SLOW = 1
      };

      enum select_t
      {
        FIRST = 0,
        RANDOM = 1,
        LAST = 2
      };

      speed_t speed;
      select_t select;

    private:

      int rate(void) const noexcept;
      int random(int, int) const noexcept;

    public:

      solver_c(void)
      {
        set_fast_speed();
        set_first_select();
      }

      solver_c(const solver_c* solver_init) : board_c(solver_init)
      {
        speed = solver_init->speed;
        select = solver_init->select;
      }

      void set_fast_speed(void) noexcept
      {
        speed = FAST;
      }

      void set_slow_speed(void) noexcept
      {
        speed = SLOW;
      }

      void set_first_select(void) noexcept
      {
        select = FIRST;
      }

      void set_random_select(void) noexcept
      {
        select = RANDOM;
      }

      void set_last_select(void) noexcept
      {
        select = LAST;
      }

      move_c* best_move(void) const;
  };

}

#endif
