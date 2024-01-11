#include "assembler.h"

void
Assembler::run(Program& prog) {
    prog.function->assemble(output);
}