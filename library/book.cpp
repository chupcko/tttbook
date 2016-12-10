#include "tttbook.hpp"

namespace TTTbook
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
    for(page_c* page: pages)
      delete page;
    pages.clear();
    shortcuts.clear();
    unpublished_pages.clear();
    shuffle_begin_index = page_c::null_page_index;
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
    "%%BeginResource: TTTbook_init_page\n"
    "\n"
    "/TTTbook_init_page\n"
    "{\n"
    "  << /PageSize [TTTbook_page_in_mm 72 mul 25.4 div dup] /MediaColor (white) >> setpagedevice\n"
    "  72 25.4 div dup scale\n"
    "  4 dict begin\n"
    "    gsave\n"
    "      TTTbook_page_in_mm 2 div TTTbook_page_in_mm 2 div translate\n"
    "      45 rotate\n"
    "      /HelveticaBold findfont 25 scalefont setfont\n"
    "      0.95 setgray\n"
    "      newpath 0 0 moveto (CHUPCKO) true charpath pathbbox\n"
    "      /ury exch def\n"
    "      /urx exch def\n"
    "      /lly exch def\n"
    "      /llx exch def\n"
    "      newpath llx urx add 2 div neg lly ury add 2 div neg moveto (CHUPCKO) show\n"
    "    grestore\n"
    "  end\n"
    "  gsave\n"
    "    TTTbook_footer_font_name findfont TTTbook_footer_font_size scalefont setfont\n"
    "    TTTbook_footer_gray setgray\n"
    "    newpath 7.5 7.5 moveto TTTbook_footer_text show\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_helper\n"
    "\n"
    "/TTTbook_helper\n"
    "{\n"
    "  0.01 setlinewidth\n"
    "  0 0 0.75 setrgbcolor\n"
    "  0 2.5 TTTbook_page_in_mm\n"
    "  {\n"
    "    /i exch def\n"
    "    newpath i 0 moveto i TTTbook_page_in_mm lineto stroke\n"
    "    newpath 0 i moveto TTTbook_page_in_mm i lineto stroke\n"
    "  } for\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_page_number\n"
    "\n"
    "/TTTbook_page_number\n"
    "{\n"
    "  5 dict begin\n"
    "    /page_number exch def\n"
    "    gsave\n"
    "      TTTbook_page_number_font_name findfont TTTbook_page_number_font_size scalefont setfont\n"
    "      TTTbook_page_number_gray setgray\n"
    "      newpath 0 0 moveto page_number true charpath pathbbox\n"
    "      /ury exch def\n"
    "      /urx exch def\n"
    "      /lly exch def\n"
    "      /llx exch def\n"
    "      newpath 112.5 urx sub 7.5 moveto page_number show\n"
    "    grestore\n"
    "  end\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_status\n"
    "\n"
    "/TTTbook_status\n"
    "{\n"
    "  5 dict begin\n"
    "    /status exch def\n"
    "    gsave\n"
    "      TTTbook_status_font_name findfont TTTbook_status_font_size scalefont setfont\n"
    "      TTTbook_status_gray setgray\n"
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
    "%%BeginResource: TTTbook_hash\n"
    "\n"
    "/TTTbook_hash\n"
    "{\n"
    "  gsave\n"
    "    TTTbook_hash_line_width setlinewidth\n"
    "    TTTbook_hash_gray setgray\n"
    "    newpath 47.5 22.5 moveto 47.5 97.5 lineto stroke\n"
    "    newpath 72.5 22.5 moveto 72.5 97.5 lineto stroke\n"
    "    newpath 22.5 47.4 moveto 97.5 47.5 lineto stroke\n"
    "    newpath 22.5 72.5 moveto 97.5 72.5 lineto stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_find\n"
    "\n"
    "/TTTbook_find\n"
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
    "%%BeginResource: TTTbook_empty\n"
    "\n"
    "/TTTbook_empty\n"
    "{\n"
    "  pop\n"
    "  pop\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_x\n"
    "\n"
    "/TTTbook_x\n"
    "{\n"
    "  gsave\n"
    "    TTTbook_find translate\n"
    "    TTTbook_x_line_width setlinewidth\n"
    "    TTTbook_x_gray setgray\n"
    "    newpath -7.5 -7.5 moveto 7.5 7.5 lineto stroke\n"
    "    newpath -7.5 7.5 moveto 7.5 -7.5 lineto stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_x_gray\n"
    "\n"
    "/TTTbook_x_last\n"
    "{\n"
    "  gsave\n"
    "    TTTbook_find translate\n"
    "    TTTbook_x_line_width setlinewidth\n"
    "    TTTbook_x_last_gray setgray\n"
    "    newpath -7.5 -7.5 moveto 7.5 7.5 lineto stroke\n"
    "    newpath -7.5 7.5 moveto 7.5 -7.5 lineto stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_o\n"
    "\n"
    "/TTTbook_o\n"
    "{\n"
    "  gsave\n"
    "    TTTbook_find translate\n"
    "    TTTbook_o_line_width setlinewidth\n"
    "    TTTbook_o_gray setgray\n"
    "    newpath 0 0 7.5 0 360 arc stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_o_gray\n"
    "\n"
    "/TTTbook_o_last\n"
    "{\n"
    "  gsave\n"
    "    TTTbook_find translate\n"
    "    TTTbook_o_line_width setlinewidth\n"
    "    TTTbook_o_last_gray setgray\n"
    "    newpath 0 0 7.5 0 360 arc stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_go_to\n"
    "\n"
    "/TTTbook_go_to\n"
    "{\n"
    "  1 dict begin\n"
    "    /go_to exch def\n"
    "    gsave\n"
    "      TTTbook_find translate\n"
    "      TTTbook_go_to_font_name findfont TTTbook_go_to_font_size scalefont setfont\n"
    "      TTTbook_go_to_gray setgray\n"
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
    "/TTTbook_page_in_mm 120 def\n"
    "\n"
    "/TTTbook_footer_text (TTTbook $$VERSION $$DATE by CHUPCKO) def\n"
    "/TTTbook_footer_font_name /Helvetica def\n"
    "/TTTbook_footer_font_size 2 def\n"
    "/TTTbook_footer_gray 0.5 def\n"
    "/TTTbook_page_number_font_name /HelveticaBold def\n"
    "/TTTbook_page_number_font_size 5 def\n"
    "/TTTbook_page_number_gray 0 def\n"
    "/TTTbook_status_font_name /HelveticaBold def\n"
    "/TTTbook_status_font_size 5 def\n"
    "/TTTbook_status_gray 0 def\n"
    "/TTTbook_hash_line_width 2 def\n"
    "/TTTbook_hash_gray 0 def\n"
    "/TTTbook_x_line_width 2 def\n"
    "/TTTbook_x_gray 0 def\n"
    "/TTTbook_x_last_gray 0.5 def\n"
    "/TTTbook_o_line_width 2 def\n"
    "/TTTbook_o_gray 0 def\n"
    "/TTTbook_o_last_gray 0.5 def\n"
    "/TTTbook_go_to_font_name /HelveticaBold def\n"
    "/TTTbook_go_to_font_size 5 def\n"
    "/TTTbook_go_to_gray 0 def\n"
    "\n"
    "%%EndSetup\n"
    "\n";

  void book_c::write_ps(std::ostream& out) const noexcept
  {
    std::string header = ps_header;
    util_c::string_replace(header, "$$VERSION", TTTBOOK_VERSION);
    util_c::string_replace(header, "$$DATE", TTTBOOK_DATE);
    out << header;
    page_index_t page_offset = 1;
    for(page_c* page: pages)
    {
      page_index_t page_index = page->shuffle_index;
      out <<
        "%%Page: " << pages[page_index]->page_index+page_offset << ' ' << pages[page_index]->page_index+page_offset << std::endl <<
        "TTTbook_init_page (" << pages[page_index]->page_index+page_offset << ") TTTbook_page_number (";
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
      out << ") TTTbook_status TTTbook_hash" << std::endl;
      for(move_coordinate_t y = 0; y < pages[page_index]->size; y++)
      {
        for(move_coordinate_t x = 0; x < pages[page_index]->size; x++)
        {
          if(x != 0)
            out << ' ';
          out << x << ' ' << y << ' ';
          if(pages[page_index]->fields[x][y].is_empty())
            if(pages[page_index]->status.is_playable())
              out << '(' << pages[pages[page_index]->go_to_indexes[x][y]]->page_index+page_offset << ") TTTbook_go_to";
            else
              out << "TTTbook_empty";
          else if(pages[page_index]->fields[x][y].is_x())
            if
            (
              showing_last_move &&
              pages[page_index]->last_move_is_set &&
              pages[page_index]->last_move.is(x, y)
            )
              out << "TTTbook_x_last";
            else
              out << "TTTbook_x";
          else if(pages[page_index]->fields[x][y].is_o())
            if
            (
              showing_last_move &&
              pages[page_index]->last_move_is_set &&
              pages[page_index]->last_move.is(x, y)
            )
              out << "TTTbook_o_last";
            else
              out << "TTTbook_o";
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
    for(page_c* page: self.pages)
      out <<
        "Page " << page_index++ << std::endl <<
        *page <<
        std::endl <<
        std::endl;
  }

}
