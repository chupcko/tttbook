#ifndef __SOLVER__HPP__
#define __SOLVER__HPP__

namespace TTTbook
{

  class solver_c
  {
    public:

      enum select_t
      {
        SELECT_RANDOM = 0,
        SELECT_FIRST = 1,
        SELECT_LAST = 2
      };

      enum best_speed_t
      {
        BEST_SPEED_FAST = 0,
        BEST_SPEED_SLOW = 1
      };

      double worst_best_rate;
      select_t select;
      best_speed_t best_speed;

    private:

      int rate(const board_c&) const noexcept;
      move_c* best_move(const board_c&) const;
      move_c* worst_move(const board_c&) const;

    public:

      solver_c() noexcept
      {
        set_worst_best_rate(0.0);
        set_select_random();
        set_best_speed_fast();
      }

      void set_worst_best_rate(double worst_best_rate_init) noexcept
      {
        worst_best_rate = worst_best_rate_init;
        if(std::isnan(worst_best_rate))
          worst_best_rate = 0.0;
        else if(worst_best_rate < 0.0)
          worst_best_rate = 0.0;
        else if(worst_best_rate > 1.0)
          worst_best_rate = 1.0;
      }

      void set_select_random() noexcept
      {
        select = SELECT_RANDOM;
      }

      void set_select_first() noexcept
      {
        select = SELECT_FIRST;
      }

      void set_select_last() noexcept
      {
        select = SELECT_LAST;
      }

      void set_best_speed_fast() noexcept
      {
        best_speed = BEST_SPEED_FAST;
      }

      void set_best_speed_slow() noexcept
      {
        best_speed = BEST_SPEED_SLOW;
      }

      move_c* calculate_move(const board_c&) const;
      void info(std::ostream&) const noexcept;
  };

}

#endif
