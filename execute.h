#pragma once

#include <vector>
#include <memory>
#include <cassert>

#include "asm.h"

class Execute
{
  private:
    long EAX;
    long frame;
  public:
    void run(std::vector<std::shared_ptr<Instruction>>&);
};