#ifndef __UTIL__HPP__
#define __UTIL__HPP__

namespace TTTbook
{

  #define REPEAT_0(x)
  #define REPEAT_1(x) REPEAT_0(x) x
  #define REPEAT_2(x) REPEAT_1(x) x
  #define REPEAT_3(x) REPEAT_2(x) x
  #define REPEAT_4(x) REPEAT_3(x) x
  #define REPEAT_5(x) REPEAT_4(x) x
  #define REPEAT_6(x) REPEAT_5(x) x
  #define REPEAT_7(x) REPEAT_6(x) x
  #define REPEAT_8(x) REPEAT_7(x) x
  #define REPEAT_9(x) REPEAT_8(x) x
  #define REPEAT_(n, x) REPEAT_##n(x)
  #define REPEAT(n, x) REPEAT_(n, x)

  class util_c
  {
    public:

      static int random_int(int low, int high)
      {
        static std::random_device device;
        static std::default_random_engine generator(device());
        std::uniform_int_distribution<int> distribution(low, high);
        return distribution(generator);
      }

      static double random_double(int low, int high)
      {
        static std::random_device device;
        static std::default_random_engine generator(device());
        std::uniform_real_distribution<double> distribution(low, high);
        return distribution(generator);
      }

      static void string_replace(std::string& subject, const std::string& search, const std::string& replace)
      {
        size_t position = subject.find(search, 0);
        while(position != std::string::npos)
        {
          subject.replace(position, search.length(), replace);
          position = subject.find(search, position+replace.length());
        }
      }

  };

}

#endif
