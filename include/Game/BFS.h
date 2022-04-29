#pragma once
#ifndef BFS_H
#define BFS_H

#include <algorithm>
#include <queue>
#include "Hex.h"
#include "Log.h"


//TODO: replace this row after changing to template
//typedef Hex Vertex;


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
    template<typename Vertex>
    //assume it is initalised
    void search(Vertex* root, const Vertex* goal)
    {
        bool earlyExit = false;
        std::queue<Vertex*> q;
        root->setInProgress();
        root->setParent(nullptr);
        q.push(root);
        while (!q.empty())
        {
            Vertex* v = q.front();
            q.pop();
            for (Vertex* neighbor : v->getNeighbors())
            {
                if (!neighbor->isVisited() && !neighbor->isBlocked())
                {
                    neighbor->setInProgress();
                    neighbor->setParent(v);
                    q.push(neighbor);
                    if (neighbor == goal) 
                        earlyExit = true;
                }
            }
            if(earlyExit)
                return;
            v->setDone();
        }
    }
} // namespace BFS

#endif