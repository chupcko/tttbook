#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>

#include <getopt.h>
#include <unistd.h>

#include "tttbook.hpp"

using namespace std;
using namespace TTTbook;


void help(const char* name)
{
  cerr <<
    name << " [options] (file_name)?\n"
    "\t-h\n"
    "\t--help\n"
    "\t\tShow help\n"
    "\t-v\n"
    "\t--version\n"
    "\t\tShow version\n"
    "\t-1 [x,y]\n"
    "\t--first [x,y]\n"
    "\t\tBook play first at x,y; x,y from (0 .. 2, 0 .. 2)\n"
    "\t-2\n"
    "\t--second\n"
    "\t\tBook play second; default\n"
    "\t-l\n"
    "\t--last_move\n"
    "\t\tShow last move; default: do not show\n"
    "\t-m\n"
    "\t--marks\n"
    "\t\tShow marks; default: do not show\n"
    "\t-r [number]\n"
    "\t--rate [number]\n"
    "\t\tRate of worst vs. best solver; default: 0.0, number from (0.0 .. 1.0)\n"
    "\t--select [random, first, last]\n"
    "\t\tStrategy of selecting moves; default: random\n"
    "\t--best_speed [fast, slow]\n"
    "\t\tSpeed for best solver; default: fast\n"
     "\t-s [number]\n"
    "\t--shuffle [number]\n"
    "\t\tShuffle pages number times; default: 0; number from (0 .. 9)\n";
 exit(EXIT_FAILURE);
}

void version(const char* name)
{
  cerr << name << ' ' << TTTBOOK_VERSION << ' ' << TTTBOOK_DATE << '\n';
  exit(EXIT_FAILURE);
}

enum long_options_target_t
{
  HELP,
  VERSION,
  FIRST,
  SECOND,
  LAST_MOVE,
  MARKS,
  SHUFFLE,
  RATE,
  SELECT,
  BEST_SPEED
};

struct option long_options[] =
{
  {"help",       no_argument,       NULL, HELP      },
  {"version",    no_argument,       NULL, VERSION   },
  {"first",      required_argument, NULL, FIRST     },
  {"second",     no_argument,       NULL, SECOND    },
  {"last_move",  no_argument,       NULL, LAST_MOVE },
  {"marks",      no_argument,       NULL, MARKS     },
  {"rate",       required_argument, NULL, RATE      },
  {"select",     required_argument, NULL, SELECT    },
  {"best_speed", required_argument, NULL, BEST_SPEED},
  {"shuffle",    required_argument, NULL, SHUFFLE   },
  {0,            0,                 NULL, -2        }
};

int main(int arguments_number, char* arguments_values[])
{
  int option;
  int shuffle = -1;
  bool first = false;
  move_coordinate_t first_move_x;
  move_coordinate_t first_move_y;
  char* comma;
  double rate = 0.0;
  bool show_last_move = false;
  bool show_marks = false;
  solver_c::best_speed_t best_speed = solver_c::BEST_SPEED_FAST;
  solver_c::select_t select = solver_c::SELECT_RANDOM;
  ostream* file = &cout;
  ofstream new_file;

  opterr = 0;
  while(true)
  {
    int option_index = 0;
    option = getopt_long(arguments_number, arguments_values, "hv1:2lmg:s:", long_options, &option_index);
    if(option == -1)
      break;
    switch(option)
    {
      case 'h':
      case HELP:
        help(arguments_values[0]);
        break;
      case 'v':
      case VERSION:
        version(arguments_values[0]);
        break;
      case '1':
      case FIRST:
        first = true;
        first_move_x = atoi(optarg);
        comma = strchr(optarg, ',');
        if(comma == NULL)
        {
          cerr << "Bad first move coordinate\n";
          return EXIT_FAILURE;
        }
        comma++;
        first_move_y = atoi(comma);
        break;
      case '2':
      case SECOND:
        first = false;
        break;
      case 'l':
      case LAST_MOVE:
        show_last_move = true;
        break;
      case 'm':
      case MARKS:
        show_marks = true;
        break;
      case 'r':
      case RATE:
        rate = atof(optarg);
        break;
      case SELECT:
        switch(*optarg)
        {
          case 'r':
            select = solver_c::SELECT_RANDOM;
            break;
          case 'f':
            select = solver_c::SELECT_FIRST;
            break;
          case 'l':
            select = solver_c::SELECT_LAST;
            break;
        }
        break;
      case BEST_SPEED:
        switch(*optarg)
        {
          case 'f':
            best_speed = solver_c::BEST_SPEED_FAST;
            break;
          case 's':
            best_speed = solver_c::BEST_SPEED_SLOW;
            break;
        }
        break;
      case 's':
      case SHUFFLE:
        shuffle = atoi(optarg);
        if(shuffle < 1)
          shuffle = 1;
        if(shuffle > 10)
          shuffle = 10;
        break;
      default:
        help(arguments_values[0]);
    }
  }
  if(arguments_number-optind > 1)
    help(arguments_values[0]);

  if
  (
    arguments_number-optind == 1 &&
    strcmp(arguments_values[optind], "-") != 0
  )
  {
    new_file.open(arguments_values[optind]);
    if(!new_file.is_open())
    {
      cerr << "Cannot open \"" << arguments_values[optind] << "\"\n";
      return EXIT_FAILURE;
    }
    file = &new_file;
  }

  book_c book;
  switch(best_speed)
  {
    case solver_c::BEST_SPEED_FAST:
      book.set_best_speed_fast();
      break;
    case solver_c::BEST_SPEED_SLOW:
      book.set_best_speed_slow();
      break;
  }
  switch(select)
  {
    case solver_c::SELECT_RANDOM:
      book.set_select_random();
      break;
    case solver_c::SELECT_FIRST:
      book.set_select_first();
      break;
    case solver_c::SELECT_LAST:
      book.set_select_last();
      break;
  }
  book.set_worst_best_rate(rate);
  if(first)
    book.book_play_first(first_move_x, first_move_y);
  else
    book.book_play_second();
  if(show_last_move)
    book.show_last_move();
  else
    book.do_not_show_last_move();
  if(show_marks)
    book.show_marks();
  else
    book.do_not_show_marks();

  book.info(cerr);
  if(shuffle > 0)
    cerr << "Shuffle " << shuffle << " times\n";
  else
    cerr << "Do not shuffle\n";

  book.fill();
  if(shuffle > 0)
    book.shuffle(shuffle);

  book.write_ps(*file, 1);
  return EXIT_SUCCESS;
}
