#pragma once
#include "PriorityQueue.h"

namespace UniformCostSearch {
    //require T to have setParent, setCostSoFar, and == operator
    template<typename T>
    void UCS(T* start, T* goal) {
        auto frontier = PriorityQueue<T, int>();
        frontier.put(start, 0);
        //start->setParent(nullptr);
        //start->setCostSoFar(0);

        while (!frontier.empty()) {
            T* current = frontier.get();
            if (current == goal) {
                break; // ASK: not calculating goal cost?
            }

            for (auto next : current->getNeighbors()) {
                if (next->isBlocked() || next == start || next == nullptr) continue;
                int new_cost = current->costSoFar() + next->cost();
                if (next->getParent() == nullptr || new_cost < next->costSoFar()) {
                    next->setCostSoFar(new_cost);
                    frontier.put(next, new_cost);
                    next->setParent(current);
                }
            }
        }
    }
}