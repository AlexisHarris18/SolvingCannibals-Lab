#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

template<typename T>
class Graph {
public:
    Graph() {}

    void addVertex(T vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = vector<T>();
            vertices.push_back(vertex);
        }
    }

    void addEdge(T source, T target) {
        if (adjList.find(source) != adjList.end()) {
            adjList[source].push_back(target);
        }
    }

    int getVertexPos(T vertex) {
        for (size_t i = 0; i < vertices.size(); i++) {
            if (vertices[i] == vertex)
                return static_cast<int>(i);
        }
        return -1;
    }

    int getNumVertices() {
        return static_cast<int>(vertices.size());
    }

    bool isEdge(T src, T dest) {
        if (adjList.find(src) != adjList.end()) {
            for (T neighbor : adjList[src]) {
                if (neighbor == dest) return true;
            }
        }
        return false;
    }

    vector<T> getPath(T source, T target) {
        unordered_map<T, T> cameFrom;
        unordered_set<T> visited;
        queue<T> q;
        vector<T> path;

        q.push(source);
        visited.insert(source);

        while (!q.empty()) {
            T current = q.front(); q.pop();
            if (current == target)
                break;

            for (T neighbor : adjList[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    cameFrom[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        if (cameFrom.find(target) == cameFrom.end()) {
            return path; // No path found
        }

        for (T at = target; at != source; at = cameFrom[at]) {
            path.push_back(at);
        }
        path.push_back(source);
        reverse(path.begin(), path.end());
        return path;
    }

    friend ostream& operator<<(ostream& out, const Graph<T>& g) {
        for (auto& vertex : g.vertices) {
            out << vertex << ": ";
            for (T neighbor : g.adjList.at(vertex)) {
                out << neighbor << ", ";
            }
            out << endl;
        }
        return out;
    }

private:
    vector<T> vertices;
    unordered_map<T, vector<T>> adjList;
};
