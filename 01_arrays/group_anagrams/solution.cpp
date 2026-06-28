#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> anagramGroups;
        anagramGroups.reserve(strs.size());

        for (const std::string& word : strs) {
            std::string signature = word;
            std::sort(signature.begin(), signature.end());
            anagramGroups[signature].push_back(word);
        }

        std::vector<std::vector<std::string>> result;
        result.reserve(anagramGroups.size());

        for (auto& [_, group] : anagramGroups) {
            result.push_back(std::move(group));
        }

        return result;
    }
};