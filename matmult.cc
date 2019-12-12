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

auto matmult(int *xs, int *ys, int xs_len, int ys_len) {
  Array<int> xs_ovl = Array<int>(dim_vector(3,3),0);
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      xs_ovl(r,c) = xs[r*3+c];
    }
  }
//   for (int i = 0; i < xs_len; i++) {
//     xs_ovl(i) = xs[i];
//   }
  Array<int> ys_ovl = Array<int>(dim_vector(3,3),0);
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      ys_ovl(r,c) = ys[r*3+c];
    }
  }
//   for (int i = 0; i < ys_len; i++) {
//     ys_ovl(i) = ys[i];
//   }
  Matrix out = (Matrix) xs_ovl * (Matrix) ys_ovl;
  static int ret[9];
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      ret[r*3+c] = out(r,c);
    }
  }
  return ret;
}

int main(void)
{
  int xs[9] = {1,2,3,4,5,6,7,8,9};
  int ys[9] = {1,2,3,4,5,6,7,8,9};
  int* zs;
  zs = matmult(xs, ys, 9, 9);
  for (int i = 0; i < 9; i++) {
    printf("%d ", zs[i]);
  }
  printf("\n");
  return 0;
}
