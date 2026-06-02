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

char* codeName(enum IRRemoteCode code) {
    char* key = malloc(8 * sizeof(char));
    switch (code) {
        case IR1:     return strcpy(key, "IR1");
        case IR2:     return strcpy(key, "IR2");
        case IR3:     return strcpy(key, "IR3");
        case IR4:     return strcpy(key, "IR4");
        case IR5:     return strcpy(key, "IR5");
        case IR6:     return strcpy(key, "IR6");
        case IR7:     return strcpy(key, "IR7");
        case IR8:     return strcpy(key, "IR8");
        case IR9:     return strcpy(key, "IR9");
        case IR0:     return strcpy(key, "IR0");
        case IRstar:  return strcpy(key, "IRstar");
        case IRhash:  return strcpy(key, "IRhash");
        case IRup:    return strcpy(key, "IRup");
        case IRdown:  return strcpy(key, "IRdown");
        case IRleft:  return strcpy(key, "IRleft");
        case IRright: return strcpy(key, "IRright");
        case IRok:    return strcpy(key, "IRok");
        default:      return strcpy(key, "UNKNOWN");
    }
}

#endif // IR_REMOTE_CODES_H