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
#ifndef __BITWISE_AND_NOT_REGISTRE_H__
#define __BITWISE_AND_NOT_REGISTRE_H__

#include "register.h"
#include "assert.h"

class bitwise_and_not_registre: public registre
{
 public:
  inline bitwise_and_not_registre(simple_registre * const p_registre1, const simple_registre  * const p_registre2);
  inline uint16_t read(void)const;
  inline void write(uint16_t p_value);
 private:
  simple_registre * const m_reg1;
  const simple_registre * const m_reg2;
};

bitwise_and_not_registre::bitwise_and_not_registre(simple_registre * const p_registre1, const simple_registre  * const p_registre2):
  m_reg1(p_registre1),
  m_reg2(p_registre2)
{
  assert(p_registre1);
  assert(p_registre2);
}

uint16_t bitwise_and_not_registre::read(void)const
{
  return ~(m_reg1->read()) & (m_reg2->read());
}

void bitwise_and_not_registre::write(uint16_t p_value)
{
  m_reg1->write(p_value);
}


#endif //__BITWISE_AND_NOT_REGISTRE_H__
