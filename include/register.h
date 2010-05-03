#ifndef __REGISTRE_H__
#define __REGISTRE_H__

#include <stdint.h>

class registre
{
 public:
  virtual uint16_t read(void)const=0;
  virtual void write(uint16_t p_value)=0;
  virtual ~registre(void){};
};

#endif //__REGISTRE_H__
