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
#include "simple_register.h"
#include "display_register.h"
#include "rotate_left_register.h"
#include "rotate_right_register.h"
#include "bitwise_and_not_register.h"
#include "return_zero_register.h"
#include "conditional_register.h"
#include "sum_register.h"
#include "not_register.h"

#include <iostream>
using namespace std;

wireworld_computer::wireworld_computer(void)
{

  //Creating registers
  m_registers[0] = new display_registre();
  for(uint32_t l_index = 1; l_index <= 52 ; ++l_index)
    {
      m_registers[l_index] = new simple_registre();
    }
  simple_registre * const l_reg_53 = new simple_registre();
  simple_registre * const l_reg_54 = new simple_registre();
  m_registers[53] = new bitwise_and_not_registre(l_reg_53,l_reg_54);
  m_registers[54] = new bitwise_and_not_registre(l_reg_54,l_reg_53);
  return_zero_registre * const l_reg_55 = new return_zero_registre();
  return_zero_registre * const l_reg_57 = new return_zero_registre();
  m_registers[55] = l_reg_55;
  m_registers[56]= new conditional_registre(l_reg_55,l_reg_57);
  m_registers[57] = l_reg_57;
  m_registers[58] = new rotate_right_registre();
  m_registers[59] = new rotate_left_registre();
  m_registers[60] = new simple_registre();
  m_registers[61] = new sum_registre(m_registers[60]);
  m_registers[62] = new not_registre();
  m_registers[63] = new simple_registre();

#ifdef TOTO
  // Initialising register values
  m_registers[1]->write(0x1E);
  m_registers[2]->write(0x361F);
  m_registers[3]->write(0x2021);
  m_registers[4]->write(0x3C22);
  m_registers[5]->write(0x3D23);
  m_registers[6]->write(0x3C3D);
  m_registers[7]->write(0x3D20);
  m_registers[8]->write(0x3924);
  m_registers[9]->write(0x3725);
  m_registers[10]->write(0x383D);
  m_registers[11]->write(0x3F38);
  m_registers[12]->write(0x3D3D);
  m_registers[13]->write(0x3D3D);
  m_registers[14]->write(0x353D);
  m_registers[15]->write(0x3926);
  m_registers[16]->write(0x3727);
  m_registers[17]->write(0x3836);
  m_registers[18]->write(0x3F38);
  m_registers[19]->write(0x3928);
  m_registers[20]->write(0x0020);
  m_registers[21]->write(0x3D20);
  m_registers[22]->write(0x3C1E);
  m_registers[23]->write(0x3F29);
  m_registers[24]->write(0x203D);
  m_registers[30]->write(0x2);
  m_registers[31]->write(0x7FFF);
  m_registers[32]->write(0x0005);
  m_registers[33]->write(0x0003);
  m_registers[34]->write(0xFFFE);
  m_registers[35]->write(0xFFFD);
  m_registers[36]->write(0x0014);
  m_registers[37]->write(0x000D);
  m_registers[38]->write(0x0009);
  m_registers[39]->write(0x0005);
  m_registers[40]->write(0x0015);
  m_registers[41]->write(0x0004);
  m_registers[42]->write(0xFFFC);
  m_registers[63]->write(1);
#endif
  m_registers[63]->write(1);
  // Initialisation running variable to 0
  m_registers[41]->write(0);
  // Set upper limit
  m_registers[42]->write(10);
  // Branch value to restart the loop
  m_registers[43]->write(0x2);
  // Branch value to end the loop
  m_registers[44]->write(12);
  // Increment value
  m_registers[45]->write(1);
  //Final value
  m_registers[46]->write(0xFFFF);
  // Branch value to continue the loop
  m_registers[47]->write(0x9);

  // Compute negative value of upper limit
  m_registers[1]->write(0x3E2A);
  //current variable as second operand of adder
  m_registers[2]->write(0x3D29);
  //negative upper limite as first operand of adder
  m_registers[3]->write(0x3C3E);
  // perform addition
  m_registers[4]->write(0x383D);
  // Prepare branch if limit non reached
  m_registers[5]->write(0x372F);
  // Prepare branch if limit reached
  m_registers[6]->write(0x392C);
  // Branch on addition result
  m_registers[7]->write(0x3F38);
  // Preparing addition
  m_registers[8]->write(0x3C2D);
  //Display variable
  m_registers[9]->write(0x0029);
  // Preparing branch at the beginning of the loop
  m_registers[10]->write(0x3F2B);
  // Incrementing current variable
  m_registers[11]->write(0x293D);
  // Branching on end of the loop
  m_registers[12]->write(0x3F2C);
  // End of loop
  m_registers[13]->write(0x002E);
  
}

uint8_t wireworld_computer::decodeDestination(uint16_t p_instr)
{
  return (0x3F00 & p_instr) >> 8;
}

uint8_t wireworld_computer::decodeSource(uint16_t p_instr)
{
  return 0x3F & p_instr;
}

uint16_t wireworld_computer::getInstruction(void)
{
  cout << "PC value :" ;
  uint16_t l_pc = m_registers[63]->read();
  cout << "=> PC = " << hex << l_pc << dec << endl ;
  m_registers[63]->write(l_pc+1);
  return m_registers[l_pc]->read();
}

void wireworld_computer::execInstruction(uint16_t p_instr)
{
  cout << "=> Instruction = " << hex << p_instr << dec << endl ;
  uint16_t l_destination = decodeDestination(p_instr);
  uint16_t l_source = decodeSource(p_instr);
  cout << "=> MOV R" << l_destination << ", R" << l_source <<  endl ;
  cout << "R" << l_source << " => " ;
  uint16_t l_value = m_registers[l_source]->read();
  cout << hex << l_value << dec << " => " ;
  cout << "R" << l_destination << endl ;
  m_registers[l_destination]->write(l_value);
}

void wireworld_computer::run(void)
{
  cout << "Start running" << endl ;
  uint32_t l_nb_cycle = 0;
  uint16_t l_instr = getInstruction();
  while(1)
    {
      cout << "***** Starting cycle " << l_nb_cycle << "*****" << endl ;
      uint16_t l_new_instr = getInstruction();
      execInstruction(l_instr);
      l_instr = l_new_instr;
      sleep(1);
      ++l_nb_cycle;
    }
  cout << "Run finished" << endl ;
}

//EOF
