#include <functional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

class Solution {
public:
    std::vector<int> assignTasks(std::vector<int>& servers, std::vector<int>& tasks) {
        using ServerInfo = std::pair<int, int>;
        using BusyServer = std::tuple<long long, int, int>;

        // Ordered by server weight, then server index.
        std::priority_queue<ServerInfo, std::vector<ServerInfo>, std::greater<ServerInfo>> idleServers;

        // Ordered by free time, then server weight, then server index.
        std::priority_queue<BusyServer, std::vector<BusyServer>, std::greater<BusyServer>> busyServers;

        for (int i = 0; i < static_cast<int>(servers.size()); ++i) {
            idleServers.emplace(servers[i], i);
        }

        const int taskCount = static_cast<int>(tasks.size());
        std::vector<int> assignment(taskCount);

        for (int taskIndex = 0; taskIndex < taskCount; ++taskIndex) {
            const long long currentTime = taskIndex;

            // Move all servers that have become available into the idle heap.
            while (!busyServers.empty() && std::get<0>(busyServers.top()) <= currentTime) {
                const auto [freeTime, weight, serverIndex] = busyServers.top();
                busyServers.pop();

                idleServers.emplace(weight, serverIndex);
            }

            if (!idleServers.empty()) {
                // Assign the task to the best available server.
                const auto [weight, serverIndex] = idleServers.top();
                idleServers.pop();

                assignment[taskIndex] = serverIndex;

                busyServers.emplace(currentTime + tasks[taskIndex], weight, serverIndex);
            } else {
                // No server is idle: use the server that becomes free earliest.
                const auto [freeTime, weight, serverIndex] = busyServers.top();
                busyServers.pop();

                assignment[taskIndex] = serverIndex;

                busyServers.emplace(freeTime + tasks[taskIndex], weight, serverIndex);
            }
        }

        return assignment;
    }
};