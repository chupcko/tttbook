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

      int guaranteed_best;
      double best_weight;
      double modest_weight;
      double worst_weight;
      select_t select;
      best_speed_t best_speed;

    private:

      int best_rate(const board_c&) const noexcept;
      move_c* best_move(const board_c&) const;
      move_c* modest_move(const board_c&) const;
      move_c* worst_move(const board_c&) const;

    public:

      solver_c() noexcept
      {
        guaranteed_best = 0;
        set_best_weight(1.0);
        set_modest_weight(0.0);
        set_worst_weight(0.0);
        set_select_random();
        set_best_speed_fast();
      }

      void set_guaranteed_best(int guaranteed_best_init) noexcept
      {
        guaranteed_best = guaranteed_best_init;
      }

      void set_best_weight(double weight) noexcept
      {
        best_weight = weight;
        if
        (
          std::isnan(best_weight) ||
          best_weight < 0.0
        )
          best_weight = 0.0;
      }

      void set_modest_weight(double weight) noexcept
      {
        modest_weight = weight;
        if
        (
          std::isnan(modest_weight) ||
          modest_weight < 0.0
        )
          modest_weight = 0.0;
      }

      void set_worst_weight(double weight) noexcept
      {
        worst_weight = weight;
        if
        (
          std::isnan(worst_weight) ||
          worst_weight < 0.0
        )
          worst_weight = 0.0;
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
