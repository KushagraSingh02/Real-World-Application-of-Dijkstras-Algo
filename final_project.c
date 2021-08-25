//Application of Dijkstra in real world
#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h> //use for INT_MAX and INT_MIN 
#define v 9

void dijkstras(int graph[v][v],int src);
int min_distance(int a[],bool b[]);
void printSolution(int dist[],int src,int parent[]);
void destination();

int graph[v][v] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    int dis[v];
    
    bool dis_min[v];

    int parent[v];
struct route{
char places[100] ;
int hospital;
int cinema;
int restaurant;
};

struct route rt[9]= {{"Sarjapur",1,0,1},{"Kormangala",1,1,1},{"Bellandur",0,1,1},{"Manyatta",1,1,1},{"Banashankri",1,1,1},{"Indranagar",0,0,1},{"Jayanagar",0,1,1},{"Marathalli",1,0,1},{"Haralur",0,1,0}};
int min_distance(int dis[],bool dis_min[])
{

    int min_index ,min_value =  INT_MAX;
    for(int i =0;i<v;i++)
    {

        if(!dis_min[i] && dis[i]<=min_value)//not of () is to skip the calculation in reverse path
            {
                min_index = i;
                min_value = dis[i];
            }
    }
    return min_index;
}
//recursive call to print the path form source
void printPath(int parent[],int j)
{

    if(j==-1)
        return ;
    printPath(parent,parent[j]);

    printf("%s%s", rt[j].places,"->");

}
void printSolution(int dist[],int src,int parent[])
{
    
    printf("Places \t\t Distance from %s",rt[src].places);
    printf("\t\tTHE PATH IS -\n");
    for (int i = 0; i < v; i++)
        {
            if(i==src) continue;
            printf("%s \t\t %d\t\t", rt[i].places, dist[i]);

            printPath(parent,i);
            printf("%s\n","You have reached");

        }
}

void dijkstra(int graph[v][v],int src)
{

   
    
    for(int i = 0;i<v;i++)
    {

        dis[i] = INT_MAX;
        dis_min[i] = false;
        parent[i] = src;
    }
    dis[src] = 0; //source is at distance 0
    parent[src] = -1;
    for(int i = 0 ;i<v-1;i++)
    {

        int u = min_distance(dis,dis_min);

        dis_min[u] = true;

        
        for(int j=0;j<v;j++)
        {

            if(graph[u][j] && !dis_min[j] && dis[u]!=INT_MAX && dis[u]+graph[u][j] <dis[j])
            {
                dis[j] = dis[u] + graph[u][j];
                parent[j] = u;
            }
        }

        
    }

     printSolution(dis,src,parent);
}
//dijkstra end
//**********************
//hospital start

void least1(int s)
{
    dis[s]=INT_MAX;
    printf("\nthe list of first four nearest hospitals from home is :\n\n");
    for(int j=1;j<=4;j++)
    {
	int key=dis[0],index=0;
	for(int i=0;i<9;i++)
	{
		if(dis[i]<key && rt[i].hospital)
		{
			key=dis[i];
			index=i;
		}
	}
	printf("^^^^^^^%d)Hospital at %s is at a distance of %d from %s^^^^^^^\n",j,rt[index].places,key,rt[s].places);
	dis[index]=INT_MAX;
    }
}

void least2(int arr1[],int arr2[],int s,int m)
{
	arr2[m]=INT_MAX;
	int key1=arr1[m],key2=arr2[0],index2=0;
	for(int i=0;i<9;i++)
	{
		if((i!=s) && arr2[i]<key2 && rt[i].hospital)
		{
			key2=arr2[i];
			index2=i;
		}
	}
	int total_dist=key1+key2;
	printf("^^^the nearest hospital is %s which is at a distance of %d from %s(with a intermediate location of %s)^^^\n",rt[index2].places,total_dist,rt[s].places,rt[m].places);
}


void deco(int s,void (*p)(int[v][v],int))
{
printf("**************************************************************************************\n");
p(graph,s);
printf("**************************************************************************************\n");
}

void copy(int a[],int b[])
{
for(int i=0;i<v;i++)
{
a[i]=b[i];
}
}

void hospital()
{
	int s,i;//u stores the index of the intermediate
	printf("\nplease enter the home ID number : ");
	scanf("%d",&s);
	printf("\nPlease enter a intermediatte location id number if required,if not then enter(-1) : ");
	scanf("%d",&i);
	int d1[v],d2[v];
	if(true)
	{
		if(i==-1)
		{
			printf("\nthe path list is \n\n");
			deco(s,dijkstra);
			least1(s);
		}
		else if(i>=0)
		{
			printf("\nthe first path list is :\n\n");
			deco(s,dijkstra);
			copy(d1,dis);
			printf("\n the second path list is \n\n");
			deco(i,dijkstra);
			copy(d2,dis);
			least2(d1,d2,s,i);
		}
	}
	else
	{
		printf("!!!!!!SORRY!! your location doesn't have a Hospital\n\n");
	}
}

//Hospital end

void disp_graph()//to print the nodes on stdout file
{
	FILE *f1=fopen("graph.txt","r");
	char ch;
	while((ch=fgetc(f1))!=EOF)
	{
		fputc(ch,stdout);
	}
	printf("\n\n\n");
	fclose(f1);
}
void restaurant()
{
	char src[50];char dest[50];
	printf("Enter the source:");
	scanf("%s",src);
	for(int i=0;i<9;i++)
	{
		if(strcmp(src,rt[i].places)==0)
			dijkstra(graph,i);
	}
}

void destination()
{
    int src,dest;
    printf("Enter your current location and destination in terms of corresponding integers\n");
    scanf("%d %d",&src,&dest);
    if(src<0 || src>=9 || dest<0 || dest>=9 || src==dest)
    {
        printf("Enter valid integers\n");
        destination();
        exit(0);
    }
    dijkstra(graph,src);
    printf("Your location :%s\n",rt[src].places);
    printf("Destination :%s\n", rt[dest].places);
    printf("Available facilities at your destination:\n\n");
    if(rt[dest].hospital)
    printf("Hospital\n");
    if(rt[dest].cinema)
    printf("Cinema Hall\n");
    if(rt[dest].restaurant)
    printf("Restaurant\n");
    printf("\nRoute :");
    printPath(parent,dest);
    printf("%s\n","You have reached");
    printf("Distance :%d\n", dis[dest]);
}


void cinema_hall()
{
    int src,dest;
    printf("Enter your current location and destination in terms of corresponding integers\n");
    scanf("%d %d",&src,&dest);
    if(src<0 || src>=9 || dest<0 || dest>=9 || src==dest)
    {
        printf("Enter valid integers");
        cinema_hall();
        exit(0);
    }
    dijkstra(graph,src);
    for (int i = 0; i < v; i++)
        {
            if(i==src) continue;
            else if(rt[i].cinema && dest==i)
            {
                printf("Found Cinema hall..\n" );
                printf("From :%s\n",rt[src].places);
                printf("To :%s\n", rt[i].places);
                printf("Route :");
                printPath(parent,i);
                printf("%s\n","You have reached");
                printf("Distance :%d\n", dis[i]);
            }
        } 
        if(!rt[dest].cinema)
        printf("Sorry...No Cinema hall spotted at your destination\n");
}


int main()
{
      
    disp_graph();
    printf("enter the choice \n1)Hospital\n2)Restaurant\n3)Cinema Hall\n4)Destination\n5)Quit\n->  ");
    int c;
    scanf("%d",&c);
    while(true)
    {
    	switch(c)
    	{
    		case 1:
    		hospital();
    		break;
    		case 2:
    		restaurant();
    		break;
    		case 3:
    		cinema_hall();
    		break;
		case 4:
		destination();
		break;
    		case 5:
    		return 0;
    		default:
    		printf("invalid choice");
    	}
    	printf("\nenter the choice \n1)Hospital\n2)Restaurant\n3)Cinema Hall\n4)Destination\n5)Quit\n->  ");
    	scanf("%d",&c);
    }

   
    return 0;
}
