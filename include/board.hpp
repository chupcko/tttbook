#ifndef __BOARD__HPP__
#define __BOARD__HPP__

namespace TTTbook
{

  class board_c
  {
    public:

      typedef long hash_t;

      class all_fields_c
      {
        public:

          class iterator_c
          {
            private:

              board_c* board;
              move_c::coordinate_t position;

            public:

              iterator_c(const board_c* board_init, move_c::coordinate_t position_init) noexcept
              {
                board = (board_c*)board_init;
                position = position_init;
              }

              bool operator!=(const iterator_c& other) const noexcept
              {
                return position != other.position;
              }

              field_c& operator*() const noexcept;
              const iterator_c& operator++() noexcept;
          };

          board_c* board;

          all_fields_c(board_c* board_init) noexcept
          {
            board = board_init;
          }

          iterator_c begin() const
          {
            return iterator_c(board, 0);
          }

          iterator_c end() const
          {
            return iterator_c(board, size*size);
          }
      };

      class all_moves_c
      {
        public:

          class iterator_c
          {
            private:

              board_c* board;
              move_c move;
              move_c::coordinate_t position;

            public:

              iterator_c(const board_c* board_init, move_c::coordinate_t position_init) noexcept
              {
                board = (board_c*)board_init;
                position = position_init;
                make_move();
              }

              bool operator!=(const iterator_c& other) const noexcept
              {
                return position != other.position;
              }

              move_c& operator*() const noexcept;
              const iterator_c& operator++() noexcept;
              void make_move() noexcept;
          };

          board_c* board;

          all_moves_c(board_c* board_init) noexcept
          {
            board = board_init;
          }

          iterator_c begin() const
          {
            return iterator_c(board, 0);
          }

          iterator_c end() const
          {
            return iterator_c(board, size*size);
          }
      };

      class all_moves_on_empty_c
      {
        public:

          class iterator_c
          {
            private:

              board_c* board;
              move_c move;
              move_c::coordinate_t position;

            public:

              iterator_c(const board_c* board_init, move_c::coordinate_t position_init) noexcept
              {
                board = (board_c*)board_init;
                position = position_init;
                while
                (
                  position < board->size*board->size &&
                  !board->fields[position%board->size][position/board->size].is_empty()
                )
                  position++;
                make_move();
              }

              bool operator!=(const iterator_c& other) const noexcept
              {
                return position != other.position;
              }

              move_c& operator*() const noexcept;
              const iterator_c& operator++() noexcept;
              void make_move() noexcept;
          };

          board_c* board;

          all_moves_on_empty_c(board_c* board_init) noexcept
          {
            board = board_init;
          }

          iterator_c begin() const
          {
            return iterator_c(board, 0);
          }

          iterator_c end() const
          {
            return iterator_c(board, size*size);
          }
      };

      static const move_c::coordinate_t size = 3;

      status_c status;
      field_c fields[size][size];
      player_c next_player;
      all_fields_c all_fields;
      all_moves_c all_moves;
      all_moves_on_empty_c all_moves_on_empty;

    private:

      bool is_win_in_row(move_c::coordinate_t, field_c::field_t) const noexcept;
      bool is_win_in_column(move_c::coordinate_t, field_c::field_t) const noexcept;
      bool is_win_in_diagonal(move_c::coordinate_t, field_c::field_t) const noexcept;
      bool recalculate_status_is_draw() const noexcept;
      bool recalculate_status_is_win(field_c::field_t) const noexcept;
      void recalculate_status() noexcept;

    public:

      board_c() noexcept :
        all_fields(this),
        all_moves(this),
        all_moves_on_empty(this)
      {
        init();
      }

      board_c(const board_c&) noexcept;
      void init() noexcept;
      bool is_win_in_row(move_c::coordinate_t) const noexcept;
      bool is_win_in_column(move_c::coordinate_t) const noexcept;
      bool is_win_in_diagonal(move_c::coordinate_t) const noexcept;
      void next() noexcept;
      const status_c& play(move_c);
      hash_t hash() const noexcept;

      friend std::ostream& operator<<(std::ostream&, const board_c&);
  };

}

#endif
