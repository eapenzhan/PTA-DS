typedef enum { true, false, maybe } Keys;
typedef Keys ElementType;

void swap(ElementType * a, ElementType* b){
  ElementType temp = *a;
  *a = *b;
  *b = temp;
}

void MySort( ElementType A[], int N ){
  int i,j;
  if (N == 1) {
    return;
  }
  int start = 0;
  for ( i = 0 ,j = N - 1; i < j;) {
    while (i < j && A[i] == false) i++;
    while (i < j && A[j] == true) j--;
    if (i == j) {
      break;
    }
    if (A[i] == A[j]) {
      start = i + 1 < start ? start : i + 1;
      while (start < j && A[start] == maybe) {
        start++;
      }
      if(start == j)break;
      if (A[start] == false) {
        swap(A + i, A + start);
      } else swap (A + start, A + j);
    } else {
      swap(A + i, A + j);
    }
  }
}
