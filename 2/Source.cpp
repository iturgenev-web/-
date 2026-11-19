#include <cstdio>
#include <cstdlib>
#include <locale.h>
#include <vector>
#include <queue>
#include <chrono>
using namespace std;

#define REPEATS 10

typedef vector<vector<int>> Graph;

// Матрица смежности n x n, p — вероятность ребра в процентах
Graph generateGraph(int n, int p) {
    Graph g(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (rand() % 100 < p)
                g[i][j] = g[j][i] = 1;
    return g;
}
//Собственная очередь на односвязном списке
struct Node {
    int value;
    Node* next;
};

struct ListQueue {
    Node* first = nullptr;
    Node* last = nullptr;

    ~ListQueue() { while (first) pop(); }

    bool empty() const { return first == nullptr; }
    int front() const { return first->value; }

    void push(int value) {
        Node* node = new Node{ value, nullptr };
        if (last) last->next = node;
        else      first = node;
        last = node;
    }

    void pop() {
        Node* old = first;
        first = old->next;
        if (!first) last = nullptr;
        delete old;
    }
};
// Один BFS для обеих очередей 
template <class Queue>
vector<int> bfs(const Graph& g) {
    int n = g.size();
    vector<int> order, visited(n, 0);
    order.reserve(n);
    Queue q;

    for (int s = 0; s < n; s++) {
        if (visited[s]) continue;
        visited[s] = 1;
        q.push(s);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            order.push_back(cur);
            for (int v = 0; v < n; v++) {
                if (g[cur][v] && !visited[v]) {
                    visited[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return order;
}

// Время одного запуска BFS в миллисекундах
template <class Queue>
double timeBfs(const Graph& g) {
    auto start = chrono::steady_clock::now();
    volatile size_t sink = bfs<Queue>(g).size();   // чтобы компилятор не выкинул вызов 
    (void)sink;
    return chrono::duration<double, milli>(chrono::steady_clock::now() - start).count();
}

int main() {
    const int p = 10;   

    setlocale(LC_ALL, "");
    srand(42);

    printf("Сравнение BFS для матрицы смежности: queue и собственная очередь на списке\n");
    printf("Вероятность ребра: %d%%, повторений: %d\n\n", p, REPEATS);
    printf("%-10s%-20s%s\n", "N", "queue (ms)", "ListQueue (ms)");

    for (int n : { 100, 500, 1000, 2000 }) {
        Graph g = generateGraph(n, p);
        double totalS = 0.0, totalL = 0.0;

        for (int r = 0; r < REPEATS; r++) {
            totalS += timeBfs<queue<int>>(g);
            totalL += timeBfs<ListQueue>(g);
        }

        printf("%-10d%-20.4f%.4f\n", n, totalS / REPEATS, totalL / REPEATS);
    }

    printf("\nВремя в миллисекундах (среднее за %d запусков).\n", REPEATS);
    return 0;
}