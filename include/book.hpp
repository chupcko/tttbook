#ifndef __BOOK__HPP__
#define __BOOK__HPP__

namespace tttbook
{

  class book_c
  : solver_c
  {
    public:

      std::vector<page_c> pages;
      std::map<board_hash_t, page_index_t> shortcuts;
      std::deque<page_index_t> unpublished_pages;
      bool book_is_first;

      book_c(void) noexcept
      {
        set_book_as_first();
      };
    private:

      page_index_t find_page(board_c& board) noexcept;

    public:

      void set_book_as_first() noexcept;
      void set_book_as_second() noexcept;
      void fill(void) noexcept;

      friend std::ostream& operator<< (std::ostream&, const book_c&);
  };

}

#endif
