// vim: set path+=/usr/include/octave-4.4.0/octave/ :
// vim: set path+=/usr/include/octave-4.4.0/ :
#include <iostream>
#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/interpreter.h>

void initOct() {
  static octave::interpreter interpreter;
      int status = interpreter.execute();
      if (status != 0)
        {
          std::cout << "Status failure\n";
          return;
        }
}

int gcd(int i, int j) {
//   try
//     {
      octave_value_list in;
      in(0) = octave_value(i);
      in(1) = octave_value(j);
      octave_value_list out = octave::feval("gcd", in, 1);

      if (out.length() > 0)
        return out(0).int_value();
      else {
        std::cout << "invalid\n";
        return -1;
      }
//     }
//   catch (const octave::exit_exception& ex)
//     {
//       std::cerr << "Octave interpreter exited with status = "
//                 << ex.exit_status() << std::endl;
//     }
//   catch (const octave::execution_exception&)
//     {
//       std::cerr << "error encountered in Octave evaluator!" << std::endl;
//     }
}

int
main(void)
{
  std::cout << gcd(10,15) << std::endl;
  return 0;
}
