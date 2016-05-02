Threaded Matrix Multiplication
Copyright © 2016 Mario Jacob García Navarro
===============================================
===============================================
+             	 USEFUL NOTES                 +
===============================================
The source code, version changes, and more
information about the project can be found in:
github.com/JacobGarcia/
ThreadedMatrixMultiplication

===============================================
+             	 CONTRIBUTORS                 +
===============================================
Mario Jacob García Navarro - A01363206

===============================================
+             IMPLEMENTATION PROCESS          +
===============================================
Parallel version of the matrix multiplication
algorithm. The program creates N child threads
that compute the multiplication of
row i X column j of two square matrices and
then send their results to the parent thread
using thread synchronization.

===============================================
+      	   HOW TO BUILD THE EXECUTABLE        +
===============================================

———————————————————————————————————————————————
                    make
———————————————————————————————————————————————

When the build is executed, the matrices text
file must be passed as an argument.
NOTE: Consider for the next command that the
test file must be in the same folder. If that
were not the case, then add the file address.
———————————————————————————————————————————————
          /.multiplicate matrices.txt
———————————————————————————————————————————————

===============================================
+              INPUT FILE FORMAT              +
===============================================
While reading from the input file, the first
line must represent the N dimensions size for
the matrices. Since the program addresses only
square matrices, both of them will be of the
form N X N. The next two lines represent the
actual values for the matrices in form of an
array (this is not a problem since C
interprets matrices as arrays).

Input test file example:
    2
    1234
    4321



