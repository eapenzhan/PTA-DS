//
//  main.cpp
//  Strongly Connected Components
//
//  Created by john on 5/9/16.
//  Copyright © 2016 lezhu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
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

void AddMat(int(*mat)[MaxVertices], int (*matA)[MaxVertices], int (*matB)[MaxVertices], int n) {
    // int ** mat = calloc(sizeof(int) * n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = matA[i][j] || matB[i][j];
        }
    }
}

void MulMat(int (*mat)[MaxVertices], int (*matA)[MaxVertices], int (*matB)[MaxVertices], int count) {
    // int ** mat = calloc(sizeof(int) * count * count);
    int i,j;
    for (i = 0; i < count; i++) {
        int temp;
        for (j = 0; j < count; j++) {
            temp = 0;
            for (int k = 0; k < count; k++) {
                temp = matA[i][k] && matB[k][j];
                if (temp) {
                    break;
                }
            }
            mat[i][j] = temp;
        }
    }
}

Vertex FindRoot(Vertex ver, Vertex * set) {
    if (set[ver] == -1) {
        return ver;
    }
    Vertex root = FindRoot(set[ver], set);
    return set[ver] = root;
}

void Merge(Vertex vera, Vertex verb, Vertex * set) {
    Vertex roota = FindRoot(vera, set);
    Vertex rootb = FindRoot(verb, set);
    
    if(roota != rootb)set[rootb] = roota;
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ) {
    const int numVer = G->NumOfVertices;
    int mat[MaxVertices][MaxVertices];
    memset(mat, 0, sizeof(mat));
    for(int i = 0; i < G->NumOfVertices; i++) {
        PtrToVNode node = *(G->Array + i);
//         node = node->Next;
        while (node) {
            mat[i][node->Vert] = 1;
            node = node->Next;
        }
    }
    
    int multi[MaxVertices][MaxVertices];
    memcpy(multi, mat, sizeof(int) * MaxVertices * MaxVertices);
    int result[MaxVertices][MaxVertices];
    int multier[MaxVertices][MaxVertices];
    memcpy(multier, mat, sizeof(mat));
    
    for (int i = 0; i < numVer; i++) {
        MulMat(result, multier, multi, numVer);
        AddMat(mat, result ,mat, numVer);
        memcpy(multier, result, sizeof(mat));
    }
    
    Vertex set[MaxVertices];
    memset(set, -1, sizeof(set));
    for (int i = 0; i < numVer; i++) {
        for (int j = i; j < numVer; j++) {
            if (mat[i][j] && mat[j][i]) {
                Merge(i, j, set);
            }
        }
    }
    
    for (int i = 0; i < numVer; i++) {
        FindRoot(i, set);
    }
    int q[MaxVertices];
    memset(q, 0, sizeof(q));
    for (int i = 0; i < numVer; i++) {
        int j;
        if (set[i] != -1) {
            j = set[i];
            mat[j][q[j]] = i;
            q[j]++;
        } else {
            j = i;
            mat[j][q[j]] = i;
            q[j]++;
        }
    }
    for (int i = 0; i < numVer; i++) {
        for (int j = 0; j < q[i]; j++) {
            visit(mat[i][j]);
        }
        if(q[i])printf("\n");
    }
}

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
    printf("%d ", V);
}

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

Graph ReadG() {
    Graph g = (Graph)malloc(sizeof(struct GNode));
    scanf("%d%d", &((*g).NumOfVertices), &(g->NumOfEdges));
    g->Array = (PtrToVNode *)malloc(g->NumOfVertices * sizeof(PtrToVNode));
    for (int i = 0; i < g->NumOfVertices; i++) {
        ((g->Array)[i]) = (PtrToVNode)malloc(sizeof(struct VNode));
        g->Array[i]->Next = NULL;
    }
    for (int i = 0; i < g->NumOfEdges; i++) {
        int a,b;
        scanf("%d%d", &a, &b);
        PtrToVNode v = (PtrToVNode)malloc(sizeof(struct VNode));
        v->Vert = b;
        PtrToVNode * array = (*g).Array;
        v->Next = (array[a])->Next;
        (array[a])->Next = v;
    }
    
    return g;
}
