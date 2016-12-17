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
    "\t-r\n"
    "\t--reverse\n"
    "\t\tPlay reverse game\n"
    "\t-1 [x,y]\n"
    "\t--first [x,y]\n"
    "\t\tBook play first at x,y; x,y from (0 .. 2, 0 .. 2)\n"
    "\t-l\n"
    "\t--last_move\n"
    "\t\tShow last move; default: do not show\n"
    "\t-m\n"
    "\t--marks\n"
    "\t\tShow marks; default: do not show\n"
    "\t-g [number]\n"
    "\t--guaranteed_best [number]\n"
    "\t\tGuaranteed first best moves; default: 0, from (0 .. 5)\n"
    "\t--best_weight [number]\n"
    "\t\tBest solver weight; default: 1.0, positive number\n"
    "\t--modest_weight [number]\n"
    "\t\tModest solver weight; default: 0.0, positive number\n"
    "\t--worst_weight [number]\n"
    "\t\tWorst solver weight; default: 0.0, positive number\n"
    "\t--select [random, first, last]\n"
    "\t\tStrategy of selecting moves; default: random\n"
    "\t--speed [fast, slow]\n"
    "\t\tSpeed for solvers; default: fast\n"
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
  REVERSE,
  FIRST,
  LAST_MOVE,
  MARKS,
  GUARANTEED_BEST,
  BEST_WEIGHT,
  MODEST_WEIGHT,
  WORST_WEIGHT,
  LOSE_WEIGHT,
  SELECT,
  SPEED,
  SHUFFLE
};

struct option long_options[] =
{
  {"help",            no_argument,       NULL, HELP           },
  {"version",         no_argument,       NULL, VERSION        },
  {"reverse",         no_argument,       NULL, REVERSE        },
  {"first",           required_argument, NULL, FIRST          },
  {"last_move",       no_argument,       NULL, LAST_MOVE      },
  {"marks",           no_argument,       NULL, MARKS          },
  {"guaranteed_best", required_argument, NULL, GUARANTEED_BEST},
  {"best_weight",     required_argument, NULL, BEST_WEIGHT    },
  {"modest_weight",   required_argument, NULL, MODEST_WEIGHT  },
  {"worst_weight",    required_argument, NULL, WORST_WEIGHT   },
  {"lose_weight",     required_argument, NULL, LOSE_WEIGHT    },
  {"select",          required_argument, NULL, SELECT         },
  {"speed",           required_argument, NULL, SPEED          },
  {"shuffle",         required_argument, NULL, SHUFFLE        },
  {0,                 0,                 NULL, -2             }
};

int main(int arguments_number, char* arguments_values[])
{
  int option;
  move_c::coordinate_t first_move_x;
  move_c::coordinate_t first_move_y;
  char* comma;
  ostream* file = &cout;
  ofstream new_file;
  book_c book;

  opterr = 0;
  while(true)
  {
    int option_index = 0;
    option = getopt_long(arguments_number, arguments_values, "hvr1:lmg:s:", long_options, &option_index);
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
      case 'r':
      case REVERSE:
        book.set_type_reverse();
        break;
      case '1':
      case FIRST:
        first_move_x = atoi(optarg);
        comma = strchr(optarg, ',');
        if(comma == NULL)
        {
          cerr << "Bad first move coordinate\n";
          return EXIT_FAILURE;
        }
        comma++;
        first_move_y = atoi(comma);
        book.book_play_first(first_move_x, first_move_y);
        break;
        break;
      case 'l':
      case LAST_MOVE:
        book.show_last_move();
        break;
      case 'm':
      case MARKS:
        book.show_marks();
        break;
      case 'g':
      case GUARANTEED_BEST:
        book.set_guaranteed_best(atoi(optarg));
        break;
      case BEST_WEIGHT:
        book.set_best_weight(atof(optarg));
        break;
      case MODEST_WEIGHT:
        book.set_modest_weight(atof(optarg));
        break;
      case WORST_WEIGHT:
        book.set_worst_weight(atof(optarg));
        break;
      case LOSE_WEIGHT:
        book.set_lose_weight(atof(optarg));
        break;
      case SELECT:
        switch(*optarg)
        {
          case 'r':
            book.set_select_random();
            break;
          case 'f':
            book.set_select_first();
            break;
          case 'l':
            book.set_select_last();
            break;
        }
        break;
      case SPEED:
        switch(*optarg)
        {
          case 'f':
            book.set_speed_fast();
            break;
          case 's':
            book.set_speed_slow();
            break;
        }
        break;
      case 's':
      case SHUFFLE:
        book.set_shuffle_count(atoi(optarg));
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

  book.info(cerr);
  book.fill();
  book.write_ps(*file);
  return EXIT_SUCCESS;
}
