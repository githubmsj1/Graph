
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>  
#include <time.h>




void sToVD(char *src, ListD* output)
{
	int ten[]={1,10,100,1000,10000,100000,1000000};
	int index=0;
	int begin=0;
	int end;
	int bit=0;
	while(bit<2)
	{
		if(src[index]==',')
		{
			end=index-1;
			int sum=0;
			for(int i=end;i>=begin;i--)
			{
				sum+=(src[i]-'0')*ten[end-i];
			}
			// output[bit]=sum;
			if(bit==0)
			{
				output->begin=sum;
			}
			else
			{
				output->end=sum;
			}
			bit++;
			begin=index+1;
		}
		index++;

	}

	output->next=(UListD*)malloc(sizeof(UListD));
	UListD* e=output->next;
	while(1)
	{

		if(src[index]>'9'||src[index]<'0')//NULL->\0
		{
			end=index-1;
			int sum=0;
			for(int i=end;i>=begin;i--)
			{
				sum+=(src[i]-'0')*ten[end-i];
			}
			// output[bit]=sum;
			e->next=(UListD*)malloc(sizeof(UListD));
			e=e->next;

			e->data=sum;
			e->next=NULL;

			bit++;
			begin=index+1;

			if(src[index]!='|')//NULL->\0
			{
				// output[bit]=-1;
				output->size=bit-2;

				break;
			}
		}
		// printf("index: %d",index);
		index++;

	}

}
bool sToV(char *src,int *output)
{
	int ten[]={1,10,100,1000,10000,100000,1000000};
	int index=0;
	int begin=0;
	int end;
	int bit=0;

	while(bit<4)
	{
		if(src[index]==','||src[index]=='\n'||src[index]==(char)(NULL))
		{
			end=index-1;
			int sum=0;
			for(int i=end;i>=begin;i--)
			{
				sum+=(src[i]-'0')*ten[end-i];
			}
			output[bit]=sum;
			bit++;
			begin=index+1;
		}
		index++;

	}
	if(src[index-1]==(char)(NULL))
	{
		return true;
		
	}
	else
	{
		return false;
		

	}
}

void visit()
{}
//
void BFSInit(ALGraph* graph,ListD* demand)
{
	UListD* pD=demand->next->next;

	// int count=0;
	while(pD)
	{
		int source=pD->data;

		bool visited[graph->vexNum];
		std::queue<int>trans;
		for(unsigned int i=0;i<graph->vexNum;i++)
		{
			visited[i]=false;
		}
		visited[source]=true;
		trans.push(source);
		graph->adjList[source].infoVal=graph->vexNum;
		int visitVex=1;
		int visitVexMax=((float)graph->vexNum)/demand->size;//*0.8*4/demand->size;

		while(visitVex<visitVexMax&&trans.size()!=0)
		{
			//-----------------1 1000000 1000000 1000000 100000


			int vex=trans.front();
			trans.pop();
			EdgeNode* p=graph->adjList[vex].firstEdgeI;
			while(p)
			{
				if(visited[p->adjvex]==false)
				{
					visited[p->adjvex]=true;
					visitVex++;
					graph->adjList[p->adjvex].infoVal+=graph->adjList[vex].infoVal/3;//-50;//50;
					if(graph->adjList[p->adjvex].infoVal<0)
					{
						graph->adjList[p->adjvex].infoVal=1;
					}
					trans.push(p->adjvex);
				}
				p=p->next;
			}
			// if(count==1)
			// {
			// 	/////////////////////////////////////////////////////////
			//     unsigned short result[] = {1, 5, 4};//示例中的一个解
			//     for (int i = 0; i < 3; i++)
			//         record_result(result[i]);
			//     return;
			// 	/////////////////////////////////////////////////////////
			// }
		}

	    // count++;
		pD=pD->next;
	}

}


int roughSearch(ALGraph* graph,ListD* demand,int src,int des,std::vector<int> &output)
{
	using namespace std;


	// clock_t start = clock();

	vector<int> path;
	vector<int> pathEdge;
	path.push_back(src);
	pathEdge.push_back(-1);
	// pathEdge.push_back(-1)
	// stack<pair<int,int> >reflect;//<stepth,who,route>;
	vector<ReflectNode> reflect1;
	
	// int finalIdex=src;
	bool visited[graph->vexNum];



	// reflect.push(make_pair(0,src));
	// ReflectNodeLink firstreflect=(ReflectNodeLink)malloc(sizeof(ReflectNode));
	// reflect1.push_back(make_pair(0,src));
	ReflectNode firstReflect;
	firstReflect.stepth=0;
	firstReflect.edgeID=-1;
	firstReflect.nodeID=src;
	reflect1.push_back(firstReflect);


	bool satisfied=false;
	PathNodeLink result;//result of Dij
	//while(reflect.size()&&!satisfied)
	while(reflect1.size()&&!satisfied)
	{
		
		// clock_t end = (clock() - start)/CLOCKS_PER_SEC;
		
		// printf("%d s\n",end);
		// if(end>7)
		// {
		// 	return -1;
		// }
		// pair<int,int>tmp=reflect.top();
		// int autoSize=reflect1.size()/2;
		// autoSize=(autoSize==0?1:autoSize);
		int randIndex=reflect1.size()-1;//clock()%reflect1.size();////rand->clock
		
		// printf("****%lu\n",clock());
		// printf("****%lu\n",reflect1.size());
		// pair<int,int>tmp=reflect1[randIndex];//`````````````````edit
		ReflectNode tmp=reflect1[randIndex];
		//reflect.pop();
		// printf("reflect1 size: %lu",reflect1.size());
		reflect1.resize(randIndex+1);

		//reflect1.erase(reflect1.begin()+randIndex);
		// printf("reflect1 size: %lu",reflect1.size());

		// EdgeNode *p=graph->adjList[tmp.second].firstEdge;
		// path[tmp.first]=tmp.second;
		EdgeNode *p=graph->adjList[tmp.nodeID].firstEdge;
		path[tmp.stepth]=tmp.nodeID;
		pathEdge[tmp.stepth]=tmp.edgeID;

		//init demanded vex;
		vector<int> demandVisited;
		UListD* pD=demand->next->next;
		while(pD)
		{
			demandVisited.push_back(pD->data);
			pD=pD->next;
		}

		for(unsigned int i=0;i<graph->vexNum;i++)
		{
			visited[i]=false;
		}
		
		path.resize(tmp.stepth+1);//rebuild the path
		pathEdge.resize(tmp.stepth+1);

		for(unsigned int i=0;i<path.size();i++)
		{
			visited[path[i]]=true;

			for(unsigned int j=0;j<demandVisited.size();j++)
			{
				if(demandVisited[j]==path[i])
				{
					demandVisited.erase(demandVisited.begin()+j);
				}
			}
		}



		while(path.back()!=des&&p)
		{
			// int maxVal=-1;
			int choice=-1;
			int choiceEdge=-1;
			// vector<Unit>choice List;//---------------------------Last night -_-
			
			EdgeNode *_p=p;
			//search the node with biggest val
			while(p)
			{
				if(visited[p->adjvex]==false)
				{
					//??????????????visited[p->adjvex]=true;
					choice=p->adjvex;
				}
				p=p->next;
			}
			
			

			if(choice==-1)
				break;
			visited[choice]=true;

// printf("here???\n");
			//push the some biggest node into stack
			while(_p)
			{
				if(visited[_p->adjvex]==false)
				{
						ReflectNode tmp;
						tmp.stepth=path.size();
						tmp.nodeID=_p->adjvex;
						tmp.edgeID=_p->edgeID;
						reflect1.push_back(tmp);

				}
				_p=_p->next;
			}

			// printf("<<<%lu\n",path.size());
			path.push_back(choice);
			pathEdge.push_back(choiceEdge);
			// printf("%d>>>\n",path.size());

						//finalIdex++;
			p=graph->adjList[choice].firstEdge;

			//erase the required node visited
			for(unsigned int i=0;i<demandVisited.size();i++)
			{
				if(demandVisited[i]==choice)
				{
					demandVisited.erase(demandVisited.begin()+i);
				}
			}

			if(demandVisited.size()==0)
			{
				satisfied=true;
				break;
			}

			// //accelerate
			// int perCost=graph->vexNum/demand->size;
			// int predicCost=perCost*(demand->size-demandVisited.size());
			// printf("theory:%d real:%d \n",predicCost,path.size() );
			// if(path.size()>predicCost+50)
			// {
			// 	printf("break\n");
			// 	break;
			// }
		}

		//the demand are found
		if(satisfied==true)
		{
			printf("\nPathNode(%lu) is :\n",path.size());
			for(unsigned int i=0;i<path.size();i++)
			{
				printf("%d->",path[i]);
			}

			// // pathEdge.erase(pathEdge.begin());
			printf("\nPathEdge(%lu) is :\n",pathEdge.size());
			for(unsigned int i=0;i<pathEdge.size();i++)
			{
				printf("%d->",pathEdge[i]);
			}

			printf("\nDemand(%lu) is :\n",demandVisited.size());
			for(unsigned int i=0;i<demandVisited.size();i++)
			{
				printf("%d ",demandVisited[i]);
			}

			printf("Info List;\n");
			for(unsigned int i=0;i<graph->vexNum;i++)
			{
				printf("%d:%d\n",i,graph->adjList[i].infoVal);
			}

			if(dijMa(graph,path.back(),des,visited,result)==-1)
			{
				satisfied=false;
				printf("we go back to the %dth way...\n",randIndex);
				printf("DIJ Fail\n");
			}
			// getchar();

		}

			// printf("\nPathNode(%lu) is :\n",path.size());
			// for(int i=0;i<path.size();i++)
			// {
			// 	printf("%d->",path[i]);
			// }

			// // // pathEdge.erase(pathEdge.begin());
			// printf("\nPathEdge(%lu) is :\n",pathEdge.size());
			// for(int i=0;i<pathEdge.size();i++)
			// {
			// 	printf("%d->",pathEdge[i]);
			// }

		printf("\nDemand(%lu) is :\n",demandVisited.size());
		for(unsigned int i=0;i<demandVisited.size();i++)
		{
			printf("%d ",demandVisited[i]);
		}
		printf(">>>>%lu\n",reflect1.size());

	}
	printf(">>>>%d\n",satisfied);
	// PathNodeLink result;//=(PathNodeLink)malloc(sizeof(PathNode));;
	// result->path=new vector<int>();
	// result->path->push_back(1);
	// printf("%lu\n",result->path->size());
	// dijMa(graph,path.back(),des,visited,result);


	// if(result==NULL)
	// {
	// 	printf("%s\n", );
	// }
	// printf("!!!!!\n");
	// printf("%d\n",result->path);
	vector<int> &tmpPath=*(result->path);
	// printf("?????\n");

	printf("DIJMA:\n");
	for(unsigned int i=0;i<tmpPath.size();i++)
	{
		printf("%d->",tmpPath[i]);
	}

	vector<int> &tmpPathEdge=*(result->pathEdge);
	printf("\nDIJMAPath:\n");
	for(unsigned int i=0;i<tmpPathEdge.size();i++)
	{
		printf("%d->",tmpPathEdge[i]);
	}


	output.resize(0);
	for(unsigned int i=1;i<pathEdge.size();i++)
	{
		output.push_back(pathEdge[i]);
	}
	for(unsigned int i=1;i<tmpPathEdge.size();i++)
	{
		output.push_back(tmpPathEdge[i]);
	}

	printf("Done\n");

	return 0;

}



int goThrough(ALGraph* graph,ListD* demand,int src,int des,std::vector<int> &output)
{
	using namespace std;


	// clock_t start = clock();

	vector<int> path;
	vector<int> pathEdge;
	path.push_back(src);
	pathEdge.push_back(-1);
	// pathEdge.push_back(-1)
	// stack<pair<int,int> >reflect;//<stepth,who,route>;
	vector<ReflectNode> reflect1;
	
	// int finalIdex=src;
	bool visited[graph->vexNum];



	// reflect.push(make_pair(0,src));
	// ReflectNodeLink firstreflect=(ReflectNodeLink)malloc(sizeof(ReflectNode));
	// reflect1.push_back(make_pair(0,src));
	ReflectNode firstReflect;
	firstReflect.stepth=0;
	firstReflect.edgeID=-1;
	firstReflect.nodeID=src;
	reflect1.push_back(firstReflect);


	bool satisfied=false;
	PathNodeLink result;//result of Dij
	//while(reflect.size()&&!satisfied)
	while(reflect1.size()&&!satisfied)
	{
		
		// clock_t end = (clock() - start)/CLOCKS_PER_SEC;
		
		// printf("%d s\n",end);
		// if(end>7)
		// {
		// 	return -1;
		// }
		// pair<int,int>tmp=reflect.top();
		// int autoSize=reflect1.size()/2;
		// autoSize=(autoSize==0?1:autoSize);
		int randIndex=clock()%reflect1.size();////rand->clock
		
		// printf("****%lu\n",clock());
		// printf("****%lu\n",reflect1.size());
		// pair<int,int>tmp=reflect1[randIndex];//`````````````````edit
		ReflectNode tmp=reflect1[randIndex];
		//reflect.pop();
		// printf("reflect1 size: %lu",reflect1.size());
		reflect1.resize(randIndex+1);

		//reflect1.erase(reflect1.begin()+randIndex);
		// printf("reflect1 size: %lu",reflect1.size());

		// EdgeNode *p=graph->adjList[tmp.second].firstEdge;
		// path[tmp.first]=tmp.second;
		EdgeNode *p=graph->adjList[tmp.nodeID].firstEdge;
		path[tmp.stepth]=tmp.nodeID;
		pathEdge[tmp.stepth]=tmp.edgeID;

		//init demanded vex;
		vector<int> demandVisited;
		UListD* pD=demand->next->next;
		while(pD)
		{
			demandVisited.push_back(pD->data);
			pD=pD->next;
		}

		for(unsigned int i=0;i<graph->vexNum;i++)
		{
			visited[i]=false;
		}
		
		path.resize(tmp.stepth+1);//rebuild the path
		pathEdge.resize(tmp.stepth+1);

		for(unsigned int i=0;i<path.size();i++)
		{
			visited[path[i]]=true;

			for(unsigned int j=0;j<demandVisited.size();j++)
			{
				if(demandVisited[j]==path[i])
				{
					demandVisited.erase(demandVisited.begin()+j);
				}
			}
		}



		while(path.back()!=des&&p)
		{
			int maxVal=-1;
			int choice=-1;
			int choiceEdge=-1;
			// vector<Unit>choice List;//---------------------------Last night -_-
			
			EdgeNode *_p=p;
			//search the node with biggest val
			while(p)
			{
				if(visited[p->adjvex]==false)
				{
					//??????????????visited[p->adjvex]=true;
					if(graph->adjList[p->adjvex].infoVal>maxVal)
					{
						maxVal=graph->adjList[p->adjvex].infoVal;
						choice=p->adjvex;
						choiceEdge=p->edgeID;
					}
				}
				p=p->next;
			}
			
			

			if(choice==-1)
				break;
			visited[choice]=true;

// printf("here???\n");
			//push the some biggest node into stack
			while(_p)
			{
				if(visited[_p->adjvex]==false)
				{
					if(maxVal==0)
					{
						// reflect.push(make_pair(path.size(),_p->adjvex));
						// reflect1.push_back(make_pair(path.size(),_p->adjvex));
						ReflectNode tmp;
						tmp.stepth=path.size();
						tmp.nodeID=_p->adjvex;
						tmp.edgeID=_p->edgeID;
						reflect1.push_back(tmp);
					}
					else if(((float)graph->adjList[_p->adjvex].infoVal)/(float)maxVal>0.1)
					{
						// reflect.push(make_pair(path.size(),_p->adjvex));
						// reflect1.push_back(make_pair(path.size(),_p->adjvex));
						ReflectNode tmp;
						tmp.stepth=path.size();
						tmp.nodeID=_p->adjvex;
						tmp.edgeID=_p->edgeID;
						reflect1.push_back(tmp);

					}
				}
				_p=_p->next;
			}

			// printf("<<<%lu\n",path.size());
			path.push_back(choice);
			pathEdge.push_back(choiceEdge);
			// printf("%d>>>\n",path.size());

						//finalIdex++;
			p=graph->adjList[choice].firstEdge;

			//erase the required node visited
			for(unsigned int i=0;i<demandVisited.size();i++)
			{
				if(demandVisited[i]==choice)
				{
					demandVisited.erase(demandVisited.begin()+i);
				}
			}

			if(demandVisited.size()==0)
			{
				satisfied=true;
				break;
			}

			// //accelerate
			// int perCost=graph->vexNum/demand->size;
			// int predicCost=perCost*(demand->size-demandVisited.size());
			// printf("theory:%d real:%d \n",predicCost,path.size() );
			// if(path.size()>predicCost+50)
			// {
			// 	printf("break\n");
			// 	break;
			// }
		}

		//the demand are found
		if(satisfied==true)
		{
			printf("\nPathNode(%lu) is :\n",path.size());
			for(unsigned int i=0;i<path.size();i++)
			{
				printf("%d->",path[i]);
			}

			// // pathEdge.erase(pathEdge.begin());
			printf("\nPathEdge(%lu) is :\n",pathEdge.size());
			for(unsigned int i=0;i<pathEdge.size();i++)
			{
				printf("%d->",pathEdge[i]);
			}

			printf("\nDemand(%lu) is :\n",demandVisited.size());
			for(unsigned int i=0;i<demandVisited.size();i++)
			{
				printf("%d ",demandVisited[i]);
			}

			// printf("Info List;\n");
			// for(unsigned int i=0;i<graph->vexNum;i++)
			// {
			// 	printf("%d:%d\n",i,graph->adjList[i].infoVal);
			// }

			if(dijMa(graph,path.back(),des,visited,result)==-1)
			{
				satisfied=false;
				printf("we go back to the %dth way...\n",randIndex);
				printf("DIJ Fail\n");
			}
			// getchar();

		}

			// printf("\nPathNode(%lu) is :\n",path.size());
			// for(unsigned int i=0;i<path.size();i++)
			// {
			// 	printf("%d->",path[i]);
			// }

			// // // pathEdge.erase(pathEdge.begin());
			// printf("\nPathEdge(%lu) is :\n",pathEdge.size());
			// for(unsigned int i=0;i<pathEdge.size();i++)
			// {
			// 	printf("%d->",pathEdge[i]);
			// }

		printf("\nDemand(%lu) is :\n",demandVisited.size());
		for(unsigned int i=0;i<demandVisited.size();i++)
		{
			printf("%d ",demandVisited[i]);
		}
		printf(">>>>%lu\n",reflect1.size());

	}
	printf(">>>>%d\n",satisfied);
	// PathNodeLink result;//=(PathNodeLink)malloc(sizeof(PathNode));;
	// result->path=new vector<int>();
	// result->path->push_back(1);
	// printf("%lu\n",result->path->size());
	// dijMa(graph,path.back(),des,visited,result);


	// if(result==NULL)
	// {
	// 	printf("%s\n", );
	// }
	// printf("!!!!!\n");
	// printf("%d\n",result->path);
	vector<int> &tmpPath=*(result->path);
	// printf("?????\n");

	printf("DIJMA:\n");
	for(unsigned int i=0;i<tmpPath.size();i++)
	{
		printf("%d->",tmpPath[i]);
	}

	vector<int> &tmpPathEdge=*(result->pathEdge);
	printf("\nDIJMAPath:\n");
	for(unsigned int i=0;i<tmpPathEdge.size();i++)
	{
		printf("%d->",tmpPathEdge[i]);
	}


	output.resize(0);
	for(unsigned int i=1;i<pathEdge.size();i++)
	{
		output.push_back(pathEdge[i]);
	}
	for(unsigned int i=1;i<tmpPathEdge.size();i++)
	{
		output.push_back(tmpPathEdge[i]);
	}

	printf("Done\n");

	return 0;

}
void clearVector(std::vector<int>&src)
{
	std::vector<int> tmp;
	tmp.swap(src); 
}
int dijMa(ALGraph *graph,int srcVex,int desVex,bool *visited,PathNodeLink &result)
{
	using namespace std;
	int dist[graph->vexNum];
	for(unsigned int i=0;i<graph->vexNum;i++)
	{
		dist[i]=INF;
	}


	vector<PathNodeLink>pool;
	// vector<PathNodeLink>result;

	PathNodeLink src=(PathNodeLink)malloc(sizeof(PathNode));

	src->idx=srcVex;
	src->weight=0;
	// printf("????%lu\n",src->path.size());
	src->path=new vector<int>();
	src->pathEdge=new vector<int>();
	src->path->push_back(srcVex);
	src->pathEdge->push_back(-1);
	// printf("!!!!\n");
	pool.push_back(src);
	visited[srcVex]=false;

	// printf("?????%lu\n",pool.size());
	while(!pool.empty())
	{


		PathNodeLink top=pool.front();
		pool.erase(pool.begin());
		// result


		if(visited[top->idx])
		{	

			clearVector(*top->path);
			free(top);
			continue;
		}
		visited[top->idx]=true;


		if(top->idx==desVex)
		{
			result=top;
			printf("Got........\n");
			return 0;
			// break;
		}

		EdgeNode *p=graph->adjList[top->idx].firstEdge;
		int cw=top->weight;

		while(p)
		{

			if(!visited[p->adjvex]&&(cw+p->weight)<dist[p->adjvex])
			{

				dist[p->adjvex]=cw+p->weight;

				PathNodeLink tmp=(PathNodeLink)malloc(sizeof(PathNode));
				tmp->idx=p->adjvex;
				tmp->weight=dist[p->adjvex];
				tmp->path=new vector<int>();
				tmp->pathEdge=new vector<int>();
				vector<int> &tmpPath=*(top->path);
				vector<int> &tmpPathEdge=*(top->pathEdge);

				for(unsigned int i=0;i<top->path->size();i++)
				{
					tmp->path->push_back(tmpPath[i]);
					tmp->pathEdge->push_back(tmpPathEdge[i]);
				}
				tmp->path->push_back(p->adjvex);
				tmp->pathEdge->push_back(p->edgeID);
				
				//push the new element into the pool
				unsigned int poolSize=pool.size();
				for(unsigned int i=0;i<pool.size();i++)
				{
					if(tmp->weight<pool[i]->weight)
					{
						pool.insert(pool.begin()+i,tmp);
						break;
					}
				}
				if(pool.size()==poolSize)
				{
					// printf("pool have new element\n");
					pool.push_back(tmp);
				}
				
			}

			p=p->next;

		}

		

	}
	return -1;
	 

}
//你要完成的功能总入口
void search_route(char *topo[5000],unsigned int edge_num, char *demand)
{
//------------ok

	ALGraph graph;
	graph.vexNum=0;
	graph.edgeNum=edge_num;

	int temp[4]={0,0,0,0};
	EdgeLink e;




	for(unsigned int i=0;i<MAX_NUM;i++)
	{
		graph.adjList[i].firstEdge=NULL;
		graph.adjList[i].data=i;
	}

	for(unsigned int i=0;i<MAX_NUM;i++)
	{
		graph.adjList[i].firstEdgeI=NULL;
		graph.adjList[i].data=i;
	}

	//read the lata from the char* and store it in to a graph 
	int maxNode=0;
	for(unsigned int i=0;i<edge_num;i++)
	{
		

		sToV(topo[i],temp);

		e=(EdgeLink)malloc(sizeof(EdgeNode));
		e->weight=temp[3];
		e->adjvex=temp[2];
		e->edgeID=i;
		e->next=graph.adjList[temp[1]].firstEdge;
		graph.adjList[temp[1]].firstEdge=e;

		e=(EdgeLink)malloc(sizeof(EdgeNode));
		e->weight=temp[3];
		e->adjvex=temp[1];
		e->edgeID=i;
		e->next=graph.adjList[temp[2]].firstEdgeI;
		graph.adjList[temp[2]].firstEdgeI=e;


		if(maxNode<temp[1])
		{
			maxNode=temp[1];
			if(maxNode<temp[2])
			{
				maxNode=temp[2];
			}
		}

	}
	graph.vexNum=maxNode+1;

	//init the vex parameter
	for(unsigned int i=0;i<graph.vexNum;i++)
	{
		graph.adjList[i].code=NULL;
		graph.adjList[i].vexNum=0;
	}

	ListD demandList;
	sToVD(demand,&demandList);
//-----------ok


	// int temp1[10];
	// sToV(topo[1],temp);
	// sToVD(demand,temp1);
	// int prinfIndex=0;
	// while(temp1[prinfIndex]!=-1)
	// {
	// 	printf("%d: ",prinfIndex);
	// 	printf("%d ",temp1[prinfIndex]);
	// 	prinfIndex++;
	// }


	printf("graph is :\n");
	printf("output :\n");
	for(unsigned int i=0; i<graph.vexNum;i++)
	{
		printf("%d:",i);
		EdgeLink p=graph.adjList[i].firstEdge;
		while(p!=NULL)
		{
			printf(" %d",p->adjvex);
			p=p->next;
		}
		printf("\n");
	}
		printf("input :\n");
	for(unsigned int i=0;i<graph.vexNum;i++)
	{
		printf("%d:",i);
		EdgeLink p=graph.adjList[i].firstEdgeI;
		while(p!=NULL)
		{
			printf(" %d",p->adjvex);
			p=p->next;
		}
		printf("\n");
	}
	printf("\n");

	printf("demand is :\n");
	UListD* tmp=demandList.next->next;
	while(tmp!=NULL)
	{
		printf("%d|",tmp->data);
		tmp=tmp->next;
	}
	
	printf("\n");


	// printf("%lu\n",demandList.size);
	// for (int i = 0; i < 5; ++i)
	// {
	// 	printf("%c ",demand[i]);
	// }

	int cIdex=0;
	while(demand[cIdex]!=(char)NULL)
	{
		printf("%c",demand[cIdex]);
		cIdex++;
	}
	printf("\n");

//--------------------------ok


	BFSInit(&graph,&demandList);
	// return ;
//---------------------------1000000 0 0 0 0 0 0 0 0 0 0

	// printf("Info List;\n");
	// for(unsigned int i=0;i<graph.vexNum;i++)
	// {
	// 	printf("%d:%d\n",i,graph.adjList[i].infoVal);
	// }


	std::vector<int>edgePath;
	if(goThrough(&graph,&demandList,demandList.begin,demandList.end,edgePath)==-1)
	// if(roughSearch(&graph,&demandList,demandList.begin,demandList.end,edgePath)==-1)
	{	
		return;
	}
//--------------------------1000000 0 100000 100000 100000 100000 100000  100000


	printf("\nFinal Path:\n");
	for(unsigned int i=0;i<edgePath.size();i++)
	{
		printf("%d|",edgePath[i]);
	}

    // unsigned short result[] = {2, 6, 3};//示例中的一个解

    // for (int i = 0; i < 3; i++)
    //     record_result(result[i]);
    //------------------------------1000000 0 100000 100000 100000 100000 100000  100000
	// /////////////////////////////////////////////////////////
 //    unsigned short result[] = {1, 5, 4};//示例中的一个解
 //    for (int i = 0; i < 3; i++)
 //        record_result(result[i]);
 //    return;
	// /////////////////////////////////////////////////////////

    for (int i = 0; i < (int)edgePath.size(); i++)
        record_result((unsigned short)edgePath[i]);
    // for (int i = 0; i < edgePath.size(); i++)
    // {
    // 	printf("%d ",edgePath[i]);
    // }

}
