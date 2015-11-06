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
#include "wireworld_computer.h"

#include <cstdlib>
#include <iostream>

using namespace std;

int main(void)
{
  typedef wireworld_computer::register_information t_reg_info;
  typedef wireworld_computer::wireworld_computer::t_register_informations t_reg_infos;
  t_reg_infos l_register_informations;

  wireworld_computer::wireworld_computer l_computer(l_register_informations);
  l_computer.run();
  return 0;
}
