#include<stdio.h>
#include <stdlib.h>
#include <string.h>
//****************************************************************//
int sequence[10000]; 		//array of page sequence
int count=0;			//number of pages
int n_frames=0;		//max number of frames
char policy[15];		//string holding the policy's name
//****************************************************************//
void reader()
{
	int iteration=0;		//loop counter
	//char filename[50];
	int element=0;			//element scanned
	/*
	printf("Please enter file name (including .txt) : ");
	fgets(filename,50,stdin);
	printf("\n");
	
	int lc=strlen(filename);		    	
	if(lc>0 && filename[lc-1]=='\n')	
	{					
		filename[lc-1] ='\0';	
		lc--;				
	}
	
	FILE* f1;
	f1=fopen(filename,"r");
	
	fscanf(f1,"%d\n",&n_frames);
	fscanf(f1,"%s\n",policy);
	while(!feof(f1))
	{
		fscanf(f1,"%d\n",&element);
		if(element != -1)
			sequence[count++] = element;
	
		else
			break;
	}
	fclose(f1);
	*/
	while (1)
	{
		if(iteration!=1)
		{
		  	//printf("Enter the digit: ");
			scanf("%d",&element);		//scan the element
			//printf("iternation# %d\t",iteration);
		  	//printf("element=%d\n",element);
		}	
		else if(iteration==1)
		{
			//printf("Enter the policy: ");
			scanf("%s",policy);	//scan the policy
			//printf("iternation# %d\t",iteration);
		  	//printf("element=%s\n",policy);
			iteration++;
			continue;
		}
		
		if(element==-1)
			break;
			
		if(iteration==0)
			n_frames=element;
		else if(iteration>1)
		{
			sequence[count++]=element;
		}
			
		iteration++;
	}
}
//****************************************************************//
int FIFO(int pages[])
{
	int counter1=0;	//counter for the number of frames in frame
	int present;	//flag for wheether this page is in current frames
	int frame_index=0;	//pointer the next location to put a page
	int is_full=0;	//flag to indicate if the frame sequence is full
	int faults=0;		//Number of page faults occured
	
	int* frame;		//frame sequency
	frame=(int*)malloc(n_frames*sizeof(int));
	for(int i=0;i<n_frames;i++)
	{
		frame[i]=-1;
	}
	//******************************//
	printf("Replacement Policy = FIFO\n");
	printf("-------------------------------------\n");
	printf("Page   Content of Frames\n");
	printf("----   -----------------\n");
	//******************************//
	for(int i=0;i<count;i++)
	{
		present=0;
		for(int j=0;j<n_frames;j++)
		{
			if(frame[j]==-1)
			{
				break;
			}
			else if(pages[i]==frame[j])
			{
				present=1;
				break;
			}
		}
		//******************************//
		if(present==0 && is_full==0)	//msh mwgode w msh malyana
		{
			frame[frame_index]=pages[i];
			counter1++;
			frame_index = (1+frame_index) % n_frames;
		}
		//******************************//
		else if(present==0 && is_full==1)//msh  mwgooda bas malyana
		{
			frame[frame_index]=pages[i];
			frame_index = (1+frame_index) % n_frames;
			faults++;
				
		}
		//******************************//
		else if(present==1)	//mwgoda
		{
			//Do nothing
		}
		//******************************//
		if(pages[i]>9)
			printf("%d",pages[i]);
		else if(pages[i]<=9)
			printf("0%d",pages[i]);
			
		if(present==1 && is_full==0)
			printf("     ");
		else if(present==1 && is_full==1)
			printf("     ");
		else if(present==0 && is_full==0)
			printf("     ");
		else if(present==0 && is_full==1)
			printf(" F   ");
			
		for(int j=0;j<counter1;j++)
		{
			if(frame[j]>9)
				printf("%d ",frame[j]);
			else if(frame[j]<=9)
				printf("0%d ",frame[j]);
		}
		printf("\n");
		//******************************//
		if(counter1==n_frames)
			is_full=1;
		//******************************//	
	}
	//******************************//
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",faults);
	return faults;
	//******************************//
}

//****************************************************************//
int find_next(int n_pages,int pages[],int frame,int index)
{
	int next;
	for(int i=index+1;i<n_pages;i++)
	{
		if(frame == pages[i])
		{
			next=i;
			break;
		}
		if(i == n_pages-1 && frame!= pages[i])
		{
			next=count+1;
			break;
		}
	}
	
	return next;
}
//****************************************************************//
int find_max(int array[],int n)
{
	int i,j,pos;
	int max=array[0];
	for(i=0;i<n;i++)
	{
		if(array[i]>max)
		{
			max=array[i];
			pos=i;
		}
	}
	return max;
}
//****************************************************************//
int OPTIMAL(int pages[])
{
	int counter1=0;
	int present;
	int frame_index=0;
	int is_full=0;
	int faults=0;
	int pos;	
	int furthest;
	int duplicate;
	
	int* frame;
	int* next;
	
	frame=(int*)malloc(n_frames*sizeof(int));
	next =(int*)malloc(n_frames*sizeof(int));
	
	for(int i=0;i<n_frames;i++)
	{
		frame[i]=-1;
		next[i]=-1;
	}
	//******************************//
	printf("Replacement Policy = OPTIMAL\n");
	printf("-------------------------------------\n");
	printf("Page   Content of Frames\n");
	printf("----   -----------------\n");
	//******************************//
	
	for(int i=0;i<count;i++)
	{
		present=0;
		for(int j=0;j<n_frames;j++)
		{
			if(frame[j]==-1)
			{
				break;
			}
			else if(pages[i]==frame[j])
			{
				present=1;
				break;
			}
		}
		//******************************//
		if(present==0 && is_full==0)//msh mwgoda w msh mlyana
		{
			frame[frame_index]=pages[i];
			counter1++;
			frame_index = (1+frame_index) % n_frames;
		}
		//******************************//
		else if(present==0 && is_full==1)//msh mwgoda bas mlyana
		{
			duplicate=0;
			for(int j=0;j<n_frames;j++)
			{
				next[j]=find_next(count,pages,frame[j],i);
			}
			
			
			furthest=find_max(next,n_frames);
			
			for(int j=0;j<n_frames-1;j++)
			{
				if(duplicate==1)
					break;
				for(int k=j+1;k<n_frames;k++)
				{
					if(next[j]==next[k])
					{
						duplicate=1;
						break;
					}
				}
			}
			
			if(furthest>count && duplicate==1)
			{
				int x;
				for(int j=0;j<n_frames;j++)
				{
					x=next[frame_index];
					if(x==furthest)
					{
						pos=frame_index;
						break;
					}
					else
					{
				frame_index = (1+frame_index) % n_frames;
					}
				}
				
			}
			else if(furthest>count && duplicate==0)
			{
				for(int j=0;j<n_frames;j++)
				{
					if(next[j]==furthest)
					{
						pos=j;
						break;
					}
				}
			}
			else if(furthest<count)
			{
				for(int j=0;j<n_frames;j++)
				{
					if(next[j]==furthest)
					{
						pos=j;
						break;
					}
				}
			}
			frame[pos]=pages[i];
			frame_index=(1+frame_index) % n_frames;
			faults++;
			
		}
		//******************************//
		else if(present == 1 )
		{
			//Do nothing
		}
		//******************************//
		if(pages[i]>9)
			printf("%d",pages[i]);
		else if(pages[i]<=9)
			printf("0%d",pages[i]);
			
		if(present==1 && is_full==0)
			printf("     ");
		else if(present==1 && is_full==1)
			printf("     ");
		else if(present==0 && is_full==0)
			printf("     ");
		else if(present==0 && is_full==1)
			printf(" F   ");
			
		for(int j=0;j<counter1;j++)
		{
			if(frame[j]>9)
				printf("%d ",frame[j]);
			else if(frame[j]<=9)
				printf("0%d ",frame[j]);
		}
		printf("\n");
		//******************************//
		if(counter1==n_frames)
			is_full=1;
		//******************************//		
	}
	//******************************//
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",faults);
	//******************************//
	return faults;
}

//****************************************************************//
int find_min_index(int array[],int n)
{
	int i,pos=0;
	int min=array[0];
	for(i=0;i<n;i++)
	{
		if(array[i]<min)
		{
			min=array[i];
			pos=i;
		}
	}
	return pos;
}
//****************************************************************//
int find_min(int array[],int n)
{
	int i,pos=0;
	int min=array[0];
	for(i=0;i<n;i++)
	{
		if(array[i]<min)
		{
			min=array[i];
			pos=i;
		}
	}
	return min;
}
//****************************************************************//

int LRU(int pages[])
{
	int counter1=0;
	int present;
	int frame_index=0;
	int is_full=0;
	int faults=0;
	int pos;	
	int index;
	
	int* frame;
	int* uses;
	frame=(int*)malloc(n_frames*sizeof(int));
	uses =(int*)malloc(n_frames*sizeof(int));
	for(int i=0;i<n_frames;i++)
	{
		frame[i]=-1;
		uses[i]=0;
	}
	//******************************//
	printf("Replacement Policy = LRU\n");
	printf("-------------------------------------\n");
	printf("Page   Content of Frames\n");
	printf("----   -----------------\n");
	//******************************//
	for(int i=0;i<count;i++)
	{
		present=0;
		for(int j=0;j<n_frames;j++)
		{
			if(frame[j]==-1)
			{
				break;
			}
			else if(pages[i]==frame[j])
			{
				present=1;
				break;
			}
		}
		//******************************//
		if(present==0 && is_full==0)//msh mwgoda w msh mlyana
		{
			frame[frame_index]=pages[i];
			uses[frame_index]=i;
			counter1++;
			frame_index = (1+frame_index) % n_frames;
		}
		//******************************//
		else if(present==0 && is_full==1)//msh mwgoda bas mlyana
		{
			index=frame_index;
			index=find_min_index(uses,n_frames);
			pos=index;
			
			frame[pos]=pages[i];
			uses[pos]=i;
			faults++;
		}
		//******************************//
		else if(present == 1)
		{
			for(int j=0;j<n_frames;j++)
			{
				if(frame[j]==pages[i])
				{
					uses[j]=i;
					break;
				}
			}
		}
		//******************************//
		//******************************//
		if(pages[i]>9)
			printf("%d",pages[i]);
		else if(pages[i]<=9)
			printf("0%d",pages[i]);
			
		if(present==1 && is_full==0)
			printf("     ");
		else if(present==1 && is_full==1)
			printf("     ");
		else if(present==0 && is_full==0)
			printf("     ");
		else if(present==0 && is_full==1)
			printf(" F   ");
			
		for(int j=0;j<counter1;j++)
		{
			if(frame[j]>9)
				printf("%d ",frame[j]);
			else if(frame[j]<=9)
				printf("0%d ",frame[j]);
		}
		printf("\n");
		//******************************//
		if(counter1==n_frames)
			is_full=1;
		//******************************//
	}
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",faults);
	//******************************//
	return faults;
}

//****************************************************************//
int CLOCK(int pages[])
{
	int counter1=0;
	int present;
	int frame_index=0;
	int is_full=0;
	int faults=0;
	int pos;	
	int index;
	
	int* frame;
	int* uses;
	frame=(int*)malloc(n_frames*sizeof(int));
	uses =(int*)malloc(n_frames*sizeof(int));
	
	for(int i=0;i<n_frames;i++)
	{
		frame[i]=-1;
		uses[i]=0;
	}
	//******************************//
	printf("Replacement Policy = CLOCK\n");
	printf("-------------------------------------\n");
	printf("Page   Content of Frames\n");
	printf("----   -----------------\n");
	//******************************//
	for(int i=0;i<count;i++)
	{
		present=0;
		for(int j=0;j<n_frames;j++)
		{
			if(frame[j]==-1)
			{
				break;
			}
			else if(pages[i]==frame[j])
			{
				present=1;
				break;
			}
		}
		//******************************//
		if(present==0 && is_full==0)//msh mwgoda w msh mlyana
		{
			frame[frame_index]=pages[i];
			uses[frame_index]=1;
			counter1++;
			frame_index = (1+frame_index) % n_frames;
		}
		//******************************//
		else if(present==0 && is_full==1)
		{
			for(int j=0;j<n_frames;j++)
			{
				if(uses[frame_index]==0)
				{
					pos=frame_index;
					break;
				}
				else if(uses[frame_index]==1)
				{
				    uses[frame_index]=0;
				    frame_index=(1+frame_index)%n_frames;
				}
			}
			pos=frame_index;
			frame[pos]=pages[i];
			uses[pos]=1;
			frame_index=(1+frame_index)%n_frames;
			faults++;
			
		}
		//******************************//
		else if(present == 1)
		{
			for(int j=0;j<n_frames;j++)
			{
				if(pages[i]==frame[j])
				{
					index=j;
					break;
				}
			}
			uses[index]=1;
		}
		//******************************//
		if(pages[i]>9)
			printf("%d",pages[i]);
		else if(pages[i]<=9)
			printf("0%d",pages[i]);
			
		if(present==1 && is_full==0)
			printf("     ");
		else if(present==1 && is_full==1)
			printf("     ");
		else if(present==0 && is_full==0)
			printf("     ");
		else if(present==0 && is_full==1)
			printf(" F   ");
			
		for(int j=0;j<counter1;j++)
		{
			if(frame[j]>9)
				printf("%d ",frame[j]);
			else if(frame[j]<=9)
				printf("0%d ",frame[j]);
		}
		printf("\n");
		//******************************//
		if(counter1==n_frames)
			is_full=1;
		//******************************//
	}
	//******************************//
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",faults);
	//******************************//
	return faults;
	
}
//****************************************************************//
//****************************************************************//
int main()
{
	reader();
	int choice;
	//******************************//
	if(strcasecmp(policy,"FIFO")==0)
		choice=1;
	else if(strcasecmp(policy,"OPTIMAL")==0)
		choice=2;
	else if(strcasecmp(policy,"LRU")==0)
		choice=3;
	else if(strcasecmp(policy,"CLOCK")==0)
		choice=4;
	else 
		printf("Invalid POlicy\n");
	//******************************//	
	switch(choice)
	{
		case 1:
		{
			FIFO(sequence);
			break;
		}
		case 2:
		{
			OPTIMAL(sequence);
			break;
		}
		case 3:
		{
			LRU(sequence);
			break;
		}
		case 4:
		{
			CLOCK(sequence);
			break;
		}
	}
	//******************************//
	return 0;
}
//****************************************************************//
