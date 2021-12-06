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
            if(bfsFriends.size() == 9) 
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

    bool dfsBool(int src, int dest) { //explores all vertices from a source using Depth First Search Traversal to check if there is a connection to destination
        set<int> visited; 
        stack<int> s;
        visited.insert(src); //marks as discovered
        s.push(src);
        while (!s.empty()) {
            int u = s.top(); //gets next node to explore from queue
            s.pop();
            for (auto v: adjList[u]) { //checks every edge from vertex u
                if (v == dest) { //if destination vertex is found, return true
                    return true;
                }
                if ((visited.find(v) == visited.end())) { //if vertex is not visited, push in stack and mark in visited
                    visited.insert(v);
                    s.push(v);
                }
            }
        }
        return false;
    }

    bool bfsBool(int src, int dest) { //explores all vertices from a source using Breadth First Search Traversal to check if there is a connection to destination
        set<int> visited;
        queue<int> q;
        visited.insert(src); //marks as discovered
        q.push(src);
        while (!q.empty()) {
            int u = q.front(); //gets next node to explore from queue
            q.pop();
            for (auto v: adjList[u]) { //checks every edge from vertex u
                if (v == dest) { //if destination vertex is found, return true
                    return true;
                }
                if ((visited.find(v) == visited.end())) { //if vertex is not visited, push in queue and mark in visited
                    visited.insert(v);
                    q.push(v);
                }
            }
        }
        return false;
    }

    bool DFSPathfinder(int src, int dest, vector<bool> &visited, vector<int> &path){
        visited.resize(25000); 
        visited[src] = true; //mark vertex as visited
        path.push_back(src); //include current vertex in path
        if (src == dest) { //if destination vertex is found, return true
            return true;
        }
        for (int i: adjList[src]){ //checks every edge
            if (!visited[i]){
                if (DFSPathfinder(i, dest, visited, path)) {//if destination is found, return true
                    return true;
                }
            }
        }
        path.pop_back(); //removing current node frm path to backtrack due to recursion
        return false; //if destinatin is not reachable
    }


    vector<int> BFSPathfinder(int & src,int & dest) { //NEEDS UPDATE BY NICK - I tried
        set<int> visited; //stores the nodes that have already been visited in bfs traversal
        string temp;
        vector<int> distance(25000, INT_MAX); //vector of distances between two nodes
        vector<int> path;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue; //gets minimum distance between source and destination
        priorityQueue.push({distance[src] = 0, src});
        while (!priorityQueue.empty()) {
            int i = priorityQueue.top().second;
            long long d = priorityQueue.top().first;
            priorityQueue.pop();
            if (distance[i] < d)continue; //if distance to the second value in pair is less than distance to first value in the pair, continue loop
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
        vector<string> shortestPath; //store all the nodes of path from source to destination
        string temp;
        int stop = 0;
        int factor = (path.size())/9; //will traverse evenly through the path to produce only 9 nodes
        for (int i = 0; i < path.size()-1; i++) {
            if(stop < 9) { //will stop after 9 nodes
                if(i% factor == 0 && i!=0) {
                    temp = intmap[path.at(i)];//converting int to string name
                    shortestPath.push_back(temp); //pushing name into shortestpath
                    stop++;
                }
            }
        }
        return shortestPath;
    }

    void printCompletePath(vector<int> const &path){ //determines how many connections between source and destination and prints all nodes between
        int counter = 0;
        string temp;
        for (int i : path) {
            if (counter==5){ // prints five name a line
                cout << endl;
                counter=0;
            }
            temp = intmap[i]; //converts int to string name 
            cout << temp << "-> ";
            counter++;
        }
        cout<< "Done!"<<endl;
        cout<< "It took " + to_string((path.size()-1)) + " Connections To Link The People You Searched!"<<endl;
    }

};
