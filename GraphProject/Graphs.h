#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <stack>
#include <unordered_map>
#include <climits>
#include <string>
#include <fstream>
#include <list>
#include <chrono>

using namespace std;


class Graph {
public:
    int numVertices;
    unordered_map <int, string> intmap;
    unordered_map <string, int> stringmap;
    vector<vector<int>> adjList;
    Graph() {
        numVertices = 25000;
        adjList.resize(numVertices);
        mapMaker();
    }

    void mapMaker() {
        string name;
        fstream inFile;
        inFile.open("C:/GraphProject/random_names_fossbytes.csv");
        srand(time(NULL));
        if (inFile.is_open()) {
            for (int i = 0; i < 25000; i++) {
                getline(inFile, name);
                stringmap.insert({ (name), i });
                intmap.insert({ i, (name) });
            }
        }
        int count = 0;
        for (auto place = stringmap.begin(); place != stringmap.end(); ++place) {
            ++count;
            int mult = count / 5000;
            int x = rand() % 10;
            for (int j = 0; j < x; j++) {
                int y = 0;
                if (mult == 0) {
                    y = rand() % 10000;
                }//so will this
                else if (mult == 1) {
                    y = rand() % 15000;
                }
                else if (mult == 2) {
                    y = rand() % 1500 + 5000;
                }
                else if (mult == 3) {
                    y = rand() % 10000 + 10000;
                }
                else if (mult == 4) {
                    y = rand() % 15000 + 10000;
                }
                else {
                    y = rand() % 10000 + 15000;
                }
                adjList[place->second].push_back(y);
            }
        }
    }

    vector<string> BFSSearch(int src, int destination, bool connected) {
        vector<int> path;
        vector<string> bfsFriends;
        if(!connected){
            cout << "NO CONNECTION FOUND" << endl;
            auto str = intmap[src];
            bfsFriends = BFSNoConnection(str);
            return bfsFriends;
        }
        else{
            cout << "connection found!" << endl;
            path = BFSPathfinder(src,destination);
            cout << "BFS: " << path.size()<<endl;
            bfsFriends = storePath(path);
            return bfsFriends;
        }
    }

    vector<string> DFSSearch(int src, int destination, bool connected) {
        vector<string> dfsFriends;
        vector<int> path;
        vector<bool> visited;
        if(!connected){
            cout << "NO CONNECTION FOUND" << endl;
            auto str = intmap[src];
            dfsFriends = DFSNoConnection(str);
            return dfsFriends;
        }else{
            cout << "connection found!" << endl;
            DFSPathfinder(src,destination,visited,path);
            cout << "DFS: " << path.size()<<endl;
            dfsFriends = storePath(path);
            return dfsFriends;
        }
    }

    vector<string> BFSNoConnection(const string& source) {
        int pos = stringmap[source];
        vector<string> bfsFriends;
        set<int> visited;
        queue<int> q;
        visited.insert(pos);
        q.push(pos);
        int n = 0;
        while (!q.empty()) {
            int curr = q.front();
            auto p = intmap.find(curr);
            int position = p->first;
            if (n > 0 && n < 10) {
                bfsFriends.push_back(p->second);
            }
            n++;
            q.pop();
            vector<int> neighbors = adjList.at(position);
            sort(neighbors.begin(), neighbors.begin() + neighbors.size());
            for (int v: neighbors) {
                if (visited.count(v) == 0) {
                    visited.insert(v);
                    q.push(v);
                }
            }
            if(bfsFriends.size()==9)
                break;
        }
        return bfsFriends;
    }

    vector<string> DFSNoConnection(const string& source) {
        int pos = stringmap[source];
        vector<string> dfsFriends;
        set<int> visited;
        stack<int> stack;
        visited.insert(pos);
        stack.push(pos);
        int n = 0;
        while (!stack.empty()) {
            int curr = stack.top();
            auto p = intmap.find(curr);
            int position = p->first;
            if (n > 0 && n < 10) {
                dfsFriends.push_back(p->second);
            }
            n++;
            stack.pop();
            vector<int> neighbors = adjList.at(position);
            for (int v: neighbors) {
                if (visited.count(v) == 0) {
                    visited.insert(v);
                    stack.push(v);
                }
            }
            if(dfsFriends.size()==9)
                break;
        }
        return dfsFriends;
    }

    bool dfsBool(int src, int dest) {
        set<int> visited;
        stack<int> s;
        visited.insert(src);
        s.push(src);
        while (!s.empty()) {
            int u = s.top();
            s.pop();
            for (auto v: adjList[u]) {
                if (v == dest) {
                    return true;
                }
                if ((visited.find(v) == visited.end())) {
                    visited.insert(v);
                    s.push(v);
                }
            }
        }
        return false;
    }

    bool bfsBool(int src, int dest) {
        set<int> visited;
        queue<int> q;
        visited.insert(src);
        q.push(src);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v: adjList[u]) {
                if (v == dest) {
                    return true;
                }
                if ((visited.find(v) == visited.end())) {
                    visited.insert(v);
                    q.push(v);
                }
            }
        }
        return false;
    }

    bool DFSPathfinder(int src, int dest, vector<bool> &visited, vector<int> &path){
        // mark the current node as discovered
        visited.resize(25000);
        visited[src] = true;
        // include the current node in the path
        path.push_back(src);
        // if destination vertex is found
        if (src == dest) {
            return true;
        }
        // do for every edge (src, i)
        for (int i: adjList[src]){
            // if `u` is not yet visited
            if (!visited[i]){
                // return true if the destination is found
                if (DFSPathfinder(i, dest, visited, path)) {
                    return true;
                }
            }
        }
        // backtrack: remove the current node from the path
        path.pop_back();
        // return false if destination vertex is not reachable from src
        return false;
    }


    vector<int> BFSPathfinder(int & src,int & dest) {
        set<int> visited;
        string temp;
        vector<int> distance(25000, INT_MAX);
        vector<int> path;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;
        priorityQueue.push({distance[src] = 0, src});
        while (!priorityQueue.empty()) {
            int i = priorityQueue.top().second;
            long long d = priorityQueue.top().first;
            priorityQueue.pop();
            if (distance[i] < d)continue;
            for (auto j : adjList[i]) {
                if ((distance[j] > distance[i] + 1) && visited.count(j)==0) {
                    distance[j] = distance[i] + 1;
                    priorityQueue.push({distance[j], j});
                    visited.insert(j);
                    path.push_back(j);
                    if(j==dest){
                        return path;
                    }
                }
            }
        }
        return path;
    }

    vector<string> storePath(vector<int> const &path){
        vector<string> shortestPath;
        string temp;
        int stop = 0;
        int factor = (path.size())/9;
        for (int i = 0; i < path.size()-1; i++) {
            if(stop < 9) {
                if(i% factor == 0 && i!=0) {
                    temp = intmap[path.at(i)];
                    shortestPath.push_back(temp);
                    stop++;
                }
            }
        }
        return shortestPath;
    }

    void printCompletePath(vector<int> const &path){
        int counter=0;
        string temp;
        for (int i : path) {
            if (counter==5){
                cout << endl;
                counter=0;
            }
            temp = intmap[i];
            cout << temp << "-> ";
            counter++;
        }
        cout<< "Done!"<<endl;
        cout<< "It took " + to_string((path.size()-1)) +" Connections To Link The People You Searched!"<<endl;
    }

};
