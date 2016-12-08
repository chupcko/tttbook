#ifndef __BOOK__HPP__
#define __BOOK__HPP__

namespace tttbook
{

  class book_c
  : public solver_c
  {
    public:

      std::vector<page_c*> pages;
      std::map<board_hash_t, page_index_t> shortcuts;
      std::deque<page_index_t> unpublished_pages;
      bool book_is_first;
      page_index_t shuffle_begin_index;

    private:

      page_index_t find_page(board_c&) noexcept;
      void fill_init_book_as_first(void) noexcept;
      void fill_init_book_as_second(void) noexcept;

    public:

      book_c(void) noexcept
      {
        set_book_as_first();
        shuffle_begin_index = page_c::null_page_index;
      };

      void set_book_as_first(void) noexcept
      {
        book_is_first = true;
      };

      void set_book_as_second(void) noexcept
      {
        book_is_first = false;
      };

      void clear(void) noexcept;
      void fill(void) noexcept;
      void shuffle(void) noexcept;

      friend std::ostream& operator<<(std::ostream&, const book_c&);
  };

}

#endif
