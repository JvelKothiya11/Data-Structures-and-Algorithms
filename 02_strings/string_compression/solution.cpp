#include <vector>
#include <string>

class Solution {
public:
    int compress(std::vector<char>& chars) {
        const int size = static_cast<int>(chars.size());

        int read = 0;
        int write = 0;

        while (read < size) {
            const char current = chars[read];
            const int groupStart = read;

            while (read < size && chars[read] == current) {
                ++read;
            }

            const int count = read - groupStart;

            chars[write++] = current;

            if (count > 1) {
                const std::string frequency = std::to_string(count);
                for (char digit : frequency) {
                    chars[write++] = digit;
                }
            }
        }

        return write;
    }
};