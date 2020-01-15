////////////////////////////////////////////////////////////////////////////////
// File: max_search_parabolic_interpolation.c                                 //
// Routine(s):                                                                //
//    Max_Search_Parabolic_Interpolation                                      //
////////////////////////////////////////////////////////////////////////////////

#include <float.h>                          // required for DBL_EPSILON
#include <math.h>                           // required for fabs(), sqrt()

#define SQRT5 2.236067977499789696

static const double alpha = 0.5 * (3.0 - SQRT5);

//                        Internally Defined Routines 

static int Stopping_Rule(double x[], double tolerance);
static int Parabolic_Maximum( double x[], double y[], double *xmin);
static void Check_New_Test_Point( double x[], double *xmin,
                                     double min_displacement, double epsilon );
static void Left_Interior_Point( double (*f)(double), double x[], double y[] );
static void Right_Interior_Point( double (*f)(double), double x[], double y[] );

////////////////////////////////////////////////////////////////////////////////
//  int Max_Search_Parabolic_Interpolation(double (*f)(double), double x0[],  //
//                                          double fx0[], double tolerance )  //
//                                                                            //
//  Description:                                                              //
//     This routine can be used to locate the maximum of a unimodal function  //
//     within a preassigned tolerance or a local maximum of a multimodal      //
//     function within a preassigned tolerance.  The function should not be   //
//     linear on any closed and bounded subinterval with nonempty interior.   //
//                                                                            //
//     Given points (x1, f(x1)), (x2, f(x2)), (x3, f(x3)) with x1 < x2 < x3   //
//     and f(x1) < f(x2) > f(x3), the parabolic interpolation method          //
//     estimates a local maximum of f(x) for x1 < x < x3 by repeated          //
//     estimation of the maximum of the parabola through three points.  The   //
//     three points being two points which bound the maximum and the current  //
//     location of the observed maximum.  The iteration is terminated when    //
//     the relative length of the interval bounding the maximum is less than  //
//     or equal to a preassigned tolerance.                                   //
//                                                                            //
//  Arguments:                                                                //
//     double (*f)(double)                                                    //
//        Pointer to a user-defined function of a real variable (type double) //
//        returning a real number (type double).                              //
//     double x0[]                                                            //
//        On input, x0[0] is the initial lower endpoint and x0[2] is the upper//
//        endpoint of an interval which contains a local maximum. x0[1] is    //
//        an interior point between x0[0] and x0[2] such that                 //
//        f(x0[1]) > f(x0[0]) and f(x0[1]) > f(x0[2]).  On output, x0[0] is   //
//        the lower endpoint and x0[2] is the upper endpoint of the final     //
//        subinterval which contains the local maximum.  x0[1] is the current //
//        best estimate of the location of the local maximum.                 //
//     double fx0[]                                                           //
//        On input and on output, fx0[i] is the value of f(x) evaluated at    //
//        x0[i], i=1,2,3.                                                     //
//     double tolerance                                                       //
//        A parameter which controls the termination of the procedure.        //
//        When the magnitude of *x3 - *x1 is less than "tolerance" *          //
//        ((*x3 + *x1) / 2 + eta), the procedure is terminated, where eta is  //
//        1 if *x3 + *x1 <= 1 and 0 otherwise.  "tolerance' should be a       //
//        strictly positive number.  If a nonpositive number is passed, then  //
//        tolerance is set to sqrt(DBL_EPSILON).                              //
//                                                                            //
//  Return Values:                                                            //
//     0   Success                                                            //
//    -1   Three points used to estimate the maximum of the parabola through  //
//         them were either collinear or the result is a minimum.             //
//    -2   The initial points failed to satisfy the condition that            //
//         x1 < x2 < x3 and fx1 < fx2 > fx3.                                  //
//                                                                            //
//  Example:                                                                  //
//     extern double f(double);                                               //
//     double x[] = { -1.0, 0.0, 1.0 };                                       //
//     double fx = { f(x[0]), f(x[1]), f(x[2]) };                             //
//     double tolerance = 1.0e-2;                                             //
//     int err;                                                               //
//                                                                            //
//             (verify fx[1] > fx[2] and fx[1] > fx[0] otherwise              //
//                                 choose different initial points)           //
//                                                                            //
//     err = Max_Search_Parabolic_Interpolation(f, x, fx, tolerance )         //
//     if (err < 0 ) printf("Error in input data\n");                         //
//     else printf("local maximum is between (%12.6e,%12.6e) and              //
//                               (%12.6e,%12.6e)\n", x[0],fx[0], x[2],fx[2]); //
////////////////////////////////////////////////////////////////////////////////

int Max_Search_Parabolic_Interpolation(double (*f)(double), double x0[],
                                              double fx0[], double tolerance )
{
   double x[5] = { x0[0], x0[0], x0[1], x0[2], x0[2] };
   double y[5] = { fx0[0], fx0[0], fx0[1], fx0[2], fx0[2] };
   double min_displacement = 0.01 * tolerance;
   double epsilon = 0.333333 * tolerance;
   double xmax, ymax;
   int err = 0;

       // Verify that the input data satisfy the conditions:
       // x1 < x2 < x3 and fx1 <= fx2 >= fx3 but not fx1 = fx2 = fx3.

   if ( (x[0] > x[2]) || (x[4] < x[2]) ) return -2;
   if ( (y[0] > y[2]) || (y[2] < y[4]) ) return -2;
   if ( (y[0] == y[2]) && (y[2] == y[4]) ) return -2;

       // If the input tolerance is nonpositive, set it to the default.

   if (tolerance <= 0.0) tolerance = sqrt(DBL_EPSILON);

                      // Find the three interior points.

   Left_Interior_Point( f, x, y );
   if ( Stopping_Rule(x, tolerance) ) return 0;
   Right_Interior_Point( f, x, y );

                 // Iterate until the location of the maximum
                 // is found within the specified tolerance.

   while (!Stopping_Rule(x, tolerance ) ) {
      err = Parabolic_Maximum( x, y, &xmax);
      if (err) break;
      Check_New_Test_Point( x, &xmax, min_displacement, epsilon);
      ymax = f(xmax);
      if ( xmax < x[2] ) {
         if ( ymax <= y[1] ) {
            x[0] = xmax; y[0] = ymax; Left_Interior_Point( f, x, y );
         }
         else if ( ymax <= y[2] ) {
            x[0] = x[1]; y[0] = y[1]; x[1] = xmax; y[1] = ymax;
         }
         else {
            x[4] = x[3]; y[4] = y[3]; x[3] = x[2]; y[3] = y[2];
            x[2] = xmax; y[2] = ymax;
         }
      }
      else {
         if ( ymax <= y[3] ) {
            x[4] = xmax; y[4] = ymax; Right_Interior_Point( f, x, y );
         }
         else if ( ymax <= y[2] ) {
            x[4] = x[3]; y[4] = y[3]; x[3] = xmax; y[3] = ymax;
         }
         else {
            x[0] = x[1]; y[0] = y[1]; x[1] = x[2]; y[1] = y[2];
            x[2] = xmax; y[2] = ymax;
         }
      }
   }

                 // If no errs were detected, return the final 
                 // interval and an internal point together with
                 // the value of the function evaluated there.

   if (err == 0) {
      x0[0] = x[1];
      x0[1] = x[2];
      x0[2] = x[3];
      fx0[0] = y[1];
      fx0[1] = y[2];
      fx0[2] = y[3];
   }
   
   return err;
}


////////////////////////////////////////////////////////////////////////////////
//  static int Stopping_Rule(double x[], double tolerance)                    //
//                                                                            //
//  Description:                                                              //
//     Given an ordered array x[0] < x[1] < ... < x[4], this routine returns  //
//     TRUE (1) if  x[3] - x[1] < epsilon * (|xm| + eta) or FALSE (0)         //
//     otherwise, where f(x[2]) is the maximum among f(x[i]), i = 0,...,4,    //
//     epsilon = tolerance, and eta = 1.0 if xm <= 0.0 otherwise              //
//     eta = 0.0.                                                             //
//                                                                            //
//     For C compilers which support the 'inline' type qualifier, this routine//
//     could be declared with the 'inline' qualifier.                         //
//                                                                            //
//  Return Values:                                                            //
//     0  Bound is not within the specified tolerance.                        //
//     1  Bound is within the specified tolerance.                            //
////////////////////////////////////////////////////////////////////////////////
static int Stopping_Rule(double x[], double tolerance)
{
   double xmid = 0.5 * fabs( x[3] + x[1] );
   double eta = (xmid <= 1.0) ? 1.0 : fabs(xmid);

   return ( ( x[3] - x[1] ) <= tolerance * eta ) ? 1 : 0;
}


////////////////////////////////////////////////////////////////////////////////
//  static int Parabolic_Maximum( double x[], double y[], double *xmax)       //
//                                                                            //
//  Description:                                                              //
//     Given three noncollinear points (x[1],y[1]), (x[2],y[2]), and          //
//     (x[3],y[3]) such that x[1] < x[2] < x[3] and y[1] < y[2] > y[3] find   //
//     the location of the maximum, xmax, of the parabola through these       //
//     points.                                                                //
//                                                                            //
//     For C compilers which support the 'inline' type qualifier, this routine//
//     could be declared with the 'inline' qualifier.                         //
//                                                                            //
//  Return Values:                                                            //
//     0  Success                                                             //
//    -1  The three points are either collinear or the extremum of the        //
//        parabola through the three points is a minimum.                     //
////////////////////////////////////////////////////////////////////////////////
static int Parabolic_Maximum( double x[], double y[], double *xmax) 
{
   double d1 = (x[3] - x[2]) * (y[1] - y[2]);
   double d2 = (x[2] - x[1]) * (y[3] - y[2]);
   double denominator = d1 + d2;
   double numerator = (x[3] + x[2]) * d1 + (x[2] + x[1]) * d2;

   if (denominator >= 0.0) { *xmax = 0.0; return -1; }
   *xmax = 0.5 * numerator / denominator;
   return 0;
}


////////////////////////////////////////////////////////////////////////////////
// static void Check_New_Test_Point( double x[], double *xmax,                //
//                                 double min_displacement, double epsilon )  //
//                                                                            //
//  Description:                                                              //
//     This routine alters the test point, *xmax, in the event that *xmax is  //
//     within min_displacement of one of the nodes x[1], x[2], and x[3].      //
//                                                                            //
//  Return Value:                                                             //
//     void                                                                   //
////////////////////////////////////////////////////////////////////////////////
static void Check_New_Test_Point( double x[], double *xmax,
                                     double min_displacement, double epsilon )
{
   double eta;
   double d1, d2;

                 // Compare the location of the minimum of the
                 // parabolic fit to the center node.

   eta = ( x[2] == 0.0 ) ? 1.0 : fabs(x[2]);
   if ( fabs(*xmax - x[2]) < (min_displacement * eta) ) {
      if ( *xmax == x[2] ) 
         if ( (x[3] - x[2]) > ( x[2] - x[1] ) )
            *xmax = x[2] + alpha * (x[3] - x[2]);
         else *xmax = x[2] - alpha * (x[2] - x[1]);
      else if ( *xmax < x[2] ) 
         if ( x[2] - x[1] < epsilon * eta )
            *xmax = x[2] + (x[2] - x[1]);
         else {
            d1 = epsilon * eta;
            d2 = alpha * (x[2] - x[1]);
            *xmax = x[2] - ( (d1 < d2) ? d1 : d2 );
         }
      else 
         if ( x[3] - x[2] < epsilon * eta )
            *xmax = x[2] - (x[3] - x[2]);
         else {
            d1 = epsilon * eta;
            d2 = alpha * (x[3] - x[2]);
            *xmax = x[2] + ( (d1 < d2) ? d1 : d2 );
         }
      return;
   }

                 // Compare the location of the maximum of the
                 // parabolic fit to the left-most node.

   eta = ( x[1] == 0.0 ) ? 1.0 : fabs(x[1]);
   if ( (*xmax - x[1]) < (min_displacement * eta)) {
      d1 = epsilon * eta;
      d2 = alpha * (x[2] - x[1]);
      *xmax = x[1] + ( (d1 < d2) ? d1 : d2 );
      return;
   }

                 // Compare the location of the maximum of the
                 // parabolic fit to the right-most node.

   eta = ( x[3] == 0.0 ) ? 1.0 : fabs(x[3]);
   if ( (x[3] - *xmax) < (min_displacement * eta)) {
      d1 = epsilon * eta;
      d2 = alpha * (x[3] - x[2]);
      *xmax = x[3] - ( (d1 < d2) ? d1 : d2 );
      return;
   }

   return;
}


////////////////////////////////////////////////////////////////////////////////
//  static void Left_Interior_Point( double (*f)(double), double x[],         //
//                                                              double y[] )  //
//                                                                            //
//  Description:                                                              //
//     Select the new test point using the points (x[0],y[0]), (x[2],y[2]),   //
//     and (x[4],y[4]),  where x[0] < x[2] < x[4] and y[0] < y[2] > y[4].     //
//     Upon return the points (x[0],y[0]), (x[1],y[1]), (x[2],y[2]),          //
//     (x[4],y[4]) are defined with x[0] < x[1] < x[2] < x[4] and             //
//     y[0] < y[1] < y[2] > y[4], where y[i] = f(x[i]).                       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
static void Left_Interior_Point( double (*f)(double), double x[], double y[] )
{
   int not_found = 1;
 
   while (not_found) { 
      x[1] = x[2] - alpha * (x[2] - x[0]);
      y[1] = f(x[1]);
      if ( y[1] <= y[0] ) { x[0] = x[1]; y[0] = y[1]; }
      else if ( y[1] <= y[2] ) not_found = 0;
      else {
         x[4] = x[3]; y[4] = y[3];
         x[3] = x[2]; y[3] = y[2];
         x[2] = x[1]; y[2] = y[1];
      }
   }
}


////////////////////////////////////////////////////////////////////////////////
//  static void Right_Interior_Point( double (*f)(double), double x[],        //
//                                                              double y[] )  //
//                                                                            //
//  Description:                                                              //
//     Given four points (x[0],y[0]), (x[1],y[1]), (x[2],y[2]), and           //
//     (x[4],y[4]), such that x[0] < x[1] < x[2] < x[4] and y[0] < y[1] <     //
//     y[2] > y[4] find points (x[0],y[0]), (x[1],y[1]), (x[2],y[2]),         //
//     (x[3],y[3]) and (x[4],y[4]), such that x[0] < x[1] < x[2] < x[3] < x[4]//
//     y[0] < y[1] < y[2] > y[3] > y[4], where y[i] = f(x[i]).                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
static void Right_Interior_Point( double (*f)(double), double x[], double y[] )
{
   int not_found = 1;
 
   while (not_found) { 
      x[3] = x[2] + alpha * (x[4] - x[2]);
      y[3] = f(x[3]);
      if ( y[3] <= y[4] ) { x[4] = x[3]; y[4] = y[3]; }
      else if ( y[3] <= y[2] ) not_found = 0;
      else {
         x[0] = x[1]; y[0] = y[1];
         x[1] = x[2]; y[1] = y[2];
         x[2] = x[3]; y[2] = y[3];
      }
   }
}
