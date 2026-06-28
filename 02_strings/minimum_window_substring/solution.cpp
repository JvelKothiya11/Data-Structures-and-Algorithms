#include <string>
#include <vector>
#include <climits>

class Solution {
public:
    std::string minWindow(const std::string& s, const std::string& t) {
        if (t.size() > s.size()) {
            return "";
        }
        std::vector<int> frequency(128, 0);

        for (char ch : t) {
            ++frequency[ch];
        }

        int remaining = static_cast<int>(t.size());
        int windowStart = 0;
        int bestStart = 0;
        int minimumLength = INT_MAX;

        for (int windowEnd = 0; windowEnd < static_cast<int>(s.size()); ++windowEnd) {
            const char rightChar = s[windowEnd];
            if (frequency[rightChar] > 0) {
                --remaining;
            }
            --frequency[rightChar];

            while (remaining == 0) {
                const int currentLength = windowEnd - windowStart + 1;
                if (currentLength < minimumLength) {
                    minimumLength = currentLength;
                    bestStart = windowStart;
                }
                const char leftChar = s[windowStart];
                ++frequency[leftChar];

                if (frequency[leftChar] > 0) {
                    ++remaining;
                }
                ++windowStart;
            }
        }

        return minimumLength == INT_MAX ? "" : s.substr(bestStart, minimumLength);
    }
};