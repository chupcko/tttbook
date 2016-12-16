#include "tttbook.hpp"

namespace TTTbook
{

  page_c::index_t book_c::find_page(board_c& board, bool do_play) noexcept
  {
    board_c board_copy(board);

    board_c::hash_t board_hash_before_play = board_copy.hash();
    if(shortcuts_before_play.count(board_hash_before_play) > 0)
      return shortcuts_before_play[board_hash_before_play];

    move_c* move = nullptr;
    if
    (
      do_play &&
      board_copy.status.is_playable()
    )
    {
      move = calculate_move(board_copy);
      board_copy.play(*move);
    }

    board_c::hash_t board_hash_after_play = board_copy.hash();
    if
    (
      !showing_last_move &&
      shortcuts_after_play.count(board_hash_after_play) > 0
    )
      return shortcuts_after_play[board_hash_after_play];

    pages.push_back(new page_c(board_copy));
    page_c::index_t page_index = (page_c::index_t)(pages.size()-1);
    pages[page_index]->page_index = page_index;
    pages[page_index]->shuffle_index = page_index;
    if(move != nullptr)
    {
      pages[page_index]->last_move_is_set = true;
      pages[page_index]->last_move = *move;
      delete move;
    }
    shortcuts_before_play[board_hash_before_play] = page_index;
    shortcuts_after_play[board_hash_after_play] = page_index;
    unpublished_pages.push_back(page_index);
    return page_index;
  }

  void book_c::fill_init_book_as_first() noexcept
  {
    board_c board;
    board.play(first_move);
    page_c::index_t page_index = find_page(board, false);
    pages[page_index]->last_move_is_set = true;
    pages[page_index]->last_move = first_move;
  }

  void book_c::fill_init_book_as_second() noexcept
  {
    find_page(*new board_c, false);
  }

  void book_c::clear() noexcept
  {
    for(page_c* page: pages)
      delete page;
    pages.clear();
    shortcuts_before_play.clear();
    shortcuts_after_play.clear();
    unpublished_pages.clear();
    shuffle_begin_index = page_c::null_index;
  }

  void book_c::fill() noexcept
  {
    if(book_is_first)
      fill_init_book_as_first();
    else
      fill_init_book_as_second();
    shuffle_begin_index = (page_c::index_t)pages.size();

    while(!unpublished_pages.empty())
    {
      page_c::index_t page_index = unpublished_pages.front();
      unpublished_pages.pop_front();
      if(pages[page_index]->status.is_playable())
        for(move_c& move : pages[page_index]->all_moves_on_empty)
        {
          board_c board_copy = board_c((board_c)*pages[page_index]);
          board_copy.play(move);
          pages[page_index]->go_to_indexes[move.x][move.y] = find_page(board_copy, true);
        }
    }
  }

  void book_c::shuffle(int count) noexcept
  {
    shuffle_count = count;
    for(page_c::index_t i = 0; i < (page_c::index_t)(shuffle_count*pages.size()); i++)
    {
      page_c::index_t a_index = util_c::random_int(shuffle_begin_index, pages.size()-1);
      page_c::index_t b_index = util_c::random_int(shuffle_begin_index, pages.size()-1);
      while(a_index == b_index)
        b_index = util_c::random_int(shuffle_begin_index, pages.size()-1);
      page_c::index_t page_index = pages[pages[a_index]->page_index]->shuffle_index;
      pages[pages[a_index]->page_index]->shuffle_index = pages[pages[b_index]->page_index]->shuffle_index;
      pages[pages[b_index]->page_index]->shuffle_index = page_index;
      page_index = pages[a_index]->page_index;
      pages[a_index]->page_index = pages[b_index]->page_index;
      pages[b_index]->page_index = page_index;
    }
  }

  static const char* ps_header =
    "%!PS-Adobe-3.0\n"
    "%%Pages: $$PAGES\n"
    "%%EndComments\n"
    "\n"
    "%%BeginProlog\n"
    "%%BeginResource: TTTbook_init\n"
    "\n"
    "/TTTbook_init\n"
    "{\n"
    "  72 25.4 div dup scale\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_center_show\n"
    "\n"
    "/TTTbook_center_show\n"
    "{\n"
    "  3 dict begin\n"
    "    /text exch def\n"
    "    text stringwidth\n"
    "    /height exch def\n"
    "    /width exch def\n"
    "    width 2 div neg 0 rmoveto text show\n"
    "  end\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_page\n"
    "\n"
    "/TTTbook_page\n"
    "{\n"
    "  TTTbook_init\n"
    "  4 dict begin\n"
    "    gsave\n"
    "      TTTbook_page_half TTTbook_page_half translate\n"
    "      45 rotate\n"
    "      TTTbook_watermark_font setfont\n"
    "      newpath 0 0 moveto TTTbook_watermark_text true charpath pathbbox\n"
    "      /ury exch def /urx exch def /lly exch def /llx exch def\n"
    "      TTTbook_watermark_gray setgray\n"
    "      newpath llx urx add 2 div neg lly ury add 2 div neg moveto TTTbook_watermark_text show\n"
    "    grestore\n"
    "    gsave\n"
    "      TTTbook_footer_font setfont\n"
    "      TTTbook_footer_gray setgray\n"
    "      newpath TTTbook_margin_size TTTbook_margin_size moveto TTTbook_footer_text show\n"
    "      newpath TTTbook_margin_size TTTbook_margin_size moveto TTTbook_footer_text true charpath pathbbox\n"
    "      /ury exch def /urx exch def /lly exch def /llx exch def\n"
    "      [ /Rect [ 0 0 urx TTTbook_margin_size add ury TTTbook_margin_size add ] /Border [ 0 0 0 ] /Page TTTbook_page_number_offset /View [ /XYZ null null null ] /LNK pdfmark\n"
    "    grestore\n"
    "  end\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_grid\n"
    "\n"
    "/TTTbook_grid\n"
    "{\n"
    "  2 dict begin\n"
    "    /delta exch def\n"
    "    gsave\n"
    "      0.01 setlinewidth\n"
    "      0 0 0.75 setrgbcolor\n"
    "      0 delta TTTbook_page_size\n"
    "      {\n"
    "        /i exch def\n"
    "        newpath\n"
    "          i 0 moveto i TTTbook_page_size lineto\n"
    "          0 i moveto TTTbook_page_size i lineto\n"
    "        stroke\n"
    "      } for\n"
    "    grestore\n"
    "  end\n"
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
    "      TTTbook_page_number_font setfont\n"
    "      newpath 0 0 moveto page_number true charpath pathbbox\n"
    "      /ury exch def /urx exch def /lly exch def /llx exch def\n"
    "      TTTbook_page_number_gray setgray\n"
    "      newpath TTTbook_margin_right urx sub TTTbook_margin_size moveto page_number show\n"
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
    "      TTTbook_status_font setfont\n"
    "      newpath 0 0 moveto status true charpath pathbbox\n"
    "      /ury exch def /urx exch def /lly exch def /llx exch def\n"
    "      TTTbook_status_gray setgray\n"
    "      newpath TTTbook_margin_size llx sub TTTbook_margin_right ury sub moveto status show\n"
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
    "    TTTbook_hash_width setlinewidth\n"
    "    TTTbook_hash_gray setgray\n"
    "    newpath\n"
    "      TTTbook_hash_left TTTbook_board_left moveto TTTbook_hash_left TTTbook_board_right lineto\n"
    "      TTTbook_hash_right TTTbook_board_left moveto TTTbook_hash_right TTTbook_board_right lineto\n"
    "      TTTbook_board_left TTTbook_hash_left moveto TTTbook_board_right TTTbook_hash_left lineto\n"
    "      TTTbook_board_left TTTbook_hash_right moveto TTTbook_board_right TTTbook_hash_right lineto\n"
    "    stroke\n"
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
    "    TTTbook_center_left x TTTbook_field_size mul add\n"
    "    TTTbook_center_right y TTTbook_field_size mul sub\n"
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
    "%%BeginResource: TTTbook_go_to\n"
    "\n"
    "/TTTbook_go_to\n"
    "{\n"
    "  1 dict begin\n"
    "    /go_to exch def\n"
    "    gsave\n"
    "      TTTbook_find translate\n"
    "      TTTbook_go_to_font setfont\n"
    "      newpath 0 0 moveto go_to true charpath pathbbox\n"
    "      /ury exch def /urx exch def /lly exch def /llx exch def\n"
    "      TTTbook_go_to_gray setgray\n"
    "      newpath llx urx add 2 div neg lly ury add 2 div neg moveto go_to show\n"
    "      [ /Rect [ TTTbook_go_to_half neg TTTbook_go_to_half neg TTTbook_go_to_half TTTbook_go_to_half ] /Border [ 0 0 0 ] /Page go_to cvi TTTbook_page_number_offset add /View [ /XYZ null null null ] /LNK pdfmark\n"
    "    grestore\n"
    "  end\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_x\n"
    "\n"
    "/TTTbook_x\n"
    "{\n"
    "  gsave\n"
    "    TTTbook_find translate\n"
    "    TTTbook_symbol_width setlinewidth\n"
    "    TTTbook_symbol_gray setgray\n"
    "    newpath\n"
    "      TTTbook_symbol_half neg TTTbook_symbol_half neg moveto TTTbook_symbol_half TTTbook_symbol_half lineto\n"
    "      TTTbook_symbol_half neg TTTbook_symbol_half moveto TTTbook_symbol_half TTTbook_symbol_half neg lineto\n"
    "    stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_x_last\n"
    "\n"
    "/TTTbook_x_last\n"
    "{\n"
    "  gsave\n"
    "    TTTbook_find translate\n"
    "    TTTbook_symbol_last_width setlinewidth\n"
    "    newpath\n"
    "       TTTbook_symbol_half neg TTTbook_symbol_half neg moveto TTTbook_symbol_half TTTbook_symbol_half lineto\n"
    "       TTTbook_symbol_half neg TTTbook_symbol_half moveto TTTbook_symbol_half TTTbook_symbol_half neg lineto\n"
    "    strokepath\n"
    "    gsave\n"
    "      TTTbook_symbol_last_outline setlinewidth\n"
    "      TTTbook_symbol_gray setgray\n"
    "      stroke\n"
    "    grestore\n"
    "    TTTbook_symbol_last_gray setgray\n"
    "    fill\n"
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
    "    TTTbook_symbol_width setlinewidth\n"
    "    TTTbook_symbol_gray setgray\n"
    "    newpath 0 0 TTTbook_symbol_half 0 360 arc stroke\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_o_last\n"
    "\n"
    "/TTTbook_o_last\n"
    "{\n"
    "  gsave\n"
    "    TTTbook_find translate\n"
    "    TTTbook_symbol_last_width setlinewidth\n"
    "    newpath 0 0 TTTbook_symbol_half 0 360 arc strokepath\n"
    "    gsave\n"
    "      TTTbook_symbol_last_outline setlinewidth\n"
    "      TTTbook_symbol_gray setgray\n"
    "      stroke\n"
    "    grestore\n"
    "    TTTbook_symbol_last_gray setgray\n"
    "    fill\n"
    "  grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_mark_row\n"
    "\n"
    "/TTTbook_mark_row\n"
    "{\n"
    "  1 dict begin\n"
    "    /y exch def\n"
    "    /y TTTbook_center_right y TTTbook_field_size mul sub def\n"
    "    gsave\n"
    "      TTTbook_mark_width setlinewidth\n"
    "      TTTbook_mark_gray setgray\n"
    "      newpath TTTbook_board_left y moveto TTTbook_board_right y lineto stroke\n"
    "    grestore\n"
    "  end\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_mark_column\n"
    "\n"
    "/TTTbook_mark_column\n"
    "{\n"
    "  1 dict begin\n"
    "    /x exch def\n"
    "    /x TTTbook_center_left x TTTbook_field_size mul add def\n"
    "    gsave\n"
    "      TTTbook_mark_width setlinewidth\n"
    "      TTTbook_mark_gray setgray\n"
    "      newpath x TTTbook_board_left moveto x TTTbook_board_right lineto stroke\n"
    "    grestore\n"
    "  end\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%BeginResource: TTTbook_mark_diagonal\n"
    "\n"
    "/TTTbook_mark_diagonal\n"
    "{\n"
    "  1 dict begin\n"
    "    /t exch def\n"
    "    gsave\n"
    "      TTTbook_mark_width setlinewidth\n"
    "      TTTbook_mark_gray setgray\n"
    "      t 0 eq\n"
    "      {\n"
    "        newpath TTTbook_board_left TTTbook_board_right moveto TTTbook_board_right TTTbook_board_left lineto stroke\n"
    "      }\n"
    "      {\n"
    "        newpath TTTbook_board_left TTTbook_board_left moveto TTTbook_board_right TTTbook_board_right lineto stroke\n"
    "      }\n"
    "      ifelse\n"
    "    grestore\n"
    "} def\n"
    "\n"
    "%%EndResource\n"
    "%%EndProlog\n"
    "\n"
    "%%BeginSetup\n"
    "\n"
    "/TTTbook_page_size 120 def\n"
    "/TTTbook_margin_size 7.5 def\n"
    "/TTTbook_field_size 25 def\n"
    "/TTTbook_symbol_size 15 def\n"
    "/TTTbook_page_number_offset $$OFFSET def\n"
    "/TTTbook_watermark_text (CHUPCKO) def\n"
    "/TTTbook_watermark_font /Helvetica-Bold findfont 25 scalefont def\n"
    "/TTTbook_watermark_gray 0.95 def\n"
    "/TTTbook_footer_text (TTTbook $$VERSION $$DATE by CHUPCKO) def\n"
    "/TTTbook_footer_font /Helvetica findfont 2 scalefont def\n"
    "/TTTbook_footer_gray 0.75 def\n"
    "/TTTbook_page_number_font /Helvetica-Bold findfont 5 scalefont def\n"
    "/TTTbook_page_number_gray 0 def\n"
    "/TTTbook_status_font /Helvetica-Bold findfont 5 scalefont def\n"
    "/TTTbook_status_gray 0 def\n"
    "/TTTbook_hash_width 2 def\n"
    "/TTTbook_hash_gray 0 def\n"
    "/TTTbook_go_to_font /Helvetica-Bold findfont 5 scalefont def\n"
    "/TTTbook_go_to_gray 0 def\n"
    "/TTTbook_symbol_width 2 def\n"
    "/TTTbook_symbol_gray 0 def\n"
    "/TTTbook_symbol_last_outline 0.5 def\n"
    "/TTTbook_symbol_last_gray 0.75 def\n"
    "/TTTbook_mark_width 1 def\n"
    "/TTTbook_mark_gray 0.5 def\n"
    "\n"
    "/TTTbook_page_half TTTbook_page_size 2 div def\n"
    "/TTTbook_margin_right TTTbook_page_size TTTbook_margin_size sub def\n"
    "/TTTbook_board_left TTTbook_page_half TTTbook_field_size 1.5 mul sub def\n"
    "/TTTbook_board_right TTTbook_page_half TTTbook_field_size 1.5 mul add def\n"
    "/TTTbook_hash_left TTTbook_page_half TTTbook_field_size 0.5 mul sub def\n"
    "/TTTbook_hash_right TTTbook_page_half TTTbook_field_size 0.5 mul add def\n"
    "/TTTbook_center_left TTTbook_page_half TTTbook_field_size sub def\n"
    "/TTTbook_center_right TTTbook_page_half TTTbook_field_size add def\n"
    "/TTTbook_go_to_half TTTbook_field_size TTTbook_hash_width sub TTTbook_hash_width sub 2 div def\n"
    "/TTTbook_symbol_half TTTbook_symbol_size 2 div def\n"
    "/TTTbook_symbol_last_width TTTbook_symbol_width TTTbook_symbol_last_outline sub def\n"
    "\n"
    "<< /PageSize [ TTTbook_page_size 72 mul 25.4 div dup ] >> setpagedevice\n"
    "/pdfmark where {pop} {userdict /pdfmark /cleartomark load put} ifelse\n"
    "[ /Title (TTTbook) /Author (CHUPCKO) /Subject () /Keywords () /Creator (TTTbook) /DOCINFO pdfmark\n"
    "\n"
    "%%EndSetup\n"
    "\n"
    "%%Page: 1 1\n"
    "TTTbook_init\n"
    "/Helvetica-Bold findfont 21 scalefont setfont\n"
    "0 setgray\n"
    "newpath TTTbook_page_half 80 moveto (TTTbook) TTTbook_center_show\n"
    "/Helvetica-Bold findfont 7 scalefont setfont\n"
    "0 setgray\n"
    "newpath TTTbook_page_half 70 moveto ($$VERSION $$DATE) TTTbook_center_show\n"
    "/Helvetica-Bold findfont 7 scalefont setfont\n"
    "0 setgray\n"
    "newpath TTTbook_page_half 60 moveto (by CHUPCKO) TTTbook_center_show\n"
    "[ /Rect [ 0 0 TTTbook_page_size TTTbook_page_size ] /Border [ 0 0 0 ] /Page TTTbook_page_number_offset /View [ /XYZ null null null ] /LNK pdfmark\n"
    "showpage\n"
    "\n";

  void book_c::write_ps(std::ostream& out) const noexcept
  {
    const page_c::index_t page_offset = 2;
    std::string header = ps_header;
    util_c::string_replace(header, "$$PAGES", std::to_string(pages.size()+page_offset-1));
    util_c::string_replace(header, "$$OFFSET", std::to_string(page_offset));
    util_c::string_replace(header, "$$VERSION", TTTBOOK_VERSION);
    util_c::string_replace(header, "$$DATE", TTTBOOK_DATE);
    out << header;
    for(page_c* page: pages)
    {
      page_c::index_t page_index = page->shuffle_index;
      out <<
        "%%Page: " << pages[page_index]->page_index+page_offset << ' ' << pages[page_index]->page_index+page_offset <<
        "\nTTTbook_page (" << pages[page_index]->page_index << ") TTTbook_page_number (";
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
      out << ") TTTbook_status TTTbook_hash\n";
      for(move_c::coordinate_t y = 0; y < pages[page_index]->size; y++)
      {
        for(move_c::coordinate_t x = 0; x < pages[page_index]->size; x++)
        {
          if(x != 0)
            out << ' ';
          out << x << ' ' << y << ' ';
          if(pages[page_index]->fields[x][y].is_empty())
            if(pages[page_index]->status.is_playable())
              out << '(' << pages[pages[page_index]->go_to_indexes[x][y]]->page_index << ") TTTbook_go_to";
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
        out << '\n';
      }
      if(showing_marks)
      {
        for(move_c::coordinate_t xy = 0; xy < pages[page_index]->size; xy++)
        {
          if(pages[page_index]->is_win_in_row(xy))
            out << xy << " TTTbook_mark_row\n";
          if(pages[page_index]->is_win_in_column(xy))
            out << xy << " TTTbook_mark_column\n";
        }
        if(pages[page_index]->is_win_in_diagonal(0))
          out << "0 TTTbook_mark_diagonal\n";
        if(pages[page_index]->is_win_in_diagonal(1))
          out << "1 TTTbook_mark_diagonal\n";
      }
      out << "showpage\n\n";
    }
    out << "%%EOF\n";
  }

  void book_c::info(std::ostream& out) const noexcept
  {
    if(book_is_first)
      out << "Book is first with move " << first_move << '\n';
    else
      out << "Book is second\n";
    if(showing_last_move)
      out << "Show last move\n";
    else
      out << "Do not show last move\n";
    if(showing_marks)
      out << "Show marks\n";
    else
      out << "Do not show marks\n";
    solver_c::info(out);
    if(shuffle_count > 0)
      out << "Shuffle " << shuffle_count << " times\n";
    else
      out << "Do not shuffle\n";
  }

  std::ostream& operator<<(std::ostream& out, const book_c& self)
  {
    out << std::boolalpha <<
      "Book is first: " << self.book_is_first <<
      "\nShowing last move: " << self.showing_last_move <<
      "\nShuffle begin index: " << self.shuffle_begin_index << "\n\n";
    page_c::index_t page_index = 0;
    for(page_c* page: self.pages)
      out << "Page " << page_index++ << '\n' << *page << "\n\n";
    return out;
  }

}
