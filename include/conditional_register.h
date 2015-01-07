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
