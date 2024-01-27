#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <cassert>

class DeclareMap
{
    struct Entry
    {
        int paramCount;
        bool defined;
    };

  public:
    std::unordered_map<std::string, DeclareMap::Entry> fmap;

    void validateCall(std::string name, int paramCount) {
        auto mapEntry = fmap.find(name);
        if(mapEntry == fmap.end()) {
            std::cerr << "Warning: no definition or declaration found for function " << name;
            return;
        }

        if(mapEntry->second.paramCount != paramCount) {
            std::cerr << "unmatched call for function " << name << std::endl;
            assert(false);
        }
    }
    void validateDeclaration(std::string name, int paramCount) {
        auto mapEntry = fmap.find(name);
        if(mapEntry == fmap.end()) return;

        if(mapEntry->second.paramCount == paramCount) return;

        std::cerr << "inconsistent declarations found for function " << name << std::endl;
        assert(false);
    }
    void validateDef(std::string name, int paramCount) {
        auto mapEntry = fmap.find(name);
        if(mapEntry == fmap.end()) return;

        if(mapEntry->second.paramCount != paramCount) {
            std::cerr << "inconsistent declarations found for function " << name << std::endl;
            assert(false);
        }

        if(mapEntry->second.defined) {
            std::cerr << "multiple definitions found for function " << name << std::endl;
            assert(false);
        }
    }
    void pushDeclaration(std::string name, int paramCount) {
        validateDeclaration(name, paramCount);
        fmap[name] = {paramCount, false};
    }
    void pushDef(std::string name, int paramCount) {
        validateDef(name, paramCount);
        fmap[name] = {paramCount, true};
    }
};