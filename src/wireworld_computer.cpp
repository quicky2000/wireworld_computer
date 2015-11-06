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
#include "quicky_exception.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#ifndef WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif
using namespace std;

namespace wireworld_computer
{
  //----------------------------------------------------------------------------
  wireworld_computer::wireworld_computer(const t_register_informations & p_informations)
  {

    //Creating registers
    m_registers[0] = new display_register();
    for(uint32_t l_index = 1; l_index <= 52 ; ++l_index)
      {
	m_registers[l_index] = new simple_register();
      }
    simple_register * const l_reg_53 = new simple_register();
    simple_register * const l_reg_54 = new simple_register();
    m_registers[53] = new bitwise_and_not_register(l_reg_53,l_reg_54);
    m_registers[54] = new bitwise_and_not_register(l_reg_54,l_reg_53);
    return_zero_register * const l_reg_55 = new return_zero_register();
    return_zero_register * const l_reg_57 = new return_zero_register();
    m_registers[55] = l_reg_55;
    m_registers[56]= new conditional_register(l_reg_55,l_reg_57);
    m_registers[57] = l_reg_57;
    m_registers[58] = new rotate_right_register();
    m_registers[59] = new rotate_left_register();
    m_registers[60] = new simple_register();
    m_registers[61] = new sum_register(m_registers[60]);
    m_registers[62] = new not_register();
    m_registers[63] = new simple_register();

    // Load software in registers
    unsigned int l_max_label_size = 0;
    for(auto l_register_iter:p_informations)
      {
	unsigned int l_register_id = l_register_iter.first;
	if(l_register_id > 63)
	  {
	    std::stringstream l_stream;
	    l_stream << l_register_id;
	    throw quicky_exception::quicky_logic_exception("Register Id " + l_stream.str() + " is greater then max register id 63",__LINE__,__FILE__);
	  }
	if(l_register_iter.second.get_label().size() > l_max_label_size)
	  {
	    l_max_label_size = l_register_iter.second.get_label().size();
	  }
	m_registers[l_register_id]->write(l_register_iter.second.get_initial_value());
      }

    // Pretty print of software
    std::string l_empty_label = l_max_label_size ?  std::string(4 + l_max_label_size, ' ') : "";
    for(unsigned int l_index=0 ; l_index < 64 ; ++l_index)
      {
	std::cout << setfill(' ') << setw(2) << l_index << " : ";
	t_register_informations::const_iterator l_info_iter = p_informations.find(l_index);
	if(p_informations.end() != l_info_iter)
	  {
	    if("" != l_info_iter->second.get_label())
	      {
		std::cout << "<" << l_info_iter->second.get_label() << ">";
		if(l_info_iter->second.get_label().size() < l_max_label_size)
		  {
		    std::cout << std::string(l_max_label_size - l_info_iter->second.get_label().size(),' ');
		  }
		std::cout << ": ";
	      }
	    else
	      {
		std::cout << l_empty_label;
	      }
	    std::stringstream l_stream;
	    if(l_info_iter->second.is_instruction())
	      {
		uint16_t l_destination = decodeDestination(l_info_iter->second.get_initial_value());
		std::stringstream l_dest_stream;
		l_dest_stream << l_destination;
		std::string l_dest_str = l_dest_stream.str();
		if(l_dest_str.size() != 2)
		  {
		    l_dest_str += ' ';
		  }
		uint16_t l_source = decodeSource(l_info_iter->second.get_initial_value());
		l_stream << "MOV R" << l_dest_str << ", R" << l_source;
	      }
	    else
	      {
		l_stream << "0x" << setfill('0') << setw(4) << hex << l_info_iter->second.get_initial_value() << dec;
	      }
	    std::string l_content = l_stream.str();
	    std::cout << l_content;
	    if("" != l_info_iter->second.get_comment())
	      {
		if(l_content.size() < 12)
		  {
		    std::cout << std::string(12 - l_content.size(),' ');
		  }
		std::cout << " ; " << l_info_iter->second.get_comment();
	      }
	  }
	else
	  {
	    if(l_max_label_size)
	      {
		std::cout << l_empty_label;
	      }
	    if((l_index >= 1 && l_index <= 52) || 60 == l_index || 63 == l_index)
	      {
		std::cout << "0x" << setfill('0') << setw(4) << hex << m_registers[l_index]->read() << dec;
	      }
	    else
	      {
		std::cout << "SPECIAL REG";
	      }
	  }
	std::cout << std::endl ;
      }
#if 0
#ifdef ORIGINAL_CODE
    // Initialising register values
    // 1  001e  MOV R0 ,R30  ; set display to 2
    m_registers[1]->write(0x001E);

    // 2  361f  MOV R54,R31  ; initialise mask register for sign bit test
    m_registers[2]->write(0x361F);

    // 3  2021  MOV R32,R33  ; set candidate prime p=3
    m_registers[3]->write(0x2021);

    // 4  3c22  MOV R60,R34  ; the trial divisor q is stored in the adder as its
    //                       ; negative: here it is initialised to -1, i.e. q=1
    m_registers[4]->write(0x3C22);

    // 5  3d23  MOV R61,R35  ; other summand=-2
    m_registers[5]->write(0x3D23);

    // 6  3c3d  MOV R60,R61  ; next trial divisor q=q+2
    m_registers[6]->write(0x3C3D);

    // 7  3d20  MOV R61,R32  ; move p to adder summand input a, which holds remainder
    m_registers[7]->write(0x3D20);

    // 8  3924  MOV R57,R36  ; for the first time round the loop, set the target
    //                       ; for the branch if subtraction gives zero to 20: this
    //                       ; detects the case p==q, which means we have done all
    //                       ; the trial divisors and p is prime
    m_registers[8]->write(0x3924);

    // 9  3725  MOV R55,R37  ; if subtraction result non-zero, target is 13
    m_registers[9]->write(0x3725);

    //10  383d  MOV R56,R61  ; test a-q
    m_registers[10]->write(0x383D);

    //11  3f38  MOV R63,R56  ; branch to selected target
    m_registers[11]->write(0x3F38);

    //12  3d3d  MOV R61,R61  ; a-=q
    m_registers[12]->write(0x3D3D);

    //13  3d3d  MOV R61,R61  ; a-=q (continuing here if subtraction result not zero)
    m_registers[13]->write(0x3D3D);

    //14  353d  MOV R53,R61  ; move a-q to and-not register to check sign
    m_registers[14]->write(0x353D);

    //15  3926  MOV R57,R38  ; target is 9 if a-q positive (round subtraction loop
    //                       ; again)
    m_registers[15]->write(0x3926);

    //16  3727  MOV R55,R39  ; else target is 5 (q does not divide p, so try next q)
    m_registers[16]->write(0x3727);

    //17  3836  MOV R56,R54  ; test a-q AND 0x8000
    m_registers[17]->write(0x3836);

    //18  3f38  MOV R63,R56  ; branch to selected target
    m_registers[18]->write(0x3F38);

    //19  3928  MOV R57,R40  ; reset target for other branch to 21 (a zero result
    //                       ; from the subtraction now indicates q properly
    //                       ; divides p and so p is composite)
    m_registers[19]->write(0x3928);

    //20  0020  MOV R0 ,R32  ; p is prime: write it to the display
    m_registers[20]->write(0x0020);

    //21  3d20  MOV R61,R32  ; move p to adder
    m_registers[21]->write(0x3D20);

    //22  3c1e  MOV R60,R30  ; other summand=2
    m_registers[22]->write(0x3C1E);

    //23  3f29  MOV R63,R41  ; goto 4 to try new p
    m_registers[23]->write(0x3F29);

    //24  203d  MOV R32,R61  ; p+=2
    m_registers[24]->write(0x203D);

    //25                     ; unused
    //26                     ; unused
    //27                     ; unused
    //28                     ; unused
    //29                     ; unused

    //30  0002               ; constant 2
    m_registers[30]->write(0x2);

    //31  7fff               ; constant mask for sign bit testing
    m_registers[31]->write(0x7FFF);

    //32  0005               ; current candidate p
    m_registers[32]->write(0x0005);

    //33  0003               ; constant 3
    m_registers[33]->write(0x0003);

    //34  fffe               ; constant -1
    m_registers[34]->write(0xFFFE);

    //35  fffd               ; constant -2
    m_registers[35]->write(0xFFFD);

    //36  0014  20           ; branch target: trial divisor q equal to candidate p,
    //                       ; and hence prime found
    m_registers[36]->write(0x0014);

    //37  000d  13           ; branch target: trial divisor q less than candidate p
    m_registers[37]->write(0x000D);

    //38  0009   9           ; branch target: more subtractions to do
    m_registers[38]->write(0x0009);

    //39  0005   5           ; branch target: next trial divisor q
    m_registers[39]->write(0x0005);

    //40  0015  21           ; branch target: subtraction gave zero, so p composite
    m_registers[40]->write(0x0015);

    //41  0004   4           ; branch target: next candidate p
    m_registers[41]->write(0x0004);

    //42  fffc               ; constant -3  m_registers[1]->write(0x1E);
    m_registers[42]->write(0xFFFC);

    // Define start of software
    m_registers[63]->write(1);
#else // MY SIMPLE LOOP CODE
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
#endif // ORIGINAL_CODE
#endif
  }

  //----------------------------------------------------------------------------
  uint8_t wireworld_computer::decodeDestination(uint16_t p_instr)
  {
    return (0x3F00 & p_instr) >> 8;
  }

  //----------------------------------------------------------------------------
  uint8_t wireworld_computer::decodeSource(uint16_t p_instr)
  {
    return 0x3F & p_instr;
  }

  //----------------------------------------------------------------------------
  uint16_t wireworld_computer::getInstruction(void)
  {
    cout << "PC value :" ;
    uint16_t l_pc = m_registers[63]->read();
    cout << "=> PC = 0x" << hex << l_pc << dec << endl ;
    m_registers[63]->write(l_pc+1);
    return m_registers[l_pc]->read();
  }

  //----------------------------------------------------------------------------
  void wireworld_computer::execInstruction(uint16_t p_instr)
  {
    cout << "=> Instruction = 0x" << hex << p_instr << dec << endl ;
    uint16_t l_destination = decodeDestination(p_instr);
    uint16_t l_source = decodeSource(p_instr);
    cout << "=> MOV R" << l_destination << ", R" << l_source <<  endl ;
    cout << "R" << l_source << " => " ;
    uint16_t l_value = m_registers[l_source]->read();
    cout << "0x" << hex << l_value << dec << " => " ;
    cout << "R" << l_destination << endl ;
    m_registers[l_destination]->write(l_value);
  }

  //----------------------------------------------------------------------------
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

}
//EOF
