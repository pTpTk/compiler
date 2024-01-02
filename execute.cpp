#include "execute.h"

void
Execute::run(std::vector<std::shared_ptr<Instruction>>& insts) {
    for(auto& inst : insts) {
        switch(inst->op) {
            case Opcode::nop:
            case Opcode::tag:
                break;
            case Opcode::movl:
            {
                EAX = std::dynamic_pointer_cast<Movl>(inst)->imm;
                break;
            }
            case Opcode::ret:
            {
                frame = EAX;
                break;
            }
            default:
                assert(false);
        }
    }
}