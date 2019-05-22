#include <iostream>
using	namespace	std;
/*-----------------------------------------------------------
Function: Default constructor for the complex class objects,
  assigns 0s to rpart and ipart variables.
Parameters: None
*/
complex::complex(){
  rpart = 0;
  ipart = 0;
}
/*-----------------------------------------------------------
Function: Main constructor for complex objects. Assigns
  specific values to rpart and ipart variables.
Parameters: Float for rpart amd float for ipart.
*/
complex::complex(float x, float y){
  rpart = x;
  ipart = y;
}
/*-----------------------------------------------------------
Function: Creates complex object i as a variable inside
  all complex objects.
Parameters: Hardcoded as 0, 1
*/
complex const complex::i(0,1);
/*-----------------------------------------------------------
Function: Friend function to complex class, aalows output of
  complex objects
Parameters: Output command, generally cout, as outfile, and a
  complex on rhs
Returns: Output of value of complex object
*/
ostream&   operator<<(ostream& outfile, const complex& z) {
  if (z.rpart == 0) outfile << z.ipart << "i";
  else outfile << z.rpart << "+" << z.ipart << "i";
  return outfile;
}
/*-----------------------------------------------------------
Function: Overload of boolean equality operator for comples
  objects
Parameters: A complex obect
Returns: A value of true or false depending on if rhs complex
  has same values as lhs complex.
*/
bool    complex::operator==(const complex& rhs) const{
  // Check if lhs complex equals rhs complex
  if (rpart == rhs.rpart && ipart == rhs.ipart)
    return 1; // if rpart and ipart are equal, return true
  else
    return 0;
}
/*-----------------------------------------------------------
Function: Overload of assignment operator for a complex object
Parameters: A float on rhs of operator, object on lhs
Returns: Well, it returns the float as the rpart real number
  of the complex. I couldn't find any actual application for
  it.
*/
const   complex& complex::operator=(float rhs){
  // A complex assigned a float
  rpart = rhs;
}
/*-----------------------------------------------------------
Function: Overloads assignment operator
Parameters: A complex object on rhs, assigned to complex on
  lhs
*/
const   complex& complex::operator=(const complex& rhs){
  //Assign values at rhs to current object;
  rpart = rhs.rpart;
  ipart = rhs.ipart;
}
/*-----------------------------------------------------------
Function: Overloads addition operator
Parameters: Float number lhs, complex object rhs
Returns: complex object with correct adjustments to values
*/
complex operator+(float lhs, const complex& rhs){
  //flt + (a+bi)
  complex fltSum;
  // Add the real numbers.
  // flt + a assigned to complex:
  fltSum.rpart = lhs+rhs.rpart;
  // ipart of recieved complex assigned:
  fltSum.ipart = rhs.ipart;
  return fltSum;
}
/*-----------------------------------------------------------
Function: Overloads subtraction operator
Parameters: Float number lhs, complex object rhs
Returns:complex object with correct adjustments to values
*/
complex operator-(float lhs, const complex& rhs){
  //flt - (a+bi)
  complex fltSub;
  // Subtract the real numbers.
  // flt - a assigned to complex:
  fltSub.rpart = lhs-rhs.rpart;
  // ipart of recieved complex assigned:
  fltSub.ipart = rhs.ipart;
  return fltSub;
}
/*-----------------------------------------------------------
Function: Overloads multiplication operator
Parameters: Float number lhs, complex object rhs
Returns:complex object with correct adjustments to values
*/
complex operator*(float lhs, const complex& rhs){
  //flt * (a+bi)
  complex fltMul;
  //Multiply r and i numbers by flt.
  // flt * a assigned to complex rpart:
  fltMul.rpart = lhs*rhs.rpart;
  // flt * b assigned to complex ipart:
  fltMul.ipart = lhs*rhs.ipart;
  return fltMul;
}
/*-----------------------------------------------------------
Function: Overloads division operator
Parameters: Float number lhs, complex object rhs
Returns:complex object with correct adjustments to values
*/
complex operator/(float lhs, const complex& rhs){
  //flt / (a+bi)
  complex fltDiv;
  // Divide r and i numbers from flt.
  // flt/a assigned to rpart of complex:
  fltDiv.rpart = lhs/rhs.rpart;
  // flt/b assigned to ipart of complex:
  fltDiv.ipart = lhs/rhs.ipart;
  return fltDiv;
}
/*-----------------------------------------------------------
Function: Overloads addition operator
Parameters: comples object on rhs
Returns:complex object with correct adjustments to values
*/
complex complex::operator+(const complex& rhs) const {
  complex sum;
  sum.rpart = rpart+rhs.rpart;
  sum.ipart = ipart+rhs.ipart;
  return sum;
}
/*-----------------------------------------------------------
Function: Overloads addition operator
Parameters: float on rhs
Returns:complex object with correct adjustments to values
*/
complex complex::operator+(float rhs) const{
  // (a+bi) + c
  complex addFlt;  //Object to return
  // rpart = added real numbers
  addFlt.rpart = rpart + rhs;
  // ipart = lhs.ipart
  addFlt.ipart = ipart;
  return addFlt;
}
/*-----------------------------------------------------------
Function: Overloads subtraction operator
Parameters: comples object on rhs
Returns:complex object with correct adjustments to values
*/
complex complex::operator-(const complex& rhs) const{
  //(a + bi)-(c + di) = (a - c)+(b - d)i
  // rpart = a; ipart = b; rhs.rpart = c; rhs.ipart = d
  complex sub;
  // rpart = a - c
  sub.rpart = rpart-rhs.rpart;
  // ipart = b - d
  sub.ipart = ipart-rhs.ipart;
  return sub;
}
/*-----------------------------------------------------------
Function: Overloads subtraction operator
Parameters: float on rhs
Returns:complex object with correct adjustments to values
*/
complex complex::operator-(float rhs) const{
  // (a+bi) - c
  complex subFlt;  //Object to return
  // rpart = subtract real numbers
  subFlt.rpart = rpart - rhs;
  // ipart = lhs.ipart
  subFlt.ipart = ipart;
  return subFlt;
}
/*-----------------------------------------------------------
Function: Overloads subtraction operator
Parameters: None
Returns:complex object with correct adjustments to values
*/
complex complex::operator-() const{
  //Making negative:
  complex neg;  //Object to return
  neg.rpart = rpart * -1; //rpart made negative
  neg.ipart = ipart * -1; //ipart made negative
  return neg;
}
/*-----------------------------------------------------------
Function: Overloads multiplication operator
Parameters: comples object on rhs
Returns:complex object with correct adjustments to values
*/
complex complex::operator*(const complex& rhs) const{
  // (a + bi)(c + di) = (ac - bd)+(ad + bc)i
  // rpart = a; ipart = b; rhs.rpart = c; rhs.ipart = d
  complex mlt;  //Object to return
  // rpart = (a*c) - (b*d)
  mlt.rpart = (rpart * rhs.rpart) - (ipart*rhs.ipart);
  // ipart = (a*d) + (b*c)
  mlt.ipart = (rpart * rhs.ipart) + (ipart*rhs.rpart);
  return mlt;
}
/*-----------------------------------------------------------
Function: Overloads multiplication operator
Parameters: comples object on rhs
Returns:complex object with correct adjustments to values
*/
complex complex::operator*(float rhs) const{
  //(a + bi) * c
  complex mltFlt;  //Object to return
  // rpart = (a*c)
  mltFlt.rpart = rpart * rhs;
  // ipart = (b*c)
  mltFlt.ipart = ipart * rhs;
  return mltFlt;
}
/*-----------------------------------------------------------
Function: Overloads division operator
Parameters: float on rhs
Returns:complex object with correct adjustments to values
*/
complex complex::operator/(const complex& rhs) const{
  // (a+bi)/(c+di) = (ac+bd)+(bc-ad)i / (c^2 + d^2)
  // rpart = a; ipart = b; rhs.rpart = c; rhs.ipart = d
  complex div;  //Object to return
  // rpart = (ac+bd) / (c^2 + d^2)
  div.rpart = ((rpart * rhs.rpart) + (ipart*rhs.ipart)) / ((rhs.rpart*rhs.rpart)+ (rhs.ipart*rhs.ipart));
  // ipart = (bc-ad)i / (c^2 + d^2)
  div.ipart = ((ipart * rhs.rpart) - (rpart*rhs.ipart)) / ((rhs.rpart*rhs.rpart)+ (rhs.ipart*rhs.ipart));
  return div;
}
/*-----------------------------------------------------------
Function: Overloads division operator
Parameters: float on rhs
Returns:complex object with correct adjustments to values
*/
complex complex::operator/(float rhs) const{
  // (a+bi)/c
  complex divFlt;
  // rpart = lhs.rpart/float
  divFlt.rpart = rpart / rhs;
  // ipart = lhs.ipart / float
  divFlt.ipart = ipart / rhs;
  return divFlt;
}

// Main
int main(){

cout << "-----------Formula:------------------" << endl;
  // (4y^2-2y-1)/(i+1) = 1.5 + 4.5i
  //(4(-(1+2i)/2)(-(1+2i)/2)-2(-(1+2i)/2)-1)/(i+1)
  //---------------------------
  // y = -(1+2i) / 2 = (-0.5 - i)
  complex y;
  complex z(1,1);
  y = -(1+y.i*2)/2;
  //y.i(0,1);
  cout << "   y == " << y << endl;
  y = ( 4*(y*y) + (-2*y) - 1) / z;
  cout << "  (4y^2-2y-1)/(i+1) "
       << endl << "       == 1.5+4.5i"
       << endl << "Result == " << y << endl;


cout << "--------------End------------------" << endl;
  return 0;
}
