// Lab 2: Hugeint.cpp
// HugeInt member-function and friend-function definitions.
#include <iostream>
#include <cctype> // isdigit function prototype
#include <cstring> // strlen function prototype
using namespace std;
#include<cstdio>
#include "Hugeint.h" // HugeInt class definition


// default constructor; conversion constructor that converts
// a long integer into a HugeInt object
HugeInt::HugeInt( long value )
{
   // initialize array to zero
   for ( int i = 0; i <= 29; i++ )
      integer[ i ] = 0;

   // place digits of argument into array
   for ( int j = 29; value != 0 && j >= 0; j-- )
   {
      integer[ j ] = value % 10;
      value /= 10;
   }

    // end for
} // end HugeInt default/conversion constructor

// conversion constructor that converts a character string
// representing a large integer into a HugeInt object
HugeInt::HugeInt( const char *string )
{
   // initialize array to zero
   for ( int i = 0; i <= 29; i++ )
      integer[ i ] = 0;

   // place digits of argument into array
   int length = strlen( string );

   for ( int j = 30 - length, k = 0; j <= 29; j++, k++ )

      if ( isdigit( string[ k ] ) )
         integer[ j ] = string[ k ] - '0';

} // end HugeInt conversion constructor

// get function calculates length of integer
int HugeInt::getLength() const
{
   int i=0;
   for (  i = 0; i <= 29; i++ )
      if ( integer[ i ] != 0 )
         break; // break when first digit is reached

   return 30 - i; // length is from first digit (at i) to end of array
} // end function getLength

// addition operator; HugeInt + HugeInt
HugeInt HugeInt::operator+( const HugeInt &op2 ) const
{
   HugeInt temp; // temporary result
   int carry = 0;

   for ( int i = 29; i >= 0; i-- )
   {
      temp.integer[ i ] =
         integer[ i ] + op2.integer[ i ] + carry;

      // determine whether to carry a 1
      if ( temp.integer[ i ] > 9 )
      {
         temp.integer[ i ] %= 10;  // reduce to 0-9
         carry = 1;
      } // end if
      else // no carry
         carry = 0;
   } // end for

   return temp; // return copy of temporary object
} // end function operator+
HugeInt HugeInt::operator-( HugeInt &right) const
{
    HugeInt temp;
    int b=0,a=0;
    if(*this>right){
    for(int i=29;i>(29-this->getLength());i--)
    {
        temp.integer[i]=this->integer[i]-right.integer[i]+10+b;
        b=0;
        if(temp.integer[i]/10!=0)
            temp.integer[i]=temp.integer[i]%10;
        else
            b--;
    }

    }
    else{

        for(int i=29;i>(29-right.getLength());i--)
    {

        a+=right.integer[i]+10;
        a-=this->integer[i];
        temp.integer[i]=a%10;
        a=a/10;
        a--;
    }
    }
    return temp;
}
// addition operator; HugeInt + int
HugeInt HugeInt::operator+( int op2 ) const
{
   // convert op2 to a HugeInt, then invoke
   // operator+ for two HugeInt objects
   return *this + HugeInt( op2 );
} // end function operator+

// addition operator;
// HugeInt + string that represents large integer value
HugeInt HugeInt::operator+( const char *op2 ) const
{
   // convert op2 to a HugeInt, then invoke
   // operator+ for two HugeInt objects
   return *this + HugeInt( op2 );
} // end function operator+

// equality operator; HugeInt == HugeInt
/* Write a definition for the == operator */
bool HugeInt::operator==( HugeInt &right) const
{
    int a,b,flag1=0,flag2=1;
    a=getLength();
    b=right.getLength();

    if(a==b)
        flag1=1;
    else
        return false;
    for(int i=30-a;i<=29;i++){
        if(integer[i]!=right.integer[i])
            {flag2=0;
            break;}
    }
    if(flag1==1&&flag2==1)
        return true;
    return false;
}
// inequality operator; HugeInt != HugeInt
/* Write a definition for the != operator
   by calling the == operator */
bool HugeInt::operator!=(  HugeInt &right) const
{
    if(*this==right)
        return false;
    return true;
}
// less than operator; HugeInt < HugeInt
/* Write a definition for the < operator */
bool HugeInt::operator< ( HugeInt &right) const
{
    int a,b;
    a=getLength();
    b=right.getLength();
    if(a<b)
        return true;
    if(a>b)
        return false;

    for(int i=30-a;i<=29;i++){
        if(integer[i]<right.integer[i])
            return true;
    }

    return false;
}
// less than or equal operator; HugeInt <= HugeInt
/* Write a definition for the <= operator
   by calling the < and == operators */
bool HugeInt::operator<=( HugeInt &right) const
{

    if(*this<right||*this==right)
        return true;
    return false;
}
// greater than operator; HugeInt > HugeInt
/* Write a definition for the > operator
   by calling the <= operator */
bool HugeInt::operator> ( HugeInt &right) const
{
    if(*this<=right)
        return false;
    return true;
}
// greater than or equal operator; HugeInt >= HugeInt
/* Write a definition for the >= operator
   by calling the > and == operators */
bool HugeInt::operator>=( HugeInt &right) const
{
    if(*this==right||*this>right)
        return true;
    return false;
}
// overloaded output operator
ostream& operator<<( ostream &output, const HugeInt &num )
{
   int i;

   for ( i = 0; ( num.integer[ i ] == 0 ) && ( i <= 29 ); i++ )
      ; // skip leading zeros

   if ( i == 30 )
      output << 0;
   else

      for ( ; i <= 29; i++ )
         output << num.integer[ i ];

   return output;
} // end function operator<<


/**************************************************************************
 * (C) Copyright 1992-2012 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
