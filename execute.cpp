#include "execute.h"

void
Execute::run(std::vector<std::shared_ptr<Instruction>>& insts) {
    for(auto& inst : insts) {
        switch(inst->op) {
            case Opcode::Nop:
            case Opcode::Tag:
                break;
            case Opcode::Movl:
            {
                EAX = std::dynamic_pointer_cast<Movl>(inst)->imm;
                break;
            }
            case Opcode::Ret:
            {
                frame = EAX;
                break;
            }
            default:
                assert(false);
        }
    }
}