/*
    This file is part of wireworld_computer
    Copyright (C) 2010  Julien Thevenon ( julien_thevenon at yahoo.fr )

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include "wireworld_computer.h"

#include <cstdlib>
#include <iostream>

using namespace std;

int main(void)
{
  typedef wireworld_computer::register_information t_reg_info;
  typedef wireworld_computer::wireworld_computer::t_register_informations t_reg_infos;
  t_reg_infos l_register_informations;

#define ORIGINAL_CODE
#ifdef ORIGINAL_CODE
    // Initialising register values
  l_register_informations.insert(t_reg_infos::value_type(1,t_reg_info(true,0x001E,"set display to 2")));
  l_register_informations.insert(t_reg_infos::value_type(2,t_reg_info(true,0x361F,"initialise mask register for sign bit test")));
  l_register_informations.insert(t_reg_infos::value_type(3,t_reg_info(true,0x2021,"set candidate prime p=3")));
  l_register_informations.insert(t_reg_infos::value_type(4,t_reg_info(true,0x3C22,"the trial divisor q is stored in the adder as its negative: here it is initialised to -1, i.e. q=1")));
  l_register_informations.insert(t_reg_infos::value_type(5,t_reg_info(true,0x3D23,"other summand=-2")));
  l_register_informations.insert(t_reg_infos::value_type(6,t_reg_info(true,0x3C3D,"next trial divisor q=q+2")));
  l_register_informations.insert(t_reg_infos::value_type(7,t_reg_info(true,0x3D20,"move p to adder summand input a, which holds remainder")));
  l_register_informations.insert(t_reg_infos::value_type(8,t_reg_info(true,0x3924,"for the first time round the loop, set the target for the branch if subtraction gives zero to 20: this detects the case p==q, which means we have done all the trial divisors and p is prime")));
  l_register_informations.insert(t_reg_infos::value_type(9,t_reg_info(true,0x3725,"if subtraction result non-zero, target is 13")));
  l_register_informations.insert(t_reg_infos::value_type(10,t_reg_info(true,0x383D,"test a-q")));
  l_register_informations.insert(t_reg_infos::value_type(11,t_reg_info(true,0x3F38,"branch to selected target")));
  l_register_informations.insert(t_reg_infos::value_type(12,t_reg_info(true,0x3D3D,"a-=q")));
  l_register_informations.insert(t_reg_infos::value_type(13,t_reg_info(true,0x3D3D,"a-=q (continuing here if subtraction result not zero)")));
  l_register_informations.insert(t_reg_infos::value_type(14,t_reg_info(true,0x353D,"move a-q to and-not register to check sign")));
  l_register_informations.insert(t_reg_infos::value_type(15,t_reg_info(true,0x3926,"target is 9 if a-q positive (round subtraction loop again)")));
  l_register_informations.insert(t_reg_infos::value_type(16,t_reg_info(true,0x3727,"else target is 5 (q does not divide p, so try next q)")));
  l_register_informations.insert(t_reg_infos::value_type(17,t_reg_info(true,0x3836,"test a-q AND 0x8000")));
  l_register_informations.insert(t_reg_infos::value_type(18,t_reg_info(true,0x3F38,"branch to selected target")));
  l_register_informations.insert(t_reg_infos::value_type(19,t_reg_info(true,0x3928,"reset target for other branch to 21 (a zero result from the subtraction now indicates q properly divides p and so p is composite)")));
  l_register_informations.insert(t_reg_infos::value_type(20,t_reg_info(true,0x0020,"p is prime: write it to the display")));
  l_register_informations.insert(t_reg_infos::value_type(21,t_reg_info(true,0x3D20,"move p to adder")));
  l_register_informations.insert(t_reg_infos::value_type(22,t_reg_info(true,0x3C1E,"other summand=2")));
  l_register_informations.insert(t_reg_infos::value_type(23,t_reg_info(true,0x3F29,"goto 4 to try new p")));
  l_register_informations.insert(t_reg_infos::value_type(24,t_reg_info(true,0x203D,"p+=2")));

  l_register_informations.insert(t_reg_infos::value_type(30,t_reg_info(false,0x2,"constant 2")));
  l_register_informations.insert(t_reg_infos::value_type(31,t_reg_info(false,0x7FFF,"constant mask for sign bit testing")));
  l_register_informations.insert(t_reg_infos::value_type(32,t_reg_info(false,0x0005,"current candidate p","p")));
  l_register_informations.insert(t_reg_infos::value_type(33,t_reg_info(false,0x0003,"constant 3")));
  l_register_informations.insert(t_reg_infos::value_type(34,t_reg_info(false,0xFFFE,"constant -1")));
  l_register_informations.insert(t_reg_infos::value_type(35,t_reg_info(false,0xFFFD,"constant -2")));
  l_register_informations.insert(t_reg_infos::value_type(36,t_reg_info(false,0x0014,"branch target: trial divisor q equal to candidate p, and hence prime found","Label_36")));
  l_register_informations.insert(t_reg_infos::value_type(37,t_reg_info(false,0x000D,"branch target: trial divisor q less than candidate p","Label_37")));
  l_register_informations.insert(t_reg_infos::value_type(38,t_reg_info(false,0x0009,"branch target: more subtractions to do","Label_38")));
  l_register_informations.insert(t_reg_infos::value_type(39,t_reg_info(false,0x0005,"branch target: next trial divisor q","Label_39")));
  l_register_informations.insert(t_reg_infos::value_type(40,t_reg_info(false,0x0015,"branch target: subtraction gave zero, so p composite","Label_40")));
  l_register_informations.insert(t_reg_infos::value_type(41,t_reg_info(false,0x0004,"branch target: next candidate p","Label_41")));
  l_register_informations.insert(t_reg_infos::value_type(42,t_reg_info(false,0xFFFC,"constant -3")));

  l_register_informations.insert(t_reg_infos::value_type(63,t_reg_info(false,1,"Starting PC","PC")));

#else // MY SIMPLE LOOP CODE
  l_register_informations.insert(t_reg_infos::value_type(63,t_reg_info(false,1,"Initial PC","PC")));
  l_register_informations.insert(t_reg_infos::value_type(41,t_reg_info(false,0,"Initialisation running variable to 0")));
  l_register_informations.insert(t_reg_infos::value_type(42,t_reg_info(false,10,"Set upper limit")));
  l_register_informations.insert(t_reg_infos::value_type(43,t_reg_info(false,0x2,"Branch value to restart the loop")));
  l_register_informations.insert(t_reg_infos::value_type(44,t_reg_info(false,12,"Branch value to end the loop")));
  l_register_informations.insert(t_reg_infos::value_type(45,t_reg_info(false,1,"Increment value")));
  l_register_informations.insert(t_reg_infos::value_type(46,t_reg_info(false,0xFFFF,"Final value")));
  l_register_informations.insert(t_reg_infos::value_type(47,t_reg_info(false,0x9,"Branch value to continue the loop")));



  l_register_informations.insert(t_reg_infos::value_type(1,t_reg_info(true,0x3E2A,"Compute negative value of upper limit")));
  l_register_informations.insert(t_reg_infos::value_type(2,t_reg_info(true,0x3D29,"current variable as second operand of adder")));
  l_register_informations.insert(t_reg_infos::value_type(3,t_reg_info(true,0x3C3E,"negative upper limite as first operand of adder")));
  l_register_informations.insert(t_reg_infos::value_type(4,t_reg_info(true,0x383D,"perform addition")));
  l_register_informations.insert(t_reg_infos::value_type(5,t_reg_info(true,0x372F,"Prepare branch if limit non reached")));
  l_register_informations.insert(t_reg_infos::value_type(6,t_reg_info(true,0x392C,"Prepare branch if limit reached")));
  l_register_informations.insert(t_reg_infos::value_type(7,t_reg_info(true,0x3F38,"Branch on addition result")));
  l_register_informations.insert(t_reg_infos::value_type(8,t_reg_info(true,0x3C2D,"Preparing addition")));
  l_register_informations.insert(t_reg_infos::value_type(9,t_reg_info(true,0x0029,"Display variable")));
  l_register_informations.insert(t_reg_infos::value_type(10,t_reg_info(true,0x3F2B,"Preparing branch at the beginning of the loop")));
  l_register_informations.insert(t_reg_infos::value_type(11,t_reg_info(true,0x293D,"Incrementing current variable")));
  l_register_informations.insert(t_reg_infos::value_type(12,t_reg_info(true,0x3F2C,"Branching on end of the loop")));
  l_register_informations.insert(t_reg_infos::value_type(13,t_reg_info(true,0x002E,"End of loop")));
#endif // ORIGINAL_CODE

  wireworld_computer::wireworld_computer l_computer(l_register_informations);
  l_computer.run();
  return 0;
}
