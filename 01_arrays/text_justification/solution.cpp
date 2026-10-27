#include <string>
#include <vector>

class Solution {
public:
    std::vector<std::string> fullJustify(const std::vector<std::string>& words, int maxWidth) {
        const int wordCount = static_cast<int>(words.size());
        std::vector<std::string> result;

        int index = 0;

        while (index < wordCount) {
            const int lineStart = index;
            int totalWordChars = 0;

            while (index < wordCount) {
                const int wordLength = static_cast<int>(words[index].size());
                const int wordsOnLine = index - lineStart;
                const int requiredWidth = totalWordChars + wordLength + wordsOnLine;

                if (requiredWidth > maxWidth) {
                    break;
                }

                totalWordChars += wordLength;
                ++index;
            }

            const int wordsOnLine = index - lineStart;
            const int gaps = wordsOnLine - 1;
            const bool isLastLine = index == wordCount;

            std::string line;
            line.reserve(static_cast<std::size_t>(maxWidth));

            if (isLastLine || gaps == 0) {
                for (int i = lineStart; i < index; ++i) {
                    if (i > lineStart) {
                        line += ' ';
                    }
                    line += words[i];
                }

                line.append(static_cast<std::size_t>(maxWidth) - line.size(), ' ');
            } else {
                const int totalSpaces = maxWidth - totalWordChars;
                const int baseSpaces = totalSpaces / gaps;
                const int extraSpaces = totalSpaces % gaps;

                for (int i = lineStart; i < index - 1; ++i) {
                    line += words[i];

                    const int spaces = baseSpaces + (i - lineStart < extraSpaces ? 1 : 0);
                    line.append(static_cast<std::size_t>(spaces), ' ');
                }

                line += words[index - 1];
            }

            result.push_back(std::move(line));
        }

        return result;
    }
};