#ifndef __PAGE__HPP__
#define __PAGE__HPP__

namespace tttbook
{

  typedef int page_index_t;

  class page_c
  {
    public:

      const page_index_t null_page_index = -1;

      board_c board;
      page_index_t next_indexes[board_c::size][board_c::size];

    public:

      page_c(void) noexcept
      {
        init();
      }

      void init(void) noexcept;

      friend std::ostream& operator<< (std::ostream&, const page_c&);
  };

}

#endif
