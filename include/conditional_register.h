#ifndef __CONDITIONAL_REGISTRE_H__
#define __CONDITIONAL_REGISTRE_H__

#include "simple_register.h"
#include "return_zero_register.h"
#include "assert.h"

#include <iostream>

class conditional_registre: public registre
{
 public:
  inline conditional_registre(const return_zero_registre * const p_registre1, const return_zero_registre  * const p_registre2);
  inline uint16_t read(void)const;
  inline void write(uint16_t p_value);
 private:
  const return_zero_registre * const m_reg1;
  const return_zero_registre * const m_reg2;
  simple_registre m_registre;
};

conditional_registre::conditional_registre(const return_zero_registre * const p_registre1, const return_zero_registre  * const p_registre2):
  m_reg1(p_registre1),
  m_reg2(p_registre2)
{
  assert(p_registre1);
  assert(p_registre2);
}

uint16_t conditional_registre::read(void)const
{
  return m_registre.read() ? m_reg1->m_value : m_reg2->m_value  ;
}

void conditional_registre::write(uint16_t p_value)
{
  return m_registre.write(p_value);
}

#endif //__CONDITIONAL_REGISTRE_H__
