#ifndef __UTIL__HPP__
#define __UTIL__HPP__

namespace tttbook
{
  class util_c
  {
    public:

      static int random_int(int low, int high)
      {
        static std::random_device device;
        static std::default_random_engine generator(device());
        std::uniform_int_distribution<int> distribution(low, high);
        return distribution(generator);
      };
  };

}

#endif
