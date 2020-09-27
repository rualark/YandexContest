#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

struct Vertex {
  char key=0;
  list<Vertex*> neigh;
  bool visited = false;
  int d = 0;
  int f = 0;
  Vertex* pred = nullptr;
};

void dfs(vector<Vertex>& graph) {
  int stage = 0;
  for (auto& v : graph) {
    v.visited = false;
  }
  stack<Vertex*> S;
  for (auto& s : graph) {
    if (!s.key) continue;
    if (s.visited) continue;
    S.push(&s);
    while (!S.empty()) {
      auto *v = S.top();
      bool hasUnvisitedChildren = false;
      if (!v->visited) {
        v->visited = true;
        for (auto& c : v->neigh) {
          if (!c->visited) {
            hasUnvisitedChildren = true;
            S.push(c);
          }
        }
        if (!v->d) {
          stage++;
          v->d = stage;
        }
      }
      if (!hasUnvisitedChildren) {
        S.pop();
        if (!v->f) {
          stage++;
          v->f = stage;
        }
      }
    }
  }
}

vector<Vertex> create() {
  vector<Vertex> graph(127);
  for (auto ch = 'q'; ch <= 'z'; ++ch) {
    graph[ch].key = ch;
  }
  graph['q'].neigh = { &graph['w'], &graph['t'], &graph['s'] };
  graph['r'].neigh = { &graph['y'], &graph['u'] };
  graph['s'].neigh = { &graph['v'] };
  graph['t'].neigh = { &graph['y'], &graph['x'] };
  graph['u'].neigh = { &graph['y'] };
  graph['v'].neigh = { &graph['w'] };
  graph['w'].neigh = { &graph['s'] };
  graph['x'].neigh = { &graph['z'] };
  graph['y'].neigh = { &graph['q'] };
  graph['z'].neigh = { &graph['x'] };
  return graph;
}

int main() {
  auto graph = create();
  dfs(graph);
  for (const auto& v : graph) {
    if (!v.key) continue;
    cout << v.key << " " << v.d << " " << v.f << endl;
  }
}
