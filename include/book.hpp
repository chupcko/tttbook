#ifndef __BOOK__HPP__
#define __BOOK__HPP__

namespace TTTbook
{

  class book_c :
    public solver_c
  {
    public:

      static const int shuffle_count_max = 10;

      std::vector<page_c*> pages;
      std::map<board_c::hash_t, page_c::index_t> shortcuts_before_play;
      std::map<board_c::hash_t, page_c::index_t> shortcuts_after_play;
      std::deque<page_c::index_t> unpublished_pages;
      bool book_is_first;
      move_c first_move;
      bool showing_last_move;
      bool showing_marks;
      int shuffle_count;

    private:

      page_c::index_t find_page(board_c&, bool) noexcept;
      void fill_init_book_as_first() noexcept;
      void fill_init_book_as_second() noexcept;
      void shuffle(page_c::index_t) noexcept;
      int statistic_draw;
      int statistic_win_x;
      int statistic_win_o;

    public:

      book_c() noexcept
      {
        book_play_second();
        do_not_show_last_move();
        do_not_show_marks();
        set_shuffle_count(-1);
        statistic_draw = 0;
        statistic_win_x = 0;
        statistic_win_o = 0;
      }

      void book_play_first(move_c first_move_init) noexcept
      {
        book_is_first = true;
        first_move = first_move_init;
        first_move.normalize(board_c::size);
      }

      void book_play_first(move_c::coordinate_t x, move_c::coordinate_t y) noexcept
      {
        book_is_first = true;
        first_move = move_c(x, y);
        first_move.normalize(board_c::size);
      }

      void book_play_second() noexcept
      {
        book_is_first = false;
      }

      void show_last_move() noexcept
      {
        showing_last_move = true;
      }

      void do_not_show_last_move() noexcept
      {
        showing_last_move = false;
      }

      void show_marks() noexcept
      {
        showing_marks = true;
      }

      void do_not_show_marks() noexcept
      {
        showing_marks = false;
      }

      void set_shuffle_count(int shuffle_count_init) noexcept
      {
        shuffle_count = shuffle_count_init;
        if(shuffle_count > shuffle_count_max)
          shuffle_count = shuffle_count_max;
      }

      void clear() noexcept;
      void fill() noexcept;
      void write_ps(std::ostream&) const noexcept;
      void info(std::ostream&) const noexcept;

      friend std::ostream& operator<<(std::ostream&, const book_c&);
  };

}

#endif
