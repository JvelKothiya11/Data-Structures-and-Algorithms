#include <algorithm>
#include <utility>
#include <vector>

class Solution {
public:
    std::vector<int> countServers(int n, std::vector<std::vector<int>>& logs, int x, std::vector<int>& queries) {
        const int queryCount = static_cast<int>(queries.size());

        // Store each query with its original index.
        std::vector<std::pair<int, int>> sortedQueries;
        sortedQueries.reserve(queryCount);

        for (int i = 0; i < queryCount; ++i) {
            sortedQueries.emplace_back(queries[i], i);
        }

        std::sort(sortedQueries.begin(), sortedQueries.end());

        // Store logs as {timestamp, serverId}.
        std::vector<std::pair<int, int>> sortedLogs;
        sortedLogs.reserve(logs.size());

        for (const auto& log : logs) {
            sortedLogs.emplace_back(log[1], log[0]);
        }

        std::sort(sortedLogs.begin(), sortedLogs.end());

        std::vector<int> answer(queryCount, 0);
        std::vector<int> serverFrequency(n + 1, 0);

        int activeServers = 0;
        int left = 0;
        int right = 0;

        const int logCount = static_cast<int>(sortedLogs.size());

        for (const auto& [queryTime, originalIndex] : sortedQueries) {
            const int windowStart = queryTime - x;

            // Include logs with timestamp <= queryTime.
            while (right < logCount && sortedLogs[right].first <= queryTime) {
                const int serverId = sortedLogs[right].second;

                if (serverFrequency[serverId] == 0) {
                    ++activeServers;
                }

                ++serverFrequency[serverId];
                ++right;
            }

            // Exclude logs with timestamp < queryTime - x.
            while (left < right && sortedLogs[left].first < windowStart) {
                const int serverId = sortedLogs[left].second;

                --serverFrequency[serverId];

                if (serverFrequency[serverId] == 0) {
                    --activeServers;
                }

                ++left;
            }

            answer[originalIndex] = n - activeServers;
        }

        return answer;
    }
};