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

#define nmax 1024

using namespace std;

class Graph
{
  private:
    int **length;           // 이차원 배열
    int *dist;              // 일차원 배열
    bool *s;                // 일차원 배열
    int n;                  // 정점의 수

  public: 

    Graph(const int n = 0) { 
      // 이차원 배열의 동적 생성
      length = new int*[n];        
      for(int i = 0; i < n; i++) 
        length[i] = new int [n];

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

    void ShortestPath(const int);
    int choose(const int);
    int insert(int x, int y, int data);
    void print_array(void);
    void print_dist(void);
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
  }
 
  s[v] = true;
  dist[v] = 0;

  // 정점 v로부터 n-1개 경로를 결정
  for (i = 0; i < n-1; i++) {     
  
    // choose는 dist[u] = minimum dist[w]인 u를 반환
    int u = choose(n); 
    s[u] = true;

    for (int w = 0; w < n; w++) {
      if (!s[w]) {
        if (dist[u] + length[u][w] < dist[w]) {
          dist[w] = dist[u] + length[u][w];
        }
      }
    }
  }
  
}; 

int Graph::choose(const int n)
{
  int min = 0x7FFF;
  int min_index = 0;
  int i = 0;

  if (n < 0)
    return -1;

  for (i = 0; i < n; i++) {
    if (dist[i] < min && s[i] == false) {
      min = dist[i];
      min_index = i;
    }
  }

  return min_index;
}

void Graph::print_dist(void)
{
  int i;

  for (i = 0; i < n; i++) {
    cout << dist[i] << " ";
  }

  cout << "\n";

}


int main(int argc, const char *argv[])
{
  int point = 0, line = 0;
  int i = 0, j = 0;
  Graph *graph;

  /* Get Graph */
  cout << "Point : ";
  cin >> point;
  cout << "Line : ";
  cin >> line;
  graph = new Graph(point);

  /* Insert araay */
  for (i = 0; i < line; i++) {
    int x, y, data;
    cin >> x >> y >> data;
    graph->insert(x, y, data);
    printf("array[%d][%d] : %d \n", x, y, data);
  }

  printf("End Insert \n");

  /* ===== RUN ===== */
  graph->print_array();
  graph->ShortestPath(0);
  graph->print_dist();

  /* End */
  cout << "END!! \n";
  return 0;
}

