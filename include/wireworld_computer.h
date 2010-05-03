#ifndef __WIREWORLD_COMPUTER_H__
#define __WIREWORLD_COMPUTER_H__

#include "register.h"

class wireworld_computer
{
 public:
  wireworld_computer(void);
  void run(void);
 private:
  uint8_t decodeDestination(uint16_t p_instr);
  uint8_t decodeSource(uint16_t p_instr);
  uint16_t getInstruction(void);
  void execInstruction(uint16_t p_instr);
  registre* m_registers[64];
};

#endif //__WIREWORLD_COMPUTER_H__
