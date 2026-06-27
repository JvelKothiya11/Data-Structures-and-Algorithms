#include <string>

class Solution {
public:
    std::string removeOccurrences(std::string s, const std::string& part) {
        std::string result;

        for (char ch : s) {
            result.push_back(ch);
            
            if (result.size() >= part.size() && result.compare(result.size() - part.size(), part.size(), part) == 0) {
                result.resize(result.size() - part.size());
            }
        }

        return result;
    }
};