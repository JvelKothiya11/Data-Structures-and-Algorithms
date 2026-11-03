#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<int> findSubstring(const std::string& s, const std::vector<std::string>& words) {
        std::vector<int> result;

        if (s.empty() || words.empty()) {
            return result;
        }

        const int stringLength = static_cast<int>(s.size());
        const int wordCount = static_cast<int>(words.size());
        const int wordLength = static_cast<int>(words[0].size());

        if (wordLength == 0 || stringLength < wordCount * wordLength) {
            return result;
        }

        std::unordered_map<std::string, int> requiredFrequency;

        for (const std::string& word : words) {
            ++requiredFrequency[word];
        }

        for (int offset = 0; offset < wordLength; ++offset) {
            int left = offset;
            int right = offset;
            int matchedWords = 0;

            std::unordered_map<std::string, int> windowFrequency;

            while (right + wordLength <= stringLength) {
                const std::string currentWord = s.substr(right, wordLength);
                right += wordLength;

                // Reset the window when an invalid word is encountered.
                if (requiredFrequency.find(currentWord) == requiredFrequency.end()) {
                    windowFrequency.clear();
                    matchedWords = 0;
                    left = right;
                    continue;
                }

                ++windowFrequency[currentWord];
                ++matchedWords;

                // Remove excess occurrences of the current word.
                while (windowFrequency[currentWord] > requiredFrequency.at(currentWord)) {
                    const std::string leftWord = s.substr(left, wordLength);
                    --windowFrequency[leftWord];
                    --matchedWords;
                    left += wordLength;
                }

                // A complete concatenation has been found.
                if (matchedWords == wordCount) {
                    result.push_back(left);
                    const std::string leftWord = s.substr(left, wordLength);
                    --windowFrequency[leftWord];
                    --matchedWords;
                    left += wordLength;
                }
            }
        }

        return result;
    }
};