#ifndef __ROUTE_H__
#define __ROUTE_H__

#include <vector>



#define INF INT_MAX
#define MAX_NUM 5000

// #define TRUE 0
// #define FALSE 1
typedef int VexType;

typedef struct _UListD
{
	struct _UListD* next;
	int data;
	int visitVex;
}UListD;

typedef struct 
{
	unsigned int begin;
	unsigned int end;
	UListD* next;
	unsigned long size;
}ListD;



typedef struct EdgeNode
{
	int adjvex;
	int edgeID;
	struct EdgeNode *next;
	int weight;

}EdgeNode,*EdgeLink;

typedef struct VexNode
{
	VexType data;
	EdgeNode *firstEdge;
	EdgeNode *firstEdgeI;
	unsigned long *code;
	unsigned long vexNum;
	int infoVal;
}VexNode,AdjList[MAX_NUM];

typedef struct 
{
	AdjList adjList;
	unsigned long vexSize;
	unsigned long vexNum,edgeNum;
}ALGraph;

typedef struct 
{
	int vexIdx;
	int weight;
}IW;

typedef struct PathNode
{
	int idx;
	std::vector<int>* path;
	std::vector<int>* pathEdge;
	int weight;
}PathNode,*PathNodeLink;


typedef struct
{
	int nodeID;
	int edgeID;
	int stepth;
}ReflectNode,*ReflectNodeLink;
void search_route(char *graph[5000], unsigned int edge_num, char *condition);
int dijMa(ALGraph *graph,int srcVex,int desVex,bool *visited,PathNodeLink &result);
#endif
