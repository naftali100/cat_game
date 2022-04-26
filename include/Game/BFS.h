#pragma once
#ifndef BFS_H
#define BFS_H

#include <algorithm>
#include <queue>
#include "Hex.h"


//TODO: replace this row after changing to template
typedef Hex Vertex;


/*
BFS requires:
init all vertexes to white
setColor()
setParent()
isVisited()
//TODO: change isVisited to if color == white
*/
namespace BFS
{
    //template<typename Vertex>
    //assume it is initalised
    void search(Vertex* root, const Vertex* goal)
    {
        std::queue<Vertex*> q;
        root->setColor(GRAY);
        root->setParent(nullptr);
        q.push(root);
        while (!q.empty())
        {
            Vertex* v = q.pop();
            for (Vertex* neighbor : v.getNeighbors())
            {
                if (!neighbor->isVisited())
                {
                    neighbor->setColor(GRAY);
                    neighbor->setParent(v);
                    q.push(neighbor);
                    if (neighbor == goal) return;
                }
            }
            v->setColor(BLACK);
        }
    }
} // namespace BFS
//TODO: ask Matan: we need to do iteratable object or so?
//do we need to do all in one function?

#endif