#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <cassert>

class VariableMap
{
  private:
    std::unordered_map<std::string, int> vmap;
    int curIndex = -4;
  public:
    
    void push(std::string name) {
        if(vmap.find(name) != vmap.end()) {
            std::cerr << "duplicated variable declaration " << name << std::endl;
            assert(false);
        }

        vmap[name] = curIndex;
        curIndex -= 4;
    }
};