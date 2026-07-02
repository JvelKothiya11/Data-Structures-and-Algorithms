#include <string>

class Solution {
private:
    static int valueOf(char symbol) {
        switch (symbol) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default:  return 0;
        }
    }

public:
    int romanToInt(const std::string& s) {
        const int size = static_cast<int>(s.size());
        int result = 0;

        for (int index = 0; index < size; ++index) {
            const int currentValue = valueOf(s[index]);
            const int nextValue = (index + 1 < size) ? valueOf(s[index + 1]) : 0;
            
            if (currentValue < nextValue) {
                result -= currentValue;
            } else {
                result += currentValue;
            }
        }

        return result;
    }
};