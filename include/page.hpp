#ifndef __PAGE__HPP__
#define __PAGE__HPP__

namespace tttbook
{

  typedef int page_index_t;

  class page_c
  : public board_c
  {
    public:

      const page_index_t null_page_index = -1;

      page_index_t go_to_indexes[board_c::size][board_c::size];
      page_index_t page_index;

    public:

      page_c(void) noexcept
      {
        init_next_indexes();
      }

      page_c(const board_c& board_init) noexcept
      : board_c(board_init)
      {
        init_next_indexes();
      }

      void init_next_indexes(void) noexcept;

      friend std::ostream& operator<< (std::ostream&, const page_c&);
  };

}

#endif
