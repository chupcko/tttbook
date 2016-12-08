#include "tttbook.hpp"

namespace tttbook
{

  page_index_t book_c::find_page(board_c& board) noexcept
  {
    board_hash_t board_hash = board.hash();
    if(shortcuts.count(board_hash) > 0)
      return shortcuts[board_hash];

    pages.push_back(new page_c(board));
    page_index_t page_index = (page_index_t)(pages.size()-1);
    pages[page_index]->page_index = page_index;
    pages[page_index]->shuffle_index = page_index;
    shortcuts[board_hash] = page_index;
    unpublished_pages.push_back(page_index);
    return page_index;
  }

  void book_c::fill_init_book_as_first(void) noexcept
  {
    for(move_coordinate_t y = 0; y < board_c::size; y++)
      for(move_coordinate_t x = 0; x < board_c::size; x++)
      {
        board_c board;
        board.play(move_c(x, y));
        page_index_t page_index = find_page(board);
        pages[page_index]->do_play = false;
      }
  }

  void book_c::fill_init_book_as_second(void) noexcept
  {
    board_c board;
    page_index_t page_index = find_page(board);
    pages[page_index]->do_play = false;
  }

  void book_c::clear(void) noexcept
  {
    for(auto& page: pages)
      delete page;
    pages.clear();
    shortcuts.clear();
    unpublished_pages.clear();
  }

  void book_c::fill(void) noexcept
  {
    page_index_t page_index;
    page_index_t go_to_page_index;

    if(book_is_first)
      fill_init_book_as_first();
    else
      fill_init_book_as_second();
    while(!unpublished_pages.empty())
    {
      page_index = unpublished_pages.front();
      unpublished_pages.pop_front();

      if
      (
        pages[page_index]->status.is_playable() &&
        pages[page_index]->do_play
      )
      {
        move_c* move = best_move((board_c)*pages[page_index]);
        pages[page_index]->play(*move);
        pages[page_index]->last_move = *move;
        delete move;
      }
      if(pages[page_index]->status.is_playable())
        for(move_coordinate_t y = 0; y < pages[page_index]->size; y++)
          for(move_coordinate_t x = 0; x < pages[page_index]->size; x++)
            if(pages[page_index]->fields[x][y].is_empty())
            {
              board_c board_copy = board_c((board_c)*pages[page_index]);
              board_copy.play(move_c(x, y));
              pages[page_index]->go_to_indexes[x][y] = find_page(board_copy);
            }
    }
  }

  void book_c::shuffle(void) noexcept
  {
    /*#*/
  }

  std::ostream& operator<<(std::ostream& out, const book_c& self)
  {
    page_index_t page_index = 0;
    for(auto& page: self.pages)
      out << "Page " << page_index++ << std::endl << *page << std::endl << std::endl << std::endl;
  }

}
