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

int *kron(int *xs, int *ys, int *zs, int xs_rows, int xs_cols, int ys_rows, int ys_cols) {
  Array<octave_int32> xs_ovl = Array<octave_int32>(dim_vector(xs_rows,xs_cols),0);
  for (int r = 0; r < xs_rows; r++) {
    for (int c = 0; c < xs_cols; c++) {
      xs_ovl(r,c) = xs[r*xs_cols+c];
    }
  }
  Array<octave_int32> ys_ovl = Array<octave_int32>(dim_vector(ys_rows,ys_cols),0);
  for (int r = 0; r < ys_rows; r++) {
    for (int c = 0; c < ys_cols; c++) {
      ys_ovl(r,c) = ys[r*ys_cols+c];
    }
  }
  octave_value_list params;
  params(0) = octave_value(xs_ovl);
  params(1) = octave_value(ys_ovl);
  octave_value_list out = octave::feval("kron", params, 1);
  Array<octave_int32> outmat = out(0).int32_array_value();
  // static int ret[xs_rows * xs_cols * ys_rows * ys_cols];
  for (int r = 0; r < xs_rows * ys_rows; r++) {
    for (int c = 0; c < xs_cols * ys_cols; c++) {
      zs[r*xs_cols*ys_cols+c] = outmat(r,c);
    }
  }
  return ret;
}

int main(void)
{
  int xs[9] = {1,2,3,4,5,6,7,8,9};
  int ys[9] = {1,2,3,4,5,6,7,8,9};
  int* zs = alloca(sizeof(xs) * sizeof(ys) * sizeof(int));
  kron(xs, ys, zs, 3, 3, 3, 3);
  for (int i = 0; i < 9; i++) {
    printf("%d ", zs[i]);
  }
  printf("\n");
  return 0;
}
