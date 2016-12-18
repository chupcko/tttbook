#ifndef __SOLVER__HPP__
#define __SOLVER__HPP__

namespace TTTbook
{

  class solver_c
  {
    public:

      typedef int rate_t;

      enum type_t
      {
        TYPE_NORMAL,
        TYPE_REVERSE
      };

      enum select_t
      {
        SELECT_RANDOM = 0,
        SELECT_FIRST = 1,
        SELECT_LAST = 2
      };

      enum speed_t
      {
        SPEED_FAST = 0,
        SPEED_SLOW = 1
      };

      type_t type;
      int guaranteed_best;
      double best_weight;
      double modest_weight;
      double worst_weight;
      select_t select;
      speed_t speed;

    private:

      double normalize_weight(double weight) const noexcept
      {
        if
        (
          std::isnan(weight) ||
          weight < 0.0
        )
          return 0.0;
        return weight;
      }

      rate_t rate(const board_c&) const noexcept;
      bool compare_rate(rate_t, rate_t) const noexcept;
      move_c* best_move(const board_c&) const;
      move_c* modest_normal_move(const board_c&) const;
      move_c* modest_reverse_move(const board_c&) const;
      move_c* worst_move(const board_c&) const;

    public:

      solver_c() noexcept
      {
        set_type_normal();
        guaranteed_best = 0;
        set_best_weight(1.0);
        set_modest_weight(0.0);
        set_worst_weight(0.0);
        set_select_random();
        set_speed_fast();
      }

      void set_type_normal() noexcept
      {
        type = TYPE_NORMAL;
      }

      void set_type_reverse() noexcept
      {
        type = TYPE_REVERSE;
      }

      void set_guaranteed_best(int guaranteed_best_init) noexcept
      {
        guaranteed_best = guaranteed_best_init;
      }

      void set_best_weight(double weight) noexcept
      {
        best_weight = normalize_weight(weight);
      }

      void set_modest_weight(double weight) noexcept
      {
        modest_weight = normalize_weight(weight);
      }

      void set_worst_weight(double weight) noexcept
      {
        worst_weight = normalize_weight(weight);
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

      void set_speed_fast() noexcept
      {
        speed = SPEED_FAST;
      }

      void set_speed_slow() noexcept
      {
        speed = SPEED_SLOW;
      }

      bool is_type_normal() const noexcept
      {
        return type == TYPE_NORMAL;
      }

      bool is_type_reverse() const noexcept
      {
        return type == TYPE_REVERSE;
      }

      move_c* calculate_move(const board_c&) const;
      void info(std::ostream&) const noexcept;

      friend std::ostream& operator<<(std::ostream&, const solver_c&);
  };

}

#endif
