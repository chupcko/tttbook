#ifndef __ERROR__HPP__
#define __ERROR__HPP__

namespace TTTbook
{

  #define MAKE_ERROR(name, text)                 \
  class name : public std::exception             \
  {                                              \
    virtual const char* what() const throw() \
    {                                            \
      return text;                               \
    }                                            \
  }                                              \

  MAKE_ERROR(error_bad_index,      "Bad index");
  MAKE_ERROR(error_not_playable,   "Not playable");
  MAKE_ERROR(error_already_filled, "Already filled");

}

#endif
