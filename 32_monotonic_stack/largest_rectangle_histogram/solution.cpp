#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        const int size = static_cast<int>(heights.size());

        std::stack<int> indices;
        int maximumArea = 0;

        for (int index = 0; index <= size; ++index) {
            const int currentHeight = (index == size) ? 0 : heights[index];

            while (!indices.empty() && currentHeight < heights[indices.top()]) {
                const int height = heights[indices.top()];
                indices.pop();
                const int width = indices.empty() ? index : index - indices.top() - 1;
                maximumArea = std::max(maximumArea, height * width);
            }

            indices.push(index);
        }

        return maximumArea;
    }
};