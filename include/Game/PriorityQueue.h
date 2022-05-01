#pragma once

//taken from https://www.redblobgames.com/pathfinding/a-star/implementation.html#cpp-dijkstra

template<typename T, typename priority_t>
class PriorityQueue {
    typedef std::pair<priority_t, T*> PQElement;
public:

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T* item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T* get() {
        T* best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
private:
    std::priority_queue<PQElement, std::vector<PQElement>,
        std::greater<PQElement>> elements;
};