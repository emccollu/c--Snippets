#include <vector>
#include <time.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
using namespace std;

void slowsort(vector<int> &a, int left, int right){
  if (left < right){
    int center = (left+right)/2;
    slowsort(a, left, center);
    slowsort(a, center+1, right);
    if (a[center]>a[right]){
      swap(a[center], a[right]); //Replaces center with right
    }
    slowsort(a,left,right-1);
  }
};

int main() {
  int n;
  n=200;
  vector<int> a(n);
  for (int i=0; i<a.size(); i++){
    a[i] = 1 + (int) (1000 * (sin (1.2 * i) * sin (1.2*i)));
  }
  slowsort(a, 0, n);
  return 0;
}
