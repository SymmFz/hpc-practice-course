/*
In the test driver, there is a loop "for ( p=PFIRST; p<= PLAST; p+= PINC )"
The below parameters set this range of values that p takes on
*/
#define PFIRST 8
#define PLAST 1024
#define PINC 256 // unused

/*
In the test driver, the m, n, and k dimensions are set to the below
values.  If the value equals "-1" then that dimension is bound to the
index p, given above.
*/

#define M -1
#define N -1
#define K -1

/*
In the test driver, each experiment is repeated NREPEATS times and
the best time from these repeats is used to compute the performance
*/

#define NREPEATS 1

/*
Matrices A, B, and C are stored in two dimensional arrays with
row dimensions that are greater than or equal to the row dimension
of the matrix.  This row dimension of the array is known as the
"leading dimension" and determines the stride (the number of
double precision numbers) when one goes from one element in a row
to the next.  Having this number larger than the row dimension of
the matrix tends to adversely affect performance.  LDX equals the
leading dimension of the array that stores matrix X.  If LDX=-1
then the leading dimension is set to the row dimension of matrix X.
*/

#define LDA -1
#define LDB -1
#define LDC -1

/* Create macros so that the matrices are stored in column-major order */
// #define A(i, j) a[(j) * lda + (i)]
// #define B(i, j) b[(j) * ldb + (i)]
// #define C(i, j) c[(j) * ldc + (i)]

/* Macros for row-major order */
#define A(i, j) a[(i) * lda + (j)]
#define B(i, j) b[(i) * ldb + (j)]
#define C(i, j) c[(i) * ldc + (j)]

#define abs(x) ((x) < 0.0 ? -(x) : (x))
