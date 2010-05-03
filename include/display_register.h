#ifndef __DISPLAY_REGISTRE_H__
#define __DISPLAY_REGISTRE_H__

#include "register.h"

#include <iostream>

class display_registre: public registre
{
 public:
  inline display_registre(void);
  inline uint16_t read(void)const;
  inline void write(uint16_t p_value);
 private:
  uint16_t m_value;
};

display_registre::display_registre(void):
  m_value(0)
{
}

uint16_t display_registre::read(void)const
{
  return 0;
}

void display_registre::write(uint16_t p_value)
{
  m_value = p_value;
  std::cout << "-----------------------------------" << std::endl ;
  std::cout << "** DISPLAY => " << m_value << std::endl ;
  std::cout << "-----------------------------------" << std::endl ;
}

#endif //__DISPLAY_REGISTRE_H__
