#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

struct Vertex {
  char key = 0;
  list<Vertex*> neigh;
  char color = 'w';
  int d = 0;
  int f = 0;
  Vertex* pred = nullptr;
};

void dfs(vector<Vertex>& graph) {
  int stage = 0;
  for (auto& v : graph) {
    v.color = 'w';
  }
  stack<pair<Vertex*, Vertex*>> S;
  for (auto& s : graph) {
    if (!s.key) continue;
    if (s.color != 'w') continue;
    S.emplace(nullptr, &s);
    while (!S.empty()) {
      Vertex *p = S.top().first;
      Vertex *v = S.top().second;
      bool hasUnvisitedChildren = false;
      if (v->color == 'w') {
        if (p) cout << "Tree edge: " << p->key << "-" << v->key << endl;
        v->pred = p;
        v->color = 'g';
        for (auto& c : v->neigh) {
          if (c->color == 'w') {
            hasUnvisitedChildren = true;
            S.emplace(v, c);
          }
          else if (c->color == 'g') {
            cout << "Back edge: " << v->key << "-" << c->key << endl;
          }
          else if (c->color == 'b') {
            if (stage <= c->f) {
              cout << "Forward edge: " << v->key << "-" << c->key << " (" << stage+1 << "<" << c->f << ")" << endl;
            } else {
              cout << "Cross edge: " << v->key << "-" << c->key << " (" << stage + 1 << ">" << c->f << ")" << endl;
            }
          }
        }
        if (!v->d) {
          stage++;
          v->d = stage;
        }
      }
      else if (v->color == 'g') {
        if (p && !v->d) cout << "Back edge: " << p->key << "-" << v->key << endl;
      }
      else if (v->color == 'b') {
        if (p) cout << "Forward edge: " << p->key << "-" << v->key << endl;
      }
      if (!hasUnvisitedChildren) {
        S.pop();
        if (v->color != 'b') {
          stage++;
          v->f = stage;
          v->color = 'b';
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
