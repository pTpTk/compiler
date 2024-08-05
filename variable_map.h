#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <cassert>
#include <list>
#include <memory>
#include <vector>

class VariableMap
{
  private:
    int curIndex;
    std::unordered_map<std::string, int> vmap;

  public:
    VariableMap(int index = -4) : curIndex(index) {}

    void push(std::string name) {
        if(vmap.find(name) != vmap.end()) {
            std::cerr << "duplicated variable declaration " << name << std::endl;
            assert(false);
        }

        vmap[name] = curIndex;
        curIndex -= 4;
    }

    int lookup(std::string name) {
        auto iter = vmap.find(name);
        
        if(iter == vmap.end()) return 0;

        return iter->second;
    }

    int last() {
        return curIndex;
    }

    int size() {
        return vmap.size() << 2;
    }
};

class VariableStack
{
  private:
  public:
    std::list<std::shared_ptr<VariableMap>> prevMaps;
    std::shared_ptr<VariableMap> currMap;

    std::vector<std::string> params;

    void alloc() {
        if(currMap.get() != nullptr) {
            prevMaps.push_front(currMap);
            currMap = std::make_shared<VariableMap>(prevMaps.front()->last());
        }
        else {
            currMap = std::make_shared<VariableMap>();
        }
    }

    void dealloc() {
        assert(currMap.get() != nullptr);
        if(prevMaps.front().get() != nullptr) {
            currMap = prevMaps.front();
            prevMaps.pop_front();
        }
        else {
            currMap.reset();
        }
    }

    void push(std::string name) {
        if(lookupParams(name) != -1) {
            std::cerr << "duplicated variable declaration " << name << std::endl;
            assert(false);
        }

        assert(currMap);
        currMap->push(name);
    }

    void pushFuncParams(std::vector<std::string>& _params) {
        assert(_params.size() < 5);

        params = _params;
    }

    int lookupParams(std::string name) {
        int i = 0;

        for(auto p : params) {
            if(name == p) {
                return i;
            }
            i++;
        }

        return -1;
    }

    int lookup(std::string name) {
        int size = 0;
        int ret;

        ret = currMap->lookup(name);
        if(ret != 0)
            return ret;

        for(auto vmap : prevMaps) {
            ret = vmap->lookup(name);
            if (ret != 0) break;
        }

        if(ret == 0) {
            std::cerr << "undeclared variable " << name << std::endl;
            assert(false);
        }

        return ret;
    }

    int size() {
        assert(currMap.get());
        return currMap->size();
    }

    bool first() {
        return currMap.get() && prevMaps.empty();
    }
};