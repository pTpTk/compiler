#include "assembler.h"

void
Assembler::run(Program& prog) {
    for(auto function : prog.functions)
        function->assemble(output);
}