/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015년 11월 18일 15시 12분 58초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <string.h>

#define nmax 1024

using namespace std;

class Graph
{
  private:
    int **length;           // 이차원 배열
    int **a;           // 이차원 배열
    int *dist;              // 일차원 배열
    int *path;
    bool *s;                // 일차원 배열
    int n;                  // 정점의 수

  public: 

    Graph(const int n = 0) { 
      // 이차원 배열의 동적 생성
      length = new int*[n];        
      for(int i = 0; i < n; i++) 
        length[i] = new int [n];

      a = new int*[n];        
      for(int i = 0; i < n; i++) 
        a[i] = new int[n];

      for (int i = 0; i < n; i++) {
        path = new int[n];
      }

      // Allocation Max
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          length[j][i] = 0x7FFF;
        }
      }

      this->n = n;

      dist = new int[n];
      s = new bool[n];
    }; 

    int get_n_size(void) {
      return this->n;
    };

    void ShortestPath(const int);
    int choose(const int);
    int insert(int x, int y, int data);
    void print_array(void);
    void print_dist(void);
    int read_array_file(char *path, int x);

    /* Path */
    void AllLengths(const int n); 
    void print_a(int);
};

/* 
 * Insert array data
 */
int Graph::insert(int x, int y, int data) 
{
  length[x][y] = data;
  return data;
};

/*  
 * Print array
 */
void Graph::print_array(void) 
{
  int i, j, n = this->n;

  cout << "===== PRINT ===== \n";
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("%8d", length[i][j]);
    }
    cout << "\n";
  }
  cout << "===== PRINT ===== \n";

};

void Graph::print_a(int v) 
{
  int i, j, n = this->n;

  cout << "===== ALL PATH ===== \n";
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("%8d", a[i][j]);
    }
    cout << "\n";
  }

  cout << "===== PATH ===== \n";

  for (int i = 0; i < n; i++) {
    cout << i << "PATH : ";
    for (int j = i; j != 0; j = path[j])
      printf("<== %d ", j);

    printf("<== %d \n", v);
  }


};



/*
 * dist[j],0 ? j? n은 n개의 정점을 가진 방향 그래프 G에서 정점 v로부터 정점 j
 * 까지의 최단 경로 길이로 설정됨. 간선의 길이는 length[j][j]로 주어짐.
 */
void Graph::ShortestPath(const int v)
{
  int i = 0;

  // 초기화
  for (int i = 0; i < n; i++) {
    s[i] = false; 
    dist[i] = length[v][i];

     path[i] = v;
  }

  s[v] = true;
  dist[v] = 0;

  // 정점 v로부터 n-1개 경로를 결정
  for (i = 0; i < n-1; i++) {     

    // choose는 dist[u] = minimum dist[w]인 u를 반환
    int u = choose(n); 

    if (u < 0)
      return;

    s[u] = true;
    printf("Choose => %d distp[%d] = %d  == //", u, u, dist[u]);
    print_dist();

    for (int w = 0; w < n; w++) {
      if (!s[w]) {
        if (dist[u] + length[u][w] < dist[w]) {
          /* 더 빠른 경우! 업데이트 함! */
          dist[w] = dist[u] + length[u][w];

          // Add path arrray
          path[w] = u;
        }
      }
    }
  }

}; 

/*
 * Return min index
 */
int Graph::choose(const int n)
{
  int min = 0x7FFF;
  int ret = -1;
  int i = 0;

  if (n < 0)
    return -1;

  for (i = 0; i < n; i++) {
    if (dist[i] < min && s[i] == false && dist[i] != 999 && dist[i] != 0) {
      min = dist[i];
      ret = i;
      printf("tmp min : %d \n", dist[i]);
    }
  }

  return ret;
};

void Graph::print_dist(void)
{
  int i;

  for (i = 0; i < n; i++) {
    cout << dist[i] << " ";
  }

  cout << "\n";
};

int Graph::read_array_file(char *path, int x)
{
  FILE *fp;
  char buff[1024]; // 행이 1줄씩 임시로 저장될 버퍼
  int **array = NULL;

  array = this->length;

  if (path == NULL)
    return -1;

  /* Open */
  if ((fp = fopen(path, "rt")) == NULL) {
    fputs("Cannot open input file...\n", stderr);
    return -2;
  }

  /* Read */
  int j = 0;
  while (fgets(buff, 1024, fp) != NULL) {
    /* Line by line */
    printf("Read : %s \n", buff); 

    char *tmp = NULL;
    int i = 0;

    tmp = strtok(buff, " ");
    array[j][i] = atoi(tmp);
    for (int i = 1; i < x; i++) {
      tmp = strtok(NULL, " ");
      array[j][i] = atoi(tmp);
    }
    j++;
  }
}

// length[n][n]은 n개의 정점을 가진 그래프의 인접 행렬
// a[i][j]는 i와 j 사이의 최단 경로의 길이
void Graph::AllLengths(const int n)
{
  int i = 0, j = 0, k = 0;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      a[i][j] = length[i][j]; // length를 a에 복사

  // 제일 큰 정점의 인덱스가 k인 경로에 대해
  for (k = 0; k < n; k++)     
    // 가능한 모든 정점의 쌍에 대해
    for (i = 0; i < n; i++) 
      for (j = 0; j < n; j++)
        if ((a[i][k] + a[k][j]) < a[i][j])
          a[i][j] = a[i][k] + a[k][j];
}


int main(int argc, const char *argv[])
{
  int point = 0, line = 0, start_point = 0;
  int i = 0, j = 0;
  Graph *graph;

  /* Get Graph */
  cout << "Point : ";
  cin >> point;
  // cout << "Line : ";
  // cin >> line;
  graph = new Graph(point);

  graph->read_array_file("array.arr", graph->get_n_size());

  /*  
  // Input araay
  for (i = 0; i < line; i++) {
    int x, y, data;
    cin >> x >> y >> data;
    graph->insert(x, y, data);
    printf("array[%d][%d] : %d \n", x, y, data);
  }

  // Input start point
  cout << "Start point : ";
  cin >> start_point;
  if (start_point < 0 || graph->get_n_size() < start_point) {
    cout << "Start point error!";
    return -1;
  }
  */

  /* Run */
  graph->print_array();
  
  graph->ShortestPath(start_point);
  graph->print_dist();

  graph->AllLengths(graph->get_n_size());
  graph->print_a(start_point);
 
  /* End */
  cout << "END!! \n";
  return 0;
}

