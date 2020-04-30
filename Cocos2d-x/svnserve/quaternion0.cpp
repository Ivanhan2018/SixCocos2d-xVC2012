#include "quaternion.h"

int main(int argc, char **argv)
{
  cout << "Quaternion class test" << endl;

  cout << "Constructors:" << endl;
  float vect[4] = { 5, 6, 7, 8 };
  float v[3]= { 1.1, 2.34, 7.65 };
  Quaternion <float> q1;
  Quaternion <float> q2(1.0f, 2.0f, 3.0f, 4.0f);
  Quaternion <float> q3(q2);
  Quaternion <float> q4(vect);
  Quaternion <float> q7(3.0f, 1.0f, -2.0f, 1.0f);
  Quaternion <float> q8(2.0f, -1.0f, 2.0f, 3.0f);
  Quaternion <float> q9(3.0f, 1.0f, -2.0f, 1.0f);
  Quaternion <float> q16(0.0f, 1.1f, 2.34f, 7.65f);

  cout << "q1=" << q1 << endl;
  cout << "q2=" << q2 << endl;
  cout << "q3=" << q3 << endl;
  cout << "q4=" << q4 << endl;

  cout << "Operators:" << endl;
  cout << "Operator =" << endl;
  Quaternion <float> q5 = q2;
  cout << "q5 = " << q5 << endl;
  cout << "Operator +" << endl;
  Quaternion <float> q6 =  q5 + q4;
  cout << "q5 + q4 = " << q5 + q4 << endl;  //should equal (6,8,10,12)
  cout << "Operator -" << endl;
  q6 = q5 - q4;
  cout << "q5 - q4 = " << q6 << endl;  //should equal (-4,-4,-4,-4)
  cout << "Operator *" << endl;
  q6 = q7 * q8;
  cout << "q7  * q8 = " << q6 << endl; //should equal (8,-9,-2,11) 
  cout << "Operator /" << endl;
  q6 = q8.inverse();
  cout << "q7/(q8.inverse) = " << q7/q6 << endl;//should equal [8, (-9, -2, 11)]
  cout << "Operator += " << endl;
  q4 += q5;
  cout << "q4 += q5 is " << q4 << endl;//should equal [6, (8, 10, 12)]
  cout << "Operator -= " << endl;
  q5 -= q5;
  cout << "q5 -= q5 is " << q5 << endl;//should equal [0, (0, 0, 0)]
  cout << "Operator *= " << endl;
  q7 *= q8;
  cout << "q7 *= q8 is " << q7 << endl;//should equal [8, (-9, -2, 11)]
  cout << "Operator /= " << endl;
  q7= q9;
  q6 = q8.inverse();
  q7/=q6;
  cout << "q7 /= q8.inverse() is " << q7 << endl;//should equal [8, (-9, -2, 11)]
  cout << "Operator != " << endl;
  if (q2 != q2)
    cout << "doesn't work:(" << endl;
  else
    cout << "works!" << endl;
  cout << "Operator == " << endl;
  if (q2 == q2)
    cout << "works!" << endl;
  else
    cout << "doesn't work:(" << endl;
  cout << "Norm of q2 = " << q2.norm() << endl; //30
  cout << "Magnitude of q2 = " << q2.magnitude() << endl; //5.4772255....
  q6 = q2.scale(2);
  cout << "Scale of q2 by 2 = " << q6 << endl;//should equal [2, (4, 6, 8)]
  cout << "Inverse of q8 = " << q8.inverse() << endl;//should equal [0.111..., (0.0555..., -0.111..., -0.1666...)]
  cout << "Conjugate of q8 = " << q8.conjugate() <<endl;  //should equal (2,1,-2,-3)
  cout << "Unit Quaternion of q8 is " << q8.UnitQuaternion() << endl;
  //QuatRot 
  q8.QuatRotation(v);
  cout << "Rotate q8 by 1.1, 2.34, 7.65 = " << v[0] << ", " << v[1] << ", " << v[2] << endl;
   //should get the same answer as QuatRot(v, q8) ignoring the w factor
  q2=q8*q16;
  q3=q2*(q8.inverse());
  cout << q3 << endl;
  
  return 0;
}