#include <cstdio>
#include <bits/stdc++.h> // 헤더파일 추가 설치.. 
using namespace std;

// 그래프 Class, 노드와 가중치 정보
class GRAPH {
public:
    int a, b, w;
};

// 우선순위 큐 Class
class PriorityQueue {
public:
    PriorityQueue();
    int n;
    GRAPH Arr[1000];
    GRAPH Delete();
    void Insert(GRAPH x);
    int isEmpty();
};

// 우선순위 큐 생성
PriorityQueue::PriorityQueue() { n = 0; } // 우선순위 큐 SIZE
int PriorityQueue::isEmpty() { return n==0; }

// 우선순위 큐 삽입 메소드 
void PriorityQueue::Insert(GRAPH graph) 
{
    Arr[n+1] = graph;
    int i;
    i = n+1; 
    n = n+1; // 우선순위 큐 SIZE 초기화 
    while (i>1 && Arr[i].w < Arr[i/2].w) {
        swap(Arr[i], Arr[i/2]); // 우선순위 큐 재배열 
        i = i/2;
    }
}

// 우선순위 큐 제거 메소드 
GRAPH PriorityQueue::Delete()
{
    GRAPH ret = Arr[1];
    if (n==1) {n=0; return ret;} 

    int i, j;
    Arr[1] = Arr[n];
    i = 1; n = n-1;
    while (1) {
        if (i*2 > n) { break;}
        else if (i*2+1 > n) {
            if (Arr[i*2].w < Arr[i].w) { swap(Arr[i*2],Arr[i]); i = i*2; }
            else { break; }
        }
        else {
            if (Arr[i].w > Arr[i*2].w && Arr[i].w > Arr[i*2+1].w) {
                if (Arr[i*2].w < Arr[i*2+1].w) { j = i*2; }
                else { j = i*2+1; }
                swap(Arr[i],Arr[j]);
                i = j;
            }
            else if (Arr[i].w > Arr[i*2].w && Arr[i].w <= Arr[i*2+1].w) {
                j = i*2; swap(Arr[i],Arr[j]); i = j;
            }
            else if (Arr[i].w <= Arr[i*2].w && Arr[i].w > Arr[i*2+1].w) {
                j = i*2+1; swap(Arr[i],Arr[j]); i = j;
            }
            else { break; }
        }
    }
    return ret;
}

// ============================ MAIN ============================

PriorityQueue PQ;
int n, m;
vector<pair<int, int>> Edges[1000];
int M[1000];

int main() {
    int c,i,a,b,w;
    GRAPH x,y;
    scanf("%d %d", &n, &m);
    for (i=0; i<m; i++) {
        scanf("%d %d %d", &a,&b,&w);
        Edges[a].push_back(make_pair(b,w));
        Edges[b].push_back(make_pair(a,w));
    }
    c = 1; M[c] = 1;
    for(i=0; i<Edges[c].size(); i++) {
        x.a = c; x.b = Edges[c][i].first; x.w = Edges[c][i].second; PQ.Insert(x);
    }
    while (PQ.isEmpty()==0) {
        y = PQ.Delete();
        if(M[y.a]==1 && M[y.b]==1) { continue; }
        else {
            printf("노드 %d - 노드 %d (가중치 %d) 선택. \n",y.a,y.b,y.w);
            c = y.b; M[c] = 1;
            for(i=0; i<Edges[c].size(); i++) {
                x.a = c; x.b = Edges[c][i].first; x.w = Edges[c][i].second; PQ.Insert(x);
            }
        }
    }
    return 0;
}


/*
5 10
1 2 10
2 3 1
1 5 6
1 4 5
2 4 4
2 4 3
4 5 2
3 4 9
3 5 4
5 3 6
*/