#pragma once

#include <vector>
#include <string>
#include <memory>

#include "util.h"
#include "token.h"
#include "asm.h"
#include "variable_map.h"
#include "declare_map.h"
#include "label.h"
#include "ast_function.h"
#include "ast_statement.h"
#include "ast_expression.h"

class Program
{
  public:
    std::vector<std::shared_ptr<Function>> functions;
    VariableStack vmap;
    LabelPair labelPair;
    DeclareMap fmap;
};