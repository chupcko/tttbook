#include "tttbook.hpp"

namespace tttbook
{

  page_index_t book_c::find_page(board_c& board) noexcept
  {
    board_hash_t board_hash = board.hash();
    page_index_t page_index;

    if(shortcuts.count(board_hash) > 0)
      return shortcuts[board_hash];
    pages.push_back(page_c(board));
    page_index = (page_index_t)(pages.size()-1);
    pages[page_index].page_index = page_index;
    shortcuts[board_hash] = page_index;
    unpublished_pages.push_back(page_index);
    return page_index;
  }

  void book_c::set_book_as_first() noexcept
  {
    book_is_first = true;
    /*#*/
  }

  void book_c::set_book_as_second() noexcept
  {
    book_is_first = false;
    /*#*/
  };

  void book_c::fill(void) noexcept
  {
    page_index_t page_index;
    page_index_t go_to_page_index;

    while(!unpublished_pages.empty())
    {
      page_index = unpublished_pages.front();
      unpublished_pages.pop_front();

      if(!pages[page_index].status.is_new())
      {
        move_c* move = best_move((board_c)pages[page_index]);
        pages[page_index].play(*move);
        delete move;
      }
      if(pages[page_index].status.is_playable())
        for(move_coordinate_t y = 0; y < pages[page_index].size; y++)
          for(move_coordinate_t x = 0; x < pages[page_index].size; x++)
            if(!pages[page_index].fields[x][y].is_empty())
            {
              board_c board_copy = (board_c)pages[page_index];
              board_copy.play(move_c(x, y));
              pages[page_index].go_to_indexes[x][y] = find_page(board_copy);
            }
    }
  }

}
