#include<stdio.h>
#include<stdbool.h>
#include<limits.h> //use for INT_MAX and INT_MIN 
#define v 9

void dijkstras(int graph[v][v],int src);
int min_distance(int a[],bool b[]);
void printSolution(int dist[],int src,int parent[]);

char places[9][100]  = {"Sarjapur","Kormangala","Bellandur","Manyatta","Banashankri","Indranagar","Jayanagar","Marathalli","Haralur"};
//finds and returns the index of the position storing min value so far
int min_distance(int dis[],bool dis_min[]){

    int min_index ,min_value =  INT_MAX;
    for(int i =0;i<v;i++){

        if(!dis_min[i] && dis[i]<=min_value)
            {
                min_index = i;
                min_value = dis[i];
            }
    }

    return min_index;
}
//recursive call to print the path form source
void printPath(int parent[],int j){

    if(j==-1)
        return ;
    printPath(parent,parent[j]);

    printf("%s%s", places[j],"->");

}
void printSolution(int dist[],int src,int parent[])
{
    
    printf("Places \t\t Distance from %s",places[src]);
    printf("\t\tTHE PATH IS -\n");
    for (int i = 0; i < v; i++)
        {
            if(i==src) continue;
            printf("%s \t\t %d\t\t", places[i], dist[i]);

            printPath(parent,i);
            printf("%s\n","You have reached");

        }
}

void dijkstra(int graph[v][v],int src){

    int dis[v];
    
    bool dis_min[v];

    int parent[v];
    
    for(int i = 0;i<v;i++){

        dis[i] = INT_MAX;
        dis_min[i] = false;
        parent[i] = src;
    }
    dis[src] = 0; //source is at distance 0
    parent[src] = -1;
    for(int i = 0 ;i<v-1;i++){

        int u = min_distance(dis,dis_min);

        dis_min[u] = true;

        
        for(int j=0;j<v;j++){

            if(graph[u][j] && !dis_min[j] && dis[u]!=INT_MAX && dis[u]+graph[u][j] <dis[j] ){

                dis[j] = dis[u] + graph[u][j];
                parent[j] = u;
            }
        }

        
    }

     printSolution(dis,src,parent);
}
int main(){
      int graph[v][v] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
  
    dijkstra(graph, 4);
  
    return 0;



    
}