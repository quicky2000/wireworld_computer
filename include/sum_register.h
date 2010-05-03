#ifndef __SUM_REGISTRE_H__
#define __SUM_REGISTRE_H__

#include "simple_register.h"
#include "assert.h"


class sum_registre: public registre
{
 public:
  inline sum_registre(const registre * const p_operand_registre);
  inline uint16_t read(void)const;
  inline void write(uint16_t p_value);
 private:
  const registre * const m_operand_registre;
  simple_registre m_registre;
};

sum_registre::sum_registre(const registre * const p_operand_registre):
  m_operand_registre(p_operand_registre)
{
  assert(p_operand_registre);
}

uint16_t sum_registre::read(void)const
{
  uint16_t l_op1 = m_registre.read();
  uint16_t l_op2 = m_operand_registre->read();
  uint32_t l_op1_32 = m_registre.read();
  uint32_t l_op2_32 = m_operand_registre->read();
  uint16_t l_sum16 = l_op1+l_op2;
  return l_sum16 + (((l_op1_32+l_op2_32)>l_sum16 || l_sum16 == 0xFFFF) ? 1 : 0);
}

void sum_registre::write(uint16_t p_value)
{
  return m_registre.write(p_value);
}

#endif //__SUM_REGISTRE_H__
