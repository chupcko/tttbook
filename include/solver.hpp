#ifndef __SOLVER__HPP__
#define __SOLVER__HPP__

namespace tttbook
{

  class solver_c
  {
    public:

      enum best_speed_t
      {
        BEST_FAST = 0,
        BEST_SLOW = 1
      };

      enum select_t
      {
        RANDOM = 0,
        FIRST = 1,
        LAST = 2
      };

      best_speed_t best_speed;
      select_t select;
      double worst_best_gate;

    private:

      int rate(const board_c&) const noexcept;
      move_c* best_move(const board_c&) const;
      move_c* worst_move(const board_c&) const;

    public:

      solver_c() noexcept
      {
        set_best_speed_fast();
        set_select_random();
        set_worst_best_gate(0.0);
      }

      void set_best_speed_fast() noexcept
      {
        best_speed = BEST_FAST;
      }

      void set_best_speed_slow() noexcept
      {
        best_speed = BEST_SLOW;
      }

      void set_select_random() noexcept
      {
        select = RANDOM;
      }

      void set_select_first() noexcept
      {
        select = FIRST;
      }

      void set_select_last() noexcept
      {
        select = LAST;
      }

      void set_worst_best_gate(double worst_best_gate_init) noexcept
      {
        worst_best_gate = worst_best_gate_init;
        if(std::isnan(worst_best_gate))
          worst_best_gate = 0.0;
        else if(worst_best_gate < 0.0)
          worst_best_gate = 0.0;
        else if(worst_best_gate > 1.0)
          worst_best_gate = 1.0;
      }

      move_c* calculate_move(const board_c&) const;
  };

}

#endif
