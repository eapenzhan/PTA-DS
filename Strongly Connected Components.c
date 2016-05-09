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

int ** AddMat(int** mat, int **matA, int ** matB, int n) {
  // int ** mat = calloc(sizeof(int) * n * n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      mat[i][j] = matA[i][j] || matB[i][j];
    }
  }
  return mat;
}

int ** MulMat(int**mat, int **matA, int ** matB, int count) {
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
  return mat;
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

  set[rootb] = roota;
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ) {
  const int numVer = G->NumOfVertices;
  int ** mat = calloc(G->NumOfVertices * G->NumOfVertices, sizeof(int));
  if (mat == NULL) {
    return;
  }

  for(int i = 0; i < G->NumOfVertices; i++) {
    PtrToVNode node = G->Array + i;
    // node = node->Next;
    while (node) {
      mat[i][node->Vert] = 1;
      node = node->Next;
    }
  }

  int ** multi = calloc(numVer * numVer, sizeof(int));
  memcpy(multi, mat, sizeof(int) * numVer * numVer);
  int ** result = calloc(1, sizeof(multi));

  for (int i = 0; i < numVer; i++) {
    AddMat(mat, MulMat(result, mat, multi, numVer), mat, numVer);
  }

  free(multi);
  free(result);
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
  }
  free(mat);
}
