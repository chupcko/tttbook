#ifndef __BOOK__HPP__
#define __BOOK__HPP__

namespace TTTbook
{

  class book_c
  : public solver_c
  {
    public:

      std::vector<page_c*> pages;
      std::map<board_hash_t, page_index_t> shortcuts;
      std::deque<page_index_t> unpublished_pages;
      bool book_is_first;
      bool showing_last_move;
      page_index_t shuffle_begin_index;

    private:

      page_index_t find_page(board_c&, bool) noexcept;
      void fill_init_book_as_first() noexcept;
      void fill_init_book_as_second() noexcept;

    public:

      book_c() noexcept
      {
        book_play_second();
        do_not_show_last_move();
        shuffle_begin_index = page_c::null_page_index;
      }

      void book_play_first() noexcept
      {
        book_is_first = true;
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

      void clear() noexcept;
      void fill() noexcept;
      void shuffle(int) noexcept;
      void write_ps(std::ostream&) const noexcept;

      friend std::ostream& operator<<(std::ostream&, const book_c&);
  };

}

#endif
