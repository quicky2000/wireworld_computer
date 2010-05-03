#ifndef __RETURN_ZERO_REGISTRE_H__
#define __RETURN_ZERO_REGISTRE_H__

#include "register.h"

#include <iostream>

class return_zero_registre: public registre
{
  friend class conditional_registre;
 public:
  inline return_zero_registre(void);
  inline uint16_t read(void)const;
  inline void write(uint16_t p_value);
 private:
  uint16_t m_value;
};

return_zero_registre::return_zero_registre(void):
  m_value(0)
{
}

uint16_t return_zero_registre::read(void)const
{
  return 0;
}

void return_zero_registre::write(uint16_t p_value)
{
  m_value = p_value;
}

#endif //__RETURN_ZERO_REGISTRE_H__
