#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50
#include <locale.h>
// Узел списка смежности
typedef struct Node {
    int v;
    struct Node *next;
} Node;

// Граф в виде массива списков смежности
typedef struct {
    int n;
    Node *adj[MAX];
} Graph;

// Генерация случайного неориентированного графа без петель
 void generate(int n, double p, int a[MAX][MAX])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (rand() % 101 < p)
                a[i][j] = a[j][i] = 1;
}

// Вывод матрицы смежности
void print_matrix(int n, int a[MAX][MAX])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d", a[i][j]);
            putchar('\n');
    }
}

// Построение списков смежности по матрице смежности
void build_lists(Graph *g, int n, int a[MAX][MAX])
{
    g->n = n;

    for (int i = 0; i < MAX; i++)
        g->adj[i] = NULL;

    for (int i = 0; i < n; i++)
        for (int j = n - 1; j >= 0; j--)   // обратный обход даёт возрастающий порядок
            if (a[i][j]) {
                Node *p = (Node*)malloc(sizeof(*p));
                if (!p) {
                    printf("Ошибка: недостаточно памяти.");
                    exit(1);
                }
                p->v = j;
                p->next = g->adj[i];
                g->adj[i] = p;
            }
}

void free_lists(Graph *g)
{
    for (int i = 0; i < g->n; i++) {
        Node *p = g->adj[i];
        while (p) {
            Node *next = p->next;
            free(p);
            p = next;
        }
        g->adj[i] = NULL;
    }
}
void print_lists(const Graph *g)
{
    for (int i = 0; i < g->n; i++) {
        printf("%d: ", i + 1);
        for (const Node *p = g->adj[i]; p; p = p->next)
            printf("%d ", p->v + 1);
            putchar('\n');
    }
}
int apply_unary(int *n, int a[MAX][MAX], int op, int u, int v,const int moved[MAX])
{
    static int b[MAX][MAX];
    int old = *n;

    u--;

    if (u < 0 || u >= old)
        return 0;

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            b[i][j] = 0;

    if (op == 1 || op == 2) {
        v--;

        if (v < 0 || v >= old || u == v)
            return 0;

        /// Стягивать можно только существующее ребро. 
        if (op == 2 && !a[u][v])
            return 0;

        int keep = (u < v) ? u : v;   // вершина, в которую происходит слияние 
        int drop = (u < v) ? v : u;   // вершина, которая удаляется 
        int index[MAX];
        int next = 0;

        // Новая нумерация вершин: keep и drop получают общий номер. 
        for (int i = 0; i < old; i++) {
            if (i == drop)
                index[i] = index[keep];
            else
                index[i] = next++;
        }

        for (int i = 0; i < old; i++)
            for (int j = 0; j < old; j++) {
                if (i == drop || j == drop)
                    continue;
                b[index[i]][index[j]] = a[i][j];
            }

        // При слиянии соседи обеих вершин объединяются. 
        for (int w = 0; w < old; w++) {
            if (w == drop || w == keep)
                continue;
            int linked = a[keep][w] || a[drop][w];
            b[index[keep]][index[w]] = linked;
            b[index[w]][index[keep]] = linked;
        }

        int new_n = old - 1;

        // Петли в простом графе не допускаются
        for (int i = 0; i < new_n; i++)
            b[i][i] = 0;

        for (int i = 0; i < new_n; i++)
            for (int j = 0; j < new_n; j++)
                a[i][j] = b[i][j];

        *n = new_n;
        return 1;
    }

    if (op == 3) {
        int count = 0;

        if (old >= MAX)
            return 0;

        // Переносить можно только соседей вершины u, и хотя бы один должен быть выбран
        for (int w = 0; w < old; w++) {
            if (!moved[w])
                continue;
            if (w == u || !a[u][w])
                return 0;
            count++;
        }

        if (count == 0)
            return 0;

        for (int i = 0; i < old; i++)
            for (int j = 0; j < old; j++)
                b[i][j] = a[i][j];

        for (int w = 0; w < old; w++)
            if (moved[w]) {
                b[u][w] = b[w][u] = 0;      // ребро убираем у старой вершины 
                b[old][w] = b[w][old] = 1;  // и добавляем у новой 
            }

        b[old][old] = 0;

        for (int i = 0; i <= old; i++)
            for (int j = 0; j <= old; j++)
                a[i][j] = b[i][j];

        *n = old + 1;
        return 1;
    }

    return 0;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    int a[MAX][MAX];
    int n, op, u = 0, v = 0, k = 0;
    int moved[MAX] = {0};
    double p;
    Graph g;

    srand((unsigned)time(NULL));

    printf("Введите количество вершин и вероятность появления ребра в процентах: ");
    if (scanf("%d %lf", &n, &p) != 2)
        return 1;


    generate(n, p, a);

    puts("\nИсходная матрица смежности:");
    print_matrix(n, a);

    build_lists(&g, n, a);
    puts("\nИсходные списки смежности:");
    print_lists(&g);
    free_lists(&g);

    printf("\nВыберите операцию:");
    printf("  1 — отождествление двух вершин");
    printf("  2 — стягивание ребра");
    printf("  3 — расщепление вершины");
    printf("\nНомер операции: ");
    if (scanf("%d", &op) != 1)
        return 1;

    if (op == 1 || op == 2) {
        printf("Введите две вершины (нумерация с 1): ");
        if (scanf("%d %d", &u, &v) != 2)
            return 1;
    } else if (op == 3) {
        printf("Введите расщепляемую вершину: ");
        if (scanf("%d", &u) != 1)
            return 1;

        printf("Введите количество соседей для переноса: ");
        if (scanf("%d", &k) != 1)
            return 1;

        if (k < 1 || k > n - 1) {
            puts("Ошибка: недопустимое количество соседей.");
            return 1;
        }

        printf("Введите номера соседей (нумерация с 1): ");
        for (int i = 0; i < k; i++) {
            int x;
            if (scanf("%d", &x) != 1)
                return 1;
            if (x < 1 || x > n) {
                puts("Ошибка: недопустимый номер вершины.");
                return 1;
            }
            moved[x - 1] = 1;
        }
    } else {
        puts("Ошибка: неизвестная операция.");
        return 1;
    }

    if (!apply_unary(&n, a, op, u, v, moved)) {
        puts("Операция невозможна.");
        puts("При стягивании вершины должны быть смежны,"
             " при расщеплении нужно выбрать только соседей вершины.");
        return 1;
    }

    printf("\nРезультат в виде матрицы смежности:\n");
    print_matrix(n, a);

    build_lists(&g, n, a);
    printf("\nРезультат в виде списков смежности:\n");
    print_lists(&g);
    free_lists(&g);

    return 0;
}
