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

void version(const char* name)
{
  cerr << name << ' ' << TTTBOOK_VERSION << ' ' << TTTBOOK_DATE << '\n';
  exit(EXIT_FAILURE);
}

void help(const char* name)
{
  cerr << name << " help ...\n";
  /*#*/
  exit(EXIT_FAILURE);
}

enum long_options_target_t
{
  HELP,
  VERSION,
  SHUFFLE,
  FIRST,
  SECOND,
  GATE,
  LAST_MOVE,
  SELECT,
  BEST_SPEED
};

struct option long_options[] =
{
  {"help",       no_argument,       NULL, HELP      },
  {"version",    no_argument,       NULL, VERSION   },
  {"shuffle",    required_argument, NULL, SHUFFLE   },
  {"first",      required_argument, NULL, FIRST     },
  {"second",     no_argument,       NULL, SECOND    },
  {"gate",       required_argument, NULL, GATE      },
  {"last_move",  no_argument,       NULL, LAST_MOVE },
  {"select",     required_argument, NULL, SELECT    },
  {"best_speed", required_argument, NULL, BEST_SPEED},
  {0,            0,                 NULL, -2        }
};

int main(int arguments_number, char* arguments_values[])
{
  int option;
  int shuffle = -1;
  int first = false;
  double gate = 0;
  bool show_last_move = false;
  solver_c::best_speed_t best_speed = solver_c::BEST_SPEED_FAST;
  solver_c::select_t select = solver_c::SELECT_RANDOM;
  ostream* file = &cout;
  ofstream new_file;

  opterr = 0;
  while(true)
  {
    int option_index = 0;
    option = getopt_long(arguments_number, arguments_values, "hvs:1:2g:l", long_options, &option_index);
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
      case 's':
      case SHUFFLE:
        shuffle = atoi(optarg);
        if(shuffle < 1)
          shuffle = 1;
        if(shuffle > 10)
          shuffle = 10;
        break;
      case '1':
      case FIRST:
        first = true;
        /*#*/
        break;
      case '2':
      case SECOND:
        first = false;
        break;
      case 'g':
      case GATE:
        gate = atof(optarg);
        break;
      case 'l':
      case LAST_MOVE:
        show_last_move = true;
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
      default:
        help(arguments_values[0]);
    }
  }
  if(arguments_number-optind > 1)
    help(arguments_values[0]);

  if(arguments_number-optind == 1)
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
  book.set_worst_best_gate(gate);
  if(first)
    book.book_play_first();
  else
    book.book_play_second();
  if(show_last_move)
    book.show_last_move();
  else
    book.do_not_show_last_move();
  book.fill();
  if(shuffle > 0)
    book.shuffle(shuffle);

  book.write_ps(*file);
  return EXIT_SUCCESS;
}
