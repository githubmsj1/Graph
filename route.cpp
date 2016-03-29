
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

#define QUIT_BEST 0
#define	CHOS_BEST 1
#define WANT_BEST 2


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
	for (unsigned int i = 0; i < graph->vexNum; ++i)
	{
		graph->adjList[i].infoVal=0;
	}

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
		graph->adjList[source].infoVal=graph->vexNum;//cover -> no cover
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
					if(graph->adjList[vex].edgeINum==1)
					{
						graph->adjList[p->adjvex].infoVal+=graph->adjList[vex].infoVal;
					}
					else
					{
						graph->adjList[p->adjvex].infoVal+=graph->adjList[vex].infoVal/3;//-50;//50;
					}

					if(graph->adjList[p->adjvex].infoVal<0)//max(0,x)
					{
						graph->adjList[p->adjvex].infoVal=1;
					}
					if(graph->adjList[p->adjvex].infoVal>(int)graph->vexNum)//min(x,max)
					{
						graph->adjList[p->adjvex].infoVal=graph->vexNum;
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


// int roughSearch(ALGraph* graph,ListD* demand,int src,int des,std::vector<int> &output)
// {
// 	using namespace std;


// 	// clock_t start = clock();

// 	vector<int> path;
// 	vector<int> pathEdge;
// 	path.push_back(src);
// 	pathEdge.push_back(-1);
// 	// pathEdge.push_back(-1)
// 	// stack<pair<int,int> >reflect;//<stepth,who,route>;
// 	vector<ReflectNode> reflect1;
	
// 	// int finalIdex=src;
// 	bool visited[graph->vexNum];



// 	// reflect.push(make_pair(0,src));
// 	// ReflectNodeLink firstreflect=(ReflectNodeLink)malloc(sizeof(ReflectNode));
// 	// reflect1.push_back(make_pair(0,src));
// 	ReflectNode firstReflect;
// 	firstReflect.stepth=0;
// 	firstReflect.edgeID=-1;
// 	firstReflect.nodeID=src;
// 	reflect1.push_back(firstReflect);


// 	bool satisfied=false;
// 	PathNodeLink result;//result of Dij
// 	//while(reflect.size()&&!satisfied)
// 	while(reflect1.size()&&!satisfied)
// 	{
		
// 		// clock_t end = (clock() - start)/CLOCKS_PER_SEC;
		
// 		// printf("%d s\n",end);
// 		// if(end>7)
// 		// {
// 		// 	return -1;
// 		// }
// 		// pair<int,int>tmp=reflect.top();
// 		// int autoSize=reflect1.size()/2;
// 		// autoSize=(autoSize==0?1:autoSize);
// 		int randIndex=reflect1.size()-1;//clock()%reflect1.size();////rand->clock
		
// 		// printf("****%lu\n",clock());
// 		// printf("****%lu\n",reflect1.size());
// 		// pair<int,int>tmp=reflect1[randIndex];//`````````````````edit
// 		ReflectNode tmp=reflect1[randIndex];
// 		//reflect.pop();
// 		// printf("reflect1 size: %lu",reflect1.size());
// 		reflect1.resize(randIndex+1);

// 		//reflect1.erase(reflect1.begin()+randIndex);
// 		// printf("reflect1 size: %lu",reflect1.size());

// 		// EdgeNode *p=graph->adjList[tmp.second].firstEdge;
// 		// path[tmp.first]=tmp.second;
// 		EdgeNode *p=graph->adjList[tmp.nodeID].firstEdge;
// 		path[tmp.stepth]=tmp.nodeID;
// 		pathEdge[tmp.stepth]=tmp.edgeID;

// 		//init demanded vex;
// 		vector<int> demandVisited;
// 		UListD* pD=demand->next->next;
// 		while(pD)
// 		{
// 			demandVisited.push_back(pD->data);
// 			pD=pD->next;
// 		}

// 		for(unsigned int i=0;i<graph->vexNum;i++)
// 		{
// 			visited[i]=false;
// 		}
		
// 		path.resize(tmp.stepth+1);//rebuild the path
// 		pathEdge.resize(tmp.stepth+1);

// 		for(unsigned int i=0;i<path.size();i++)
// 		{
// 			visited[path[i]]=true;

// 			for(unsigned int j=0;j<demandVisited.size();j++)
// 			{
// 				if(demandVisited[j]==path[i])
// 				{
// 					demandVisited.erase(demandVisited.begin()+j);
// 				}
// 			}
// 		}



// 		while(path.back()!=des&&p)
// 		{
// 			// int maxVal=-1;
// 			int choice=-1;
// 			int choiceEdge=-1;
// 			// vector<Unit>choice List;//---------------------------Last night -_-
			
// 			EdgeNode *_p=p;
// 			//search the node with biggest val
// 			while(p)
// 			{
// 				if(visited[p->adjvex]==false)
// 				{
// 					//??????????????visited[p->adjvex]=true;
// 					choice=p->adjvex;
// 				}
// 				p=p->next;
// 			}
			
			

// 			if(choice==-1)
// 				break;
// 			visited[choice]=true;

// // printf("here???\n");
// 			//push the some biggest node into stack
// 			while(_p)
// 			{
// 				if(visited[_p->adjvex]==false)
// 				{
// 						ReflectNode tmp;
// 						tmp.stepth=path.size();
// 						tmp.nodeID=_p->adjvex;
// 						tmp.edgeID=_p->edgeID;
// 						reflect1.push_back(tmp);

// 				}
// 				_p=_p->next;
// 			}

// 			// printf("<<<%lu\n",path.size());
// 			path.push_back(choice);
// 			pathEdge.push_back(choiceEdge);
// 			// printf("%d>>>\n",path.size());

// 						//finalIdex++;
// 			p=graph->adjList[choice].firstEdge;

// 			//erase the required node visited
// 			for(unsigned int i=0;i<demandVisited.size();i++)
// 			{
// 				if(demandVisited[i]==choice)
// 				{
// 					demandVisited.erase(demandVisited.begin()+i);
// 				}
// 			}

// 			if(demandVisited.size()==0)
// 			{
// 				satisfied=true;
// 				break;
// 			}

// 			// //accelerate
// 			// int perCost=graph->vexNum/demand->size;
// 			// int predicCost=perCost*(demand->size-demandVisited.size());
// 			// printf("theory:%d real:%d \n",predicCost,path.size() );
// 			// if(path.size()>predicCost+50)
// 			// {
// 			// 	printf("break\n");
// 			// 	break;
// 			// }
// 		}

// 		//the demand are found
// 		if(satisfied==true)
// 		{
// 			printf("\nPathNode(%lu) is :\n",path.size());
// 			for(unsigned int i=0;i<path.size();i++)
// 			{
// 				printf("%d->",path[i]);
// 			}

// 			// // pathEdge.erase(pathEdge.begin());
// 			printf("\nPathEdge(%lu) is :\n",pathEdge.size());
// 			for(unsigned int i=0;i<pathEdge.size();i++)
// 			{
// 				printf("%d->",pathEdge[i]);
// 			}

// 			printf("\nDemand(%lu) is :\n",demandVisited.size());
// 			for(unsigned int i=0;i<demandVisited.size();i++)
// 			{
// 				printf("%d ",demandVisited[i]);
// 			}

// 			printf("Info List;\n");
// 			for(unsigned int i=0;i<graph->vexNum;i++)
// 			{
// 				printf("%d:%d\n",i,graph->adjList[i].infoVal);
// 			}

// 			if(dijMa(graph,path.back(),des,visited,result)==-1)
// 			{
// 				satisfied=false;
// 				printf("we go back to the %dth way...\n",randIndex);
// 				printf("DIJ Fail\n");
// 			}
// 			// getchar();

// 		}

// 			// printf("\nPathNode(%lu) is :\n",path.size());
// 			// for(int i=0;i<path.size();i++)
// 			// {
// 			// 	printf("%d->",path[i]);
// 			// }

// 			// // // pathEdge.erase(pathEdge.begin());
// 			// printf("\nPathEdge(%lu) is :\n",pathEdge.size());
// 			// for(int i=0;i<pathEdge.size();i++)
// 			// {
// 			// 	printf("%d->",pathEdge[i]);
// 			// }

// 		printf("\nDemand(%lu) is :\n",demandVisited.size());
// 		for(unsigned int i=0;i<demandVisited.size();i++)
// 		{
// 			printf("%d ",demandVisited[i]);
// 		}
// 		printf(">>>>%lu\n",reflect1.size());

// 	}
// 	printf(">>>>%d\n",satisfied);
// 	// PathNodeLink result;//=(PathNodeLink)malloc(sizeof(PathNode));;
// 	// result->path=new vector<int>();
// 	// result->path->push_back(1);
// 	// printf("%lu\n",result->path->size());
// 	// dijMa(graph,path.back(),des,visited,result);


// 	// if(result==NULL)
// 	// {
// 	// 	printf("%s\n", );
// 	// }
// 	// printf("!!!!!\n");
// 	// printf("%d\n",result->path);
// 	vector<int> &tmpPath=*(result->path);
// 	// printf("?????\n");

// 	printf("DIJMA:\n");
// 	for(unsigned int i=0;i<tmpPath.size();i++)
// 	{
// 		printf("%d->",tmpPath[i]);
// 	}

// 	vector<int> &tmpPathEdge=*(result->pathEdge);
// 	printf("\nDIJMAPath:\n");
// 	for(unsigned int i=0;i<tmpPathEdge.size();i++)
// 	{
// 		printf("%d->",tmpPathEdge[i]);
// 	}


// 	output.resize(0);
// 	for(unsigned int i=1;i<pathEdge.size();i++)
// 	{
// 		output.push_back(pathEdge[i]);
// 	}
// 	for(unsigned int i=1;i<tmpPathEdge.size();i++)
// 	{
// 		output.push_back(tmpPathEdge[i]);
// 	}

// 	printf("Done\n");

// 	return 0;

// }



int goThrough(ALGraph* graph,ListD* demand,int src,int des,std::vector<int> &output)
{
	using namespace std;

	//make a const demand visit 
	vector<int> demandVisitedConst;
	UListD* pD=demand->next->next;
	while(pD)
	{
		demandVisitedConst.push_back(pD->data);
		pD=pD->next;
	}

	//initialize a probability class 
	Probablity demandProb(demandVisitedConst.size());


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
	PathNodeLink result=NULL;//result of Dij

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
		// printf("\nThe stack now is:\n");
		// printf("\n_________________________\n");
		// for(unsigned int i=0;i<reflect1.size();i++)
		// {	
		// 	printf("[%d] pos:%d  idx%d\n",i,reflect1[i].stepth,reflect1[i].nodeID);
		// }
		// printf("\n_________________________\n");

		// printf("****%lu\n",clock());
		// printf("****%lu\n",reflect1.size());
		// pair<int,int>tmp=reflect1[randIndex];//`````````````````edit
		ReflectNode tmp=reflect1[randIndex];
		//reflect.pop();
		// printf("reflect1 size: %lu",reflect1.size());
		reflect1.resize(randIndex+1);

		//reflect1.erase(reflect1.begin()+randIndex);
		// printf("reflect1 size: %lu",reflect1.size());
		path.resize(tmp.stepth+1);//rebuild the path
		pathEdge.resize(tmp.stepth+1);
		// EdgeNode *p=graph->adjList[tmp.second].firstEdge;
		// path[tmp.first]=tmp.second;
		EdgeNode *p=graph->adjList[tmp.nodeID].firstEdge;
		path[tmp.stepth]=tmp.nodeID;
		pathEdge[tmp.stepth]=tmp.edgeID;

		printf("\nBefore resize\n");
		printf("\ntmp.stepth:%d  pathsize:%lu\n",tmp.stepth,path.size());
		for(unsigned int i=0;i<path.size();i++)
		{
			printf("%d->",path[i]);
		}


		//init demanded vex;
		vector<int> demandVisited;
		vector<int> demandInPath;//extract from path ,have access demand point,don't need to clear

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
		

		



		printf("\nreflect ind:%d    back stepth:%d     back node:%d\n",randIndex,tmp.stepth,tmp.nodeID);
		printf("\nAfter back PathNode(%lu) is :\n",path.size());
		for(unsigned int i=0;i<path.size();i++)
		{
			printf("%d->",path[i]);
		}
		// getchar();


		//initialize the visited Node and demandNode
		for(unsigned int i=0;i<path.size();i++)
		{
			visited[path[i]]=true;

			for(unsigned int j=0;j<demandVisited.size();j++)
			{
				if(demandVisited[j]==path[i])
				{
					demandVisited.erase(demandVisited.begin()+j);
					demandInPath.push_back(path[i]);
				}
			}
		}



		while(path.back()!=des&&p)
		{

			// printf("\nPath(%lu) is :\n",path.size());
			// for(unsigned int i=0;i<path.size();i++)
			// {
			// 	printf("%d->",path[i]);
			// }


			int maxVal=-1;
			// int minVal=graph->vexNum+1;//high weight

			int choice=-1;
			int choiceEdge=-1;
			// int choiceBad=-1;
			// int choiceEdgeBad=-1;
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
					// if(graph->adjList[p->adjvex].infoVal<minVal)
					// {
					// 	minVal=graph->adjList[p->adjvex].infoVal;
					// 	choiceBad=p->adjvex;
					// 	choiceEdgeBad=p->edgeID;

					// }
				}
				p=p->next;
			}
			

			//judge whether the node is the required node 
			//if yes judge it if it is the best one
			//chose it as the next node if hit probability
			//otherwise don't take it
			if(choice!=-1)
			{
				for(unsigned int i=0;i<demandVisited.size();i++)
				{
					if(demandVisited[i]==choice)
					{
						demandInPath.push_back(demandVisited[i]);

						if(demandProb.chooseOrNot(demandInPath)==false)
						{
							printf("choose false\n");
							choice=-2;
							demandInPath.pop_back();
							break;
						}
						else
						{
							printf("choose true\n");
							demandInPath.pop_back();
							break;
						}
						
					}
				}
			}

			if(choice==des)
			{
				choice=-1;
			}




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
					else if(((float)graph->adjList[_p->adjvex].infoVal)/(float)maxVal>=0)//>0.1
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





			//break if quit the next step
			printf("\nchoice=%d\n",choice);
			if(choice==-2)//last night........
			{

				int bestIdx=demandProb.getTheBestIdx(demandInPath);
				bool _visited[graph->vexNum];
				vector<int>desIdxs;
				for(unsigned int i=0;i<graph->vexNum;i++)
				{
					_visited[i]=visited[i];
				}

				//two case:
				//1.variation exclude the best,include the demand (non-visited in current depth and not the best)
				//2.include the best and the non visited in current depth


				printf("not choose the demand\n");
				printf("Because ");

				if(demandProb.getFlag()==QUIT_BEST)
				{
					printf("quit best\n");
					_visited[bestIdx]=true;
					_visited[des]=true;
					for(unsigned int i=0;i<demandVisited.size();i++)
					{
						if(_visited[demandVisited[i]]==false)
						{
							desIdxs.push_back(demandVisited[i]);
						}
					}

				}
				else if(demandProb.getFlag()==WANT_BEST)
				{
					printf("want best\n");
					demandProb.pushNotBestVisited(demandInPath,_visited);
					// printf("asdasdasdas\n");

					_visited[des]=true;
					desIdxs.push_back(bestIdx);
					for(unsigned int i=0;i<demandVisited.size();i++)
					{
						if(_visited[demandVisited[i]]==false)
						{
							desIdxs.push_back(demandVisited[i]);
						}
					}
				}
				else
				{
					printf("error\n");
				}
				// break;
				
				
				printf("find the best...%d\n",bestIdx);
				// 
				// tmpBestidx.push_back(bestidx);
				// dijMa(graph,path.back(),bestidx,_visited,result);
				// printf("found");
				// getchar();
				// break;
				if(dijMaAdvanced(graph,path.back(),desIdxs,_visited,result)==-1)
				{
					printf("DIJ fail can't find\n");
					break;
				}
				else
				{

					//merge
					// path.resize(path.size()+result->path->size()-1);
					// pathEdge.resize(pathEdge.size()+result->pathEdge->size()-1);
					vector<int> &tmpPath=*(result->path);

					vector<int> &tmpPathEdge=*(result->pathEdge);

					for(unsigned int i=1;i<tmpPath.size();i++)
					{
						path.push_back(tmpPath[i]);
					}

					for(unsigned int i=1;i<tmpPathEdge.size();i++)
					{
						pathEdge.push_back(tmpPathEdge[i]);
					}

					//clean result
					clearVector(*result->path);
					clearVector(*result->pathEdge);
					free(result);

					//re generate
					for (unsigned int i = 0; i < path.size();i++)
					{
						visited[path[i]]=true;
					}

					p=graph->adjList[path.back()].firstEdge;

					for(unsigned int i=0;i<demandVisited.size();i++)
					{
						if(demandVisited[i]==path.back())
						{
							demandVisited.erase(demandVisited.begin()+i);
							demandInPath.push_back(path.back());
						}
					}
					if(demandVisited.size()==0)
					{
						printf("all demand node are found\n");
						satisfied=true;
						break;
					}
					continue;

				}
				
			}

			if(choice==-1)//can't find the next node,maybe find a loop
			{
				printf("dead route\n");
				// getchar();
				demandProb.refresh(demandInPath);
				break;
			}


			//set the choice visited
			visited[choice]=true;



			//push the the choice into current route
			path.push_back(choice);
			pathEdge.push_back(choiceEdge);


			//give the next node list
			p=graph->adjList[choice].firstEdge;


			//erase the required node visited
			//deleted the demand needed list if the current node is demand
			for(unsigned int i=0;i<demandVisited.size();i++)
			{
				if(demandVisited[i]==choice)
				{
					demandVisited.erase(demandVisited.begin()+i);
					demandInPath.push_back(choice);
				}
			}

			//finish find the demand
			if(demandVisited.size()==0)
			{
				printf("all demand node are found\n");
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
			// printf("%d %d\n",path.back(),des);
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

			vector<int>desVec;
			desVec.push_back(des);
			if(dijMaAdvanced(graph,path.back(),desVec,visited,result)==-1)//dijMa(graph,path.back(),des,visited,result)==-1)
			{
				satisfied=false;
				printf("we go back to the %dth way...\n",randIndex);
				printf("DIJ Fail\n");
			}
			// getchar();

		}

			printf("\nPathNode(%lu) is :\n",path.size());
			for(unsigned int i=0;i<path.size();i++)
			{
				printf("%d->",path[i]);
			}

			// // // pathEdge.erase(pathEdge.begin());
			// printf("\nPathEdge(%lu) is :\n",pathEdge.size());
			// for(unsigned int i=0;i<pathEdge.size();i++)
			// {
			// 	printf("%d->",pathEdge[i]);
			// }

		
		// printf("\nDemand(%lu) is :\n",demandVisited.size());
		// for(unsigned int i=0;i<demandVisited.size();i++)
		// {
		// 	printf("%d ",demandVisited[i]);
		// }

		// printf("\nDemand Visited(%lu) is :\n",demandInPath.size());
		// for(unsigned int i=0;i<demandInPath.size();i++)
		// {
		// 	printf("%d ",demandInPath[i]);
		// }

		printf("\nThe reflect stack size is: %lu\n",reflect1.size());
		printf("it is ready to back");
		// getchar();


	}
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

	// clearVector(*result->pathEdge);
	// clearVector(*result->path);
	// free(result);


	printf("Done\n");

	return 0;

}
void clearVector(std::vector<int>&src)
{
	std::vector<int> tmp;
	tmp.swap(src); 
}
int dijMa(ALGraph *graph,int srcVex,int desVex,bool *visited,PathNodeLink &result)//copy the visit don't destroy
{
	using namespace std;


	// //clean result
	// if(result!=NULL)
	// {

	// 	if(result->path!=NULL)
	// 	{
			
	// 		clearVector(*result->path);
	// 	}

	// 	if(result->pathEdge!=NULL)
	// 	{
	// 		clearVector(*result->pathEdge);
	// 	}
	// 	free(result);
	// }




	int dist[graph->vexNum];
	for(unsigned int i=0;i<graph->vexNum;i++)
	{
		dist[i]=INF;
	}

	bool visited1[graph->vexNum];
	for(unsigned int i=0;i<graph->vexNum;i++)
	{
		visited1[i]=visited[i];
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
	visited1[srcVex]=false;

	// printf("?????%lu\n",pool.size());
	while(!pool.empty())
	{


		PathNodeLink top=pool.front();
		pool.erase(pool.begin());
		// result


		if(visited1[top->idx])
		{	

			clearVector(*top->path);
			clearVector(*top->pathEdge);

			free(top);
			continue;
		}
		visited1[top->idx]=true;


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

			if(!visited1[p->adjvex]&&(cw+p->weight)<dist[p->adjvex])
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

int dijMaAdvanced(ALGraph *graph,int srcVex,std::vector<int> desVex,bool *visited,PathNodeLink &result)//copy the visit don't destroy
{
	using namespace std;
	
	// //clean result
	// if(result!=NULL)
	// {
	// 	if(result->path!=NULL)
	// 	{
			
	// 		clearVector(*result->path);
	// 	}
	// 	if(result->pathEdge!=NULL)
	// 	{
	// 		clearVector(*result->pathEdge);
	// 	}
	// 	free(result);
	// }



	int dist[graph->vexNum];
	for(unsigned int i=0;i<graph->vexNum;i++)
	{
		dist[i]=INF;
	}

	bool visited1[graph->vexNum];
	for(unsigned int i=0;i<graph->vexNum;i++)
	{
		visited1[i]=visited[i];
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
	visited1[srcVex]=false;

	// printf("?????%lu\n",pool.size());
	while(!pool.empty())
	{


		PathNodeLink top=pool.front();
		pool.erase(pool.begin());
		// result


		if(visited1[top->idx])
		{	

			clearVector(*top->path);
			clearVector(*top->pathEdge);

			free(top);
			continue;
		}
		visited1[top->idx]=true;


		for(unsigned int i=0;i<desVex.size();i++)
		{
			if(top->idx==desVex[i])
			{
				result=top;
				printf("Got........\n");
				return 0;
				// break;
			}
		}

		EdgeNode *p=graph->adjList[top->idx].firstEdge;
		int cw=top->weight;

		while(p)
		{

			if(!visited1[p->adjvex]&&(cw+p->weight)<dist[p->adjvex])
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


//*****************************************class define********************************//
Probablity::Probablity(unsigned int _numDemand)
{
	head=(ProbNodeLink)malloc(sizeof(ProbNode));
	head->depth=0;
	// head->numChild=0;
	// head->next=NULL:
	head->child=new std::map<int,ProbNode*>();
	head->val=0;

	numDemand=_numDemand;
	// variateRate=20;
}
Probablity::~Probablity()
{}

int Probablity::getFlag()
{
	return flag;
}
int Probablity::refresh(std::vector<int> &demandPath)
{
	ProbNodeLink p;
	p=head;
	for(unsigned int i=0;i<demandPath.size();i++)
	{
		if(p->child->find(demandPath[i])==p->child->end())
		{
			ProbNodeLink tmp=(ProbNodeLink)malloc(sizeof(ProbNode));
			tmp->child=new std::map<int,ProbNode*>();
			tmp->depth=i+1;
			tmp->val=numDemand*4;
			p->child->insert(std::pair<int,ProbNodeLink>(demandPath[i],tmp));
		}

		std::map<int,ProbNode*>& pTmp=*(p->child);
		p=pTmp[demandPath[i]];

		p->val-=p->depth;//minus not depth
		// cout<<"index: "<<demandPath[i]<<"   ";
		// cout<<"val: "<<p->val<<"   ";
		// cout<<"depth: "<<p->depth<<endl;
		if(p->val<0)
		{
			p->val=0;
		}

	}
	return 0;
}
int Probablity::establish(std::vector<int> &demandPath)
{

	ProbNodeLink p;
	p=head;

	for(unsigned int i=0;i<demandPath.size();i++)
	{
		if(p->child->find(demandPath[i])==p->child->end())
		{
			ProbNodeLink tmp=(ProbNodeLink)malloc(sizeof(ProbNode));
			tmp->child=new std::map<int,ProbNodeLink>();
			tmp->depth=i+1;
			tmp->val=numDemand*4;
			p->child->insert(std::pair<int,ProbNodeLink>(demandPath[i],tmp));
		}

		std::map<int,ProbNode*>& pTmp=*(p->child);
		p=pTmp[demandPath[i]];
	}

	return 0;
}


int Probablity::getTheBestIdx(std::vector<int> &demandPath)
{
	ProbNodeLink p;
	p=head;

	for(unsigned int i=0;i<demandPath.size();i++)
	{
		if(p->child->find(demandPath[i])==p->child->end())
		{
			ProbNodeLink tmp=(ProbNodeLink)malloc(sizeof(ProbNode));
			tmp->child=new std::map<int,ProbNodeLink>();
			tmp->depth=i+1;
			tmp->val=numDemand*4;
			p->child->insert(std::pair<int,ProbNodeLink>(demandPath[i],tmp));
		}

		std::map<int,ProbNode*>& pTmp=*(p->child);
		p=pTmp[demandPath[i]];
	}

	

	//find the best node:max prob val
	int max=-1;
	int maxIdx=p->child->begin()->first;
	for(std::map<int,ProbNodeLink>::iterator i=p->child->begin();i!=p->child->end();i++)
	{
		if(i->second->val>max)
		{
			max=i->second->val;
			maxIdx=i->first;
		}
		// printf("%d\n",i->first);
	}

	return maxIdx;
}

int Probablity::pushNotBestVisited(std::vector<int> &demandPath,bool *visited)
{
	ProbNodeLink p;
	p=head;

	for(unsigned int i=0;i<demandPath.size();i++)
	{
		if(p->child->find(demandPath[i])==p->child->end())
		{
			ProbNodeLink tmp=(ProbNodeLink)malloc(sizeof(ProbNode));
			tmp->child=new std::map<int,ProbNodeLink>();
			tmp->depth=i+1;
			tmp->val=numDemand*4;
			p->child->insert(std::pair<int,ProbNodeLink>(demandPath[i],tmp));
		}

		std::map<int,ProbNode*>& pTmp=*(p->child);
		p=pTmp[demandPath[i]];
	}

	

	//find the best node:max prob val
	int max=-1;
	int maxIdx=p->child->begin()->first;
	for(std::map<int,ProbNodeLink>::iterator i=p->child->begin();i!=p->child->end();i++)
	{
		if(i->second->val>max)
		{
			max=i->second->val;
			maxIdx=i->first;
		}
		// printf("%d\n",i->first);
	}
	for(std::map<int,ProbNodeLink>::iterator i=p->child->begin();i!=p->child->end();i++)
	{
		if(i->first!=maxIdx)
		{
			visited[i->first]=true;
		}
		// printf("%d\n",i->first);
	}


	return 0;
}



bool Probablity::chooseOrNot(std::vector<int> &demandPath)
{
	ProbNodeLink p;
	p=head;

	for(unsigned int i=0;i<demandPath.size()-1;i++)
	{
		if(p->child->find(demandPath[i])==p->child->end())
		{
			ProbNodeLink tmp=(ProbNodeLink)malloc(sizeof(ProbNode));
			tmp->child=new std::map<int,ProbNodeLink>();
			tmp->depth=i+1;
			tmp->val=numDemand*4;
			p->child->insert(std::pair<int,ProbNodeLink>(demandPath[i],tmp));
		}

		std::map<int,ProbNode*>& pTmp=*(p->child);
		p=pTmp[demandPath[i]];
	}

	if(p->child->find(demandPath.back())==p->child->end())
	{
		ProbNodeLink tmp=(ProbNodeLink)malloc(sizeof(ProbNode));
		tmp->child=new std::map<int,ProbNode*>();
		tmp->depth=demandPath.size();
		tmp->val=numDemand*4;
		p->child->insert(std::pair<int,ProbNodeLink>(demandPath.back(),tmp));
	}

	//find the best node:max prob val
	int max=-1;
	int maxIdx=p->child->begin()->first;
	for(std::map<int,ProbNodeLink>::iterator i=p->child->begin();i!=p->child->end();i++)
	{
		if(i->second->val>max)
		{
			max=i->second->val;
			maxIdx=i->first;
		}
		// printf("%d\n",i->first);
	}

	printf("\n*************************************************\n");
	printf("best Idx: %d   max pro: %d   \n",maxIdx,max);
	printf("demandPath: \n");
	for (unsigned int i=0;i<demandPath.size();i++)
	{
		printf("%d ",demandPath[i]);
	}

	printf("\nThe vals are: \n");
	for(std::map<int,ProbNodeLink>::iterator i=p->child->begin();i!=p->child->end();i++)
	{
		printf("%d(%d)",i->first,i->second->val);
		// printf("%d\n",i->first);
	}


	printf("\n*************************************************\n");
	// getchar();


	std::map<int,ProbNodeLink> &tmpchild=*(p->child);
	if(demandPath.back()==maxIdx)
	{
		// getchar();
		if(clock()%100<20&&tmpchild[maxIdx]->val!=(int)numDemand*4)
		{
			// getchar();
			printf("\nvariation\n");
			flag=QUIT_BEST;
			return false;
		}
		flag=CHOS_BEST;
		return true;
		
	}
	flag=WANT_BEST;
	return false;
}
//*****************************************class define********************************//

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
		graph.adjList[i].firstEdgeI=NULL;
		graph.adjList[i].data=i;
		graph.adjList[i].edgeINum=0;
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
		graph.adjList[temp[2]].edgeINum++;//count edge numbers

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
		printf("%d(%lu):",i,graph.adjList[i].edgeINum);
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

	printf("Info List;\n");
	for(unsigned int i=0;i<graph.vexNum;i++)
	{
		printf("%d:%d\n",i,graph.adjList[i].infoVal);
	}
	// getchar();

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
