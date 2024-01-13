#pragma once

#include <vector>
#include <string>
#include <memory>

#include "token.h"
#include "asm.h"
#include "variable_map.h"
#include "ast_function.h"
#include "ast_statement.h"
#include "ast_expression.h"

class Program
{
  public:
    std::shared_ptr<Function> function;
};