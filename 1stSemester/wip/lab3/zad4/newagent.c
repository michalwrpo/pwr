// Zadanie 4, newagent.c Michał Waluś

#include "agents.h"

struct agent newagent(int x, int y) {
    struct agent new_agent;
    new_agent.x = x;
    new_agent.y = y;
    return new_agent;
}
