#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

constexpr auto factorial(int n)
{
  unsigned long long f = 1;
  for(decltype(n) i = 1; i <= n; ++i)
    f *= i;
  return f;
}

constexpr auto recursive_factorial(int n, unsigned long long f)
{
  if(n == 1)
    return f;
  return recursive_factorial(n - 1, f *= n);
}

template<typename F, typename... Args>
void test(F func, Args&&... args)
{
    constexpr int loops = 10000;

    auto start = high_resolution_clock::now();
    for(int i = 0; i < loops; ++i)
      func(forward<Args>(args)...);
    auto end = high_resolution_clock::now();

    cout << (end - start).count() << endl;
}

int main(int argc, char** argv)
{
  if(argc < 2) {
    cerr << "argument missing" << endl;
    return 1;
  }

  if(string(argv[1]) == "test") {

    constexpr int f = 50;
    test(factorial, f);
    test(recursive_factorial, 1, f);

  } else {

    auto n = stoul(argv[1]);
    cout << factorial(n) << endl;
    cout << recursive_factorial(n, 1) << endl;

  }
}

