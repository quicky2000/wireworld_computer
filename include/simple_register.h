#ifndef __SIMPLE_REGISTRE_H__
#define __SIMPLE_REGISTRE_H__

#include "register.h"

class simple_registre: public registre
{
 public:
  inline simple_registre(void);
  inline uint16_t read(void)const;
  inline void write(uint16_t p_value);
 private:
  uint16_t m_value;
};

simple_registre::simple_registre(void):
  m_value(0)
{
}

uint16_t simple_registre::read(void)const
{
  return m_value;
}

void simple_registre::write(uint16_t p_value)
{
  m_value = p_value;
}

#endif //__SIMPLE_REGISTRE_H__
