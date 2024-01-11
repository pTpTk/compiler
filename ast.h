#pragma once

#include <vector>
#include <string>
#include <memory>

#include "token.h"
#include "ast_function.h"

class Program
{
  public:
    std::shared_ptr<Function> function;
};