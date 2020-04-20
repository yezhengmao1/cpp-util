#ifndef KMP_SEARCH_H_
#define KMP_SEARCH_H_

#include <vector>
#include <cassert>

std::vector<std::size_t> KmpTable(const char *substr) {
    std::vector<std::size_t> table(2, 0);
    std::size_t k = 0;
    for(std::size_t i = 1; substr[i] != '\0'; ++i) {
        while(k > 0 && substr[i] != substr[k]) {
            k = table[k];
        }
        substr[i] == substr[k] ? ++k : k;
        table.push_back(k);
    }
    return table;
}

std::vector<std::size_t> KmpSearch(const char* str, const char* substr) {
    assert(substr != nullptr);
    assert(substr[0] != '\0');

    std::vector<std::size_t> table = KmpTable(substr);
    std::vector<std::size_t> ret;
    std::size_t len = table.size() - 1;
    std::size_t k = 0;

    for(std::size_t i = 0; str[i] != '\0'; ++i) {
        while(k > 0 && str[i] != substr[k]) {
            k = table[k];
        }
        str[i] == substr[k] ? ++k : k;
        if(k == len) {
            ret.push_back(i + 1 - len);
        }
    }

    return ret;
}

#endif
