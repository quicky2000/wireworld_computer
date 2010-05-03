#ifndef __ROTATE_RIGHT_REGISTRE_H__
#define __ROTATE_RIGHT_REGISTRE_H__

#include "register.h"

class rotate_right_registre: public registre
{
 public:
  inline rotate_right_registre(void);
  inline uint16_t read(void)const;
  inline void write(uint16_t p_value);
 private:
  uint16_t m_value;
};

rotate_right_registre::rotate_right_registre(void):
  m_value(0)
{
}

uint16_t rotate_right_registre::read(void)const
{
  return m_value >> 1;
}

void rotate_right_registre::write(uint16_t p_value)
{
  m_value = p_value;
}

#endif //__ROTATE_RIGHT_REGISTRE_H__
