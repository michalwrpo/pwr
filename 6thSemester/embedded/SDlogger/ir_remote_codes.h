#ifndef IR_REMOTE_CODES_H
#define IR_REMOTE_CODES_H

#include "string_helper.h"

enum IRRemoteCode {
    IR1 = 0x45,
    IR2 = 0x46,
    IR3 = 0x47,
    IR4 = 0x44,
    IR5 = 0x40,
    IR6 = 0x43,
    IR7 = 0x7,
    IR8 = 0x15,
    IR9 = 0x9,
    IRstar = 0x16,
    IR0 = 0x19,
    IRhash = 0xD,
    IRup = 0x18,
    IRleft = 0x8,
    IRok = 0x1C,
    IRright = 0x5A,
    IRdown = 0x52,
};

#endif // IR_REMOTE_CODES_H