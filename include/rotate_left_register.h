#ifndef __ROTATE_LEFT_REGISTRE_H__
#define __ROTATE_LEFT_REGISTRE_H__

#include "register.h"

class rotate_left_registre: public registre
{
 public:
  inline rotate_left_registre(void);
  inline uint16_t read(void)const;
  inline void write(uint16_t p_value);
 private:
  uint16_t m_value;
};

rotate_left_registre::rotate_left_registre(void):
  m_value(0)
{
}

uint16_t rotate_left_registre::read(void)const
{
  return m_value << 1;
}

void rotate_left_registre::write(uint16_t p_value)
{
  m_value = p_value;
}

#endif //__ROTATE_LEFT_REGISTRE_H__
