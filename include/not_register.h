#ifndef __NOT_REGISTRE_H__
#define __NOT_REGISTRE_H__

#include "register.h"

class not_registre: public registre
{
 public:
  inline not_registre(void);
  inline uint16_t read(void)const;
  inline void write(uint16_t p_value);
 private:
  uint16_t m_value;
};

not_registre::not_registre(void):
  m_value(0)
{
}

uint16_t not_registre::read(void)const
{
  return ~ m_value;
}

void not_registre::write(uint16_t p_value)
{
  m_value = p_value;
}

#endif //__NOT_REGISTRE_H__
