#include <iostream>
#include <sstream>
#include "ocl.h"

using namespace std;

string getAddKernel(int);

int main(){
  // Find all devices
  ocl_device device = ocl::displayDevices();

  // N is the work-group size in this example
  int N = device.getGroupSize(0);

  // Create a kernel using the device above from vectoradd.cl
  //    Default: Format the kernel to look "nice"
  //             Allows for easy debugging
  ocl_kernel kernel(&device,getAddKernel(N));

  // We can copy without memory leaks
  ocl_kernel add = kernel;

  // Prints the kernel nicely using a parser
  //    Allows for easy debugging
  cout << "Nice-looking Kernel" << endl
       << "-------------------" << endl ;
  add.printKernel();

  // Creating the same kernel without the "nice" format
  ocl_kernel looksBad(&device,getAddKernel(N),false);

  cout << "Original Kernel" << endl
       << "---------------" << endl ;
  looksBad.printKernel();

  // Create host variables
  float* a = new float[N];
  float* b = new float[N]();
  float* c = new float[N];

  // Setup the values of a
  for(int i=0;i<N;i++)
    a[i] = i;

  // Allocate memory on the device
  //   I like to use _var for the GPU variable that corresponds to var
  //   but it's just a matter of taste
  ocl_mem _a = device.malloc(N*sizeof(float),CL_MEM_READ_ONLY);
  ocl_mem _b = device.malloc(N*sizeof(float),CL_MEM_READ_ONLY);
  ocl_mem _c = device.malloc(N*sizeof(float),CL_MEM_WRITE_ONLY);

  // When doing device.malloc, the variable gets the size and is able to copy
  //   and write without needing the size again
  _a.copyFrom(a);

  // However, partial copy is also available
  //    copyFrom(array,offset,size you want to copy)
  _b.copyFrom(b,0*sizeof(float),N*sizeof(float));

  // Set the arguments required for the kernel
  //   This was not noted on example1.cpp
  //     but the arguments are automatically
  //     scanned when creating the kernel.
  //   This saves a lot of time inputting them
  //     individually.
  add.setArgs(&N,_a.mem(),_b.mem(),_c.mem());
  looksBad.setArgs(&N,_a.mem(),_b.mem(),_c.mem());

  // We can also set the args manually (which is useful when checking constants)
  add.setArg(0,&N);

  // When doing multiple executes, it is faster to set the dimension before
  //   executing.
  add.setDims(N,N);

  add.run();
  looksBad.run(N,N);

  // Wait until the kernel is done executing
  device.finish();

  // Copy device variable _c to host variable c
  _c.copyTo(c);

  // Output c
  // Should be 0,1,...,N-1
  for(int i=0;i<N;i++)
    cout << c[i] << ',';
  cout << endl;

  // Free host variables
  delete[] a;
  delete[] b;
  delete[] c;
}

string getAddKernel(int size){
  stringstream ret;

  // Using stringstream allows the programmer to code
  //    OpenCL almost like in a real file since it
  //    emulates "newlines" by separating the string
  // However, it looks horrible when printing it, so
  //    The kernel has a parser that automatically
  //    formats the code with new lines and indentations
  ret << "__kernel void vectoradd(const int N,"
      << "__global float *a,"
      << "__global float *b,"
      << "__global float *c){"
      << "int n = get_global_id(0);"
      << "if(n<N){"
      << "c[n] = a[n] + b[n];"
      << "}"
      << "for(int i=0;i<20;i++){"
      << "}"
      << "if(0);"
      << '}';

  return ret.str();
}
