#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

constexpr auto loop_factorial(int n)
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

int main(int argc, char** argv)
{
  if(argc < 2) {
    cerr << "argument missing" << endl;
    return 1;
  }

  if(string(argv[1]) == "test") {

    constexpr int f = 50;
    constexpr int loops = 1000000;

    auto start = high_resolution_clock::now();
    for(int i = 0; i < loops; ++i)
     loop_factorial(f);
    auto end = high_resolution_clock::now();
    auto loop_factorial_result = (end - start).count();
    cout << loop_factorial_result << endl;

    start = high_resolution_clock::now();
    for(int i = 0; i < loops; ++i)
      recursive_factorial(1, f);
    end = high_resolution_clock::now();
    auto recursive_factorial_result = (end - start).count();
    cout << recursive_factorial_result << endl;

    cout << (loop_factorial_result > recursive_factorial_result ? "recursive" : "loop")
         << " factorial function is "
         << loop_factorial_result / float(recursive_factorial_result)
         << " faster.\n";

  } else {

    auto n = stoul(argv[1]);
    cout << loop_factorial(n) << endl;
    cout << recursive_factorial(n, 1) << endl;

  }
}

