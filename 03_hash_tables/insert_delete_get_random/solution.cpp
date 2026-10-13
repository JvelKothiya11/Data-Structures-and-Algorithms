#include <cstdlib>
#include <stdexcept>
#include <unordered_map>
#include <vector>

class RandomizedSet {
public:
    RandomizedSet() = default;

    bool insert(int val) {
        if (valueToIndex.contains(val)) {
            return false;
        }

        valueToIndex[val] = static_cast<int>(values.size());
        values.push_back(val);
        return true;
    }

    bool remove(int val) {
        const auto it = valueToIndex.find(val);
        if (it == valueToIndex.end()) {
            return false;
        }

        const int indexToRemove = it->second;
        const int lastValue = values.back();

        // Move the last element into the removed element's position.
        values[indexToRemove] = lastValue;
        valueToIndex[lastValue] = indexToRemove;

        values.pop_back();
        valueToIndex.erase(it);

        return true;
    }

    int getRandom() {
        if (values.empty()) {
            throw std::out_of_range("RandomizedSet is empty");
        }

        return values[static_cast<std::size_t>(std::rand()) % values.size()];
    }

private:
    std::unordered_map<int, int> valueToIndex;
    std::vector<int> values;
};