typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReverseGraph(Graph G) {
    Graph g = (Graph)malloc(sizeof(struct GNode));
    (*g).NumOfVertices = (*G).NumOfVertices;
    (*g).NumOfEdges = (*G).NumOfEdges;
    (*g).Array = (PtrToVNode *)calloc(1, sizeof(PtrToVNode) * G->NumOfVertices);

    int count = G->NumOfVertices;
    for (int i = 0; i < count; i++) {
        PtrToVNode node = G->Array[i];
        while (node) {
            int ver = node->Vert;
            PtrToVNode now = (PtrToVNode)malloc(sizeof(struct VNode));
            now->Vert = i;
            now->Next = g->Array[ver];
            g->Array[ver] = now;
            node= node->Next;
        }
    }

    return g;
}

int stack[MaxVertices];
int visited[MaxVertices];
int k;

void DFS(Graph G, int node, void (*func)(int node)){
    visited[node]= 1;
    PtrToVNode vnode = G->Array[node];
    while (vnode) {
        if (!visited[vnode->Vert]) {
            DFS(G, vnode->Vert, func);
        }
        vnode = vnode->Next;
    }

    func(node);
}

void push(int node) {
    stack[k++] = node;
}

// void PrintV(int node)
// {
//    printf("%d ", node);
// }

void SCC(Graph g, void (*visit)(Vertex V)) {
    memset(visited, 0, sizeof(visited));

    while(k > 0) {
        if (visited[stack[--k]]) {
            continue;
        }
        DFS(g, stack[k], visit);
        printf("\n");
    }
}



void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ) {
    memset(visited, 0, sizeof(visited));
    Graph g = ReverseGraph(G);
    for(int i = 0; i < G->NumOfVertices; i++) {
        if (!visited[i]) {
            DFS(g, i, push);
        }
    }
    SCC(G, visit);
}
