#pragma once

#include <string>

class LabelPair
{
  public:
    std::string first;
    std::string second;

    void clear() {
        first.clear();
        second.clear();
    }

    void set(std::string l1, std::string l2) {
        first = l1;
        second = l2;
    }

    bool empty() { return first.empty(); }
};