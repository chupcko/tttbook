#include "tttbook.hpp"

namespace tttbook
{

  page_index_t book_c::find_page(board_c& board, bool do_play) noexcept
  {
    board_hash_t board_hash = board.hash();
    if(shortcuts.count(board_hash) > 0)
      return shortcuts[board_hash];

    pages.push_back(new page_c(board));
    page_index_t page_index = (page_index_t)(pages.size()-1);

    if
    (
      do_play &&
      pages[page_index]->status.is_playable()
    )
    {
      move_c* move = calculate_move((board_c)*pages[page_index]);
      pages[page_index]->play(*move);
      pages[page_index]->last_move_is_set = true;
      pages[page_index]->last_move = *move;
      delete move;
    }

    pages[page_index]->page_index = page_index;
    pages[page_index]->shuffle_index = page_index;
    shortcuts[board_hash] = page_index;
    unpublished_pages.push_back(page_index);
    return page_index;
  }

  void book_c::fill_init_book_as_first() noexcept
  {
    for(move_coordinate_t y = 0; y < board_c::size; y++)
      for(move_coordinate_t x = 0; x < board_c::size; x++)
      {
        board_c board;
        board.play(move_c(x, y));
        page_index_t page_index = find_page(board, false);
        pages[page_index]->last_move_is_set = true;
        pages[page_index]->last_move.set(x, y);
      }
  }

  void book_c::fill_init_book_as_second() noexcept
  {
    page_index_t page_index = find_page(*new board_c, false);
  }

  void book_c::clear() noexcept
  {
    for(auto& page: pages)
      delete page;
    pages.clear();
    shortcuts.clear();
    unpublished_pages.clear();
  }

  void book_c::fill() noexcept
  {
    page_index_t page_index;
    page_index_t go_to_page_index;

    if(book_is_first)
      fill_init_book_as_first();
    else
      fill_init_book_as_second();
    shuffle_begin_index = (page_index_t)pages.size();

    while(!unpublished_pages.empty())
    {
      page_index = unpublished_pages.front();
      unpublished_pages.pop_front();
      if(pages[page_index]->status.is_playable())
        for(move_coordinate_t y = 0; y < pages[page_index]->size; y++)
          for(move_coordinate_t x = 0; x < pages[page_index]->size; x++)
            if(pages[page_index]->fields[x][y].is_empty())
            {
              board_c board_copy = board_c((board_c)*pages[page_index]);
              board_copy.play(move_c(x, y));
              pages[page_index]->go_to_indexes[x][y] = find_page(board_copy, true);
            }
    }
  }

  void book_c::shuffle(int count) noexcept
  {
    for(page_index_t i = 0; i < pages.size()*count; i++)
    {
      page_index_t a_index = util_c::random_int(shuffle_begin_index, pages.size()-1);
      page_index_t b_index = util_c::random_int(shuffle_begin_index, pages.size()-1);
      while(a_index == b_index)
         b_index = util_c::random_int(shuffle_begin_index, pages.size()-1);
      page_index_t page_index = pages[pages[a_index]->page_index]->shuffle_index;
      pages[pages[a_index]->page_index]->shuffle_index = pages[pages[b_index]->page_index]->shuffle_index;
      pages[pages[b_index]->page_index]->shuffle_index = page_index;
      page_index = pages[a_index]->page_index;
      pages[a_index]->page_index = pages[b_index]->page_index;
      pages[b_index]->page_index = page_index;
    }
  }

  static const char* ps_header =
    "%!PS-Adobe-3.0\n"
    "%%EndComments\n"
    "\n"
    "%%BeginProlog\n"
    "%%BeginResource: TTT_init_page\n"
    "\n"
    "/TTT_init_page\n"
    "{\n"
    "  << /PageSize [120 72 mul 25.4 div dup] /MediaColor (white) >> setpagedevice\n"
    "  72 25.4 div dup scale\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTT_page_number\n"
    "\n"
    "/TTT_page_number\n"
    "{\n"
    "  5 dict begin\n"
    "    /page_number exch def\n"
    "    gsave\n"
    "      TTT_page_number_font_name findfont TTT_page_number_font_size scalefont setfont\n"
    "      TTT_page_number_gray setgray\n"
    "      newpath 0 0 moveto page_number true charpath pathbbox\n"
    "      /ury exch def\n"
    "      /urx exch def\n"
    "      /lly exch def\n"
    "      /llx exch def\n"
    "      newpath 112.5 urx sub 7.5 lly sub moveto page_number show\n"
    "    grestore\n"
    "  end\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTT_status\n"
    "\n"
    "/TTT_status\n"
    "{\n"
    "  5 dict begin\n"
    "    /status exch def\n"
    "    gsave\n"
    "      TTT_status_font_name findfont TTT_status_font_size scalefont setfont\n"
    "      TTT_status_gray setgray\n"
    "      newpath 0 0 moveto status true charpath pathbbox\n"
    "      /ury exch def\n"
    "      /urx exch def\n"
    "      /lly exch def\n"
    "      /llx exch def\n"
    "      newpath 7.5 llx sub 112.5 ury sub moveto status show\n"
    "    grestore\n"
    "  end\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTT_hash\n"
    "\n"
    "/TTT_hash\n"
    "{\n"
    "  gsave\n"
    "    TTT_hash_line_width setlinewidth\n"
    "    TTT_hash_gray setgray\n"
    "    newpath 47.5 22.5 moveto 47.5 97.5 lineto stroke\n"
    "    newpath 72.5 22.5 moveto 72.5 97.5 lineto stroke\n"
    "    newpath 22.5 47.4 moveto 97.5 47.5 lineto stroke\n"
    "    newpath 22.5 72.5 moveto 97.5 72.5 lineto stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTT_find\n"
    "\n"
    "/TTT_find\n"
    "{\n"
    "  2 dict begin\n"
    "    /y exch def\n"
    "    /x exch def\n"
    "    35 x 25 mul add\n"
    "    85 y 25 mul sub\n"
    "  end\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTT_empty\n"
    "\n"
    "/TTT_empty\n"
    "{\n"
    "  pop\n"
    "  pop\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTT_x\n"
    "\n"
    "/TTT_x\n"
    "{\n"
    "  gsave\n"
    "    TTT_find translate\n"
    "    TTT_x_line_width setlinewidth\n"
    "    TTT_x_gray setgray\n"
    "    newpath -7.5 -7.5 moveto 7.5 7.5 lineto stroke\n"
    "    newpath -7.5 7.5 moveto 7.5 -7.5 lineto stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTT_x_gray\n"
    "\n"
    "/TTT_x_last\n"
    "{\n"
    "  gsave\n"
    "    TTT_find translate\n"
    "    TTT_x_line_width setlinewidth\n"
    "    TTT_x_last_gray setgray\n"
    "    newpath -7.5 -7.5 moveto 7.5 7.5 lineto stroke\n"
    "    newpath -7.5 7.5 moveto 7.5 -7.5 lineto stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTT_o\n"
    "\n"
    "/TTT_o\n"
    "{\n"
    "  gsave\n"
    "    TTT_find translate\n"
    "    TTT_o_line_width setlinewidth\n"
    "    TTT_o_gray setgray\n"
    "    newpath 0 0 7.5 0 360 arc stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTT_o_gray\n"
    "\n"
    "/TTT_o_last\n"
    "{\n"
    "  gsave\n"
    "    TTT_find translate\n"
    "    TTT_o_line_width setlinewidth\n"
    "    TTT_o_last_gray setgray\n"
    "    newpath 0 0 7.5 0 360 arc stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTT_go_to\n"
    "\n"
    "/TTT_go_to\n"
    "{\n"
    "  1 dict begin\n"
    "    /go_to exch def\n"
    "    gsave\n"
    "      TTT_find translate\n"
    "      TTT_go_to_font_name findfont TTT_go_to_font_size scalefont setfont\n"
    "      TTT_go_to_gray setgray\n"
    "      newpath 0 0 moveto go_to true charpath pathbbox\n"
    "      /ury exch def\n"
    "      /urx exch def\n"
    "      /lly exch def\n"
    "      /llx exch def\n"
    "      newpath llx urx add 2 div neg lly ury add 2 div neg moveto go_to show\n"
    "    grestore\n"
    "  end\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%EndProlog\n"
    "\n"
    "%%BeginSetup\n"
    "\n"
    "/TTT_page_number_font_name /HelveticaBold def\n"
    "/TTT_page_number_font_size 5 def\n"
    "/TTT_page_number_gray 0 def\n"
    "/TTT_status_font_name /HelveticaBold def\n"
    "/TTT_status_font_size 5 def\n"
    "/TTT_status_gray 0 def\n"
    "/TTT_hash_line_width 2 def\n"
    "/TTT_hash_gray 0 def\n"
    "/TTT_x_line_width 2 def\n"
    "/TTT_x_gray 0 def\n"
    "/TTT_x_last_gray 0.5 def\n"
    "/TTT_o_line_width 2 def\n"
    "/TTT_o_gray 0 def\n"
    "/TTT_o_last_gray 0.5 def\n"
    "/TTT_go_to_font_name /HelveticaBold def\n"
    "/TTT_go_to_font_size 5 def\n"
    "/TTT_go_to_gray 0 def\n"
    "\n"
    "%%EndSetup\n"
    "\n";

  void book_c::write_ps(std::ostream& out) const noexcept
  {
    out << ps_header;
    page_index_t page_offset = 1;
    for(auto& page: pages)
    {
      page_index_t page_index = page->shuffle_index;
      out <<
        "%%Page: " << pages[page_index]->page_index+page_offset << ' ' << pages[page_index]->page_index+page_offset << std::endl <<
        "TTT_init_page (" << pages[page_index]->page_index+page_offset << ") TTT_page_number (";
      if(pages[page_index]->status.is_playable())
        if(book_is_first)
          out << "Play as O, go to page:";
        else
          out << "Play as X, go to page:";
      else if(pages[page_index]->status.is_draw())
        out << "Draw!";
      else if(pages[page_index]->status.is_win_x())
        if(book_is_first)
          out << "Book (X) win!";
        else
          out << "You (X) win!";
      else if(pages[page_index]->status.is_win_o())
        if(book_is_first)
          out << "You (O) win!";
        else
          out << "Book (O) win!";
      out << ") TTT_status TTT_hash" << std::endl;
      for(move_coordinate_t y = 0; y < pages[page_index]->size; y++)
      {
        for(move_coordinate_t x = 0; x < pages[page_index]->size; x++)
        {
          if(x != 0)
            out << ' ';
          out << x << ' ' << y << ' ';
          if(pages[page_index]->fields[x][y].is_empty())
            if(pages[page_index]->status.is_playable())
              out << '(' << pages[pages[page_index]->go_to_indexes[x][y]]->page_index+page_offset << ") TTT_go_to";
            else
              out << "TTT_empty";
          else if(pages[page_index]->fields[x][y].is_x())
            if
            (
              showing_last_move &&
              pages[page_index]->last_move_is_set &&
              pages[page_index]->last_move.is(x, y)
            )
              out << "TTT_x_last";
            else
              out << "TTT_x";
          else if(pages[page_index]->fields[x][y].is_o())
            if
            (
              showing_last_move &&
              pages[page_index]->last_move_is_set &&
              pages[page_index]->last_move.is(x, y)
            )
              out << "TTT_o_last";
            else
              out << "TTT_o";
        }
        out << std::endl;
      }
      out <<
        "showpage" << std::endl <<
        std::endl;
    }
    out << "%%EOF" << std::endl;
  }

  std::ostream& operator<<(std::ostream& out, const book_c& self)
  {
    out << std::boolalpha <<
      "Book is first: " << self.book_is_first << std::endl <<
      "Showing last move: " << self.showing_last_move << std::endl <<
      "Shuffle begin index: " << self.shuffle_begin_index << std::endl <<
      std::endl;
    page_index_t page_index = 0;
    for(auto& page: self.pages)
      out <<
        "Page " << page_index++ << std::endl <<
        *page <<
        std::endl <<
        std::endl;
  }

}
