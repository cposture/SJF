#include "stdio.h" 
#include <stdlib.h> 
#define getpch(type) (type*)malloc(sizeof(type)) 
struct pcb {  
	char name[10]; 
	char state; 
	int super; 
	int ntime; 
	int rtime; 
	struct pcb* link; 
}*ready=NULL,*p; 
typedef struct pcb PCB;   

void sort() 
{ 
	PCB *first, *second; 
	int insert=0; 
	if((ready==NULL)||((p->ntime)<=(ready->ntime)))
	{ 
		p->link=ready; 
		ready=p; 
	} 
	else
	{ 
		first=ready; 
		second=first->link; 
		while(second!=NULL) 
		{ 
			if((p->ntime)<=(second->ntime)) 
			{ 
				p->link=second; 
				first->link=p; 
				second=NULL; 
				insert=1; 
			} 
			else 
			{ 
				first=first->link; 
				second=second->link; 
			} 
		}	 
		if(insert==0) first->link=p; 
	} 
} 

void input() 
{ 
	int i,num; 
	
	printf("\n process num: "); 
	scanf("%d",&num); 
	for(i=0;i<num;i++) 
	{ 
		printf("\n process number.%d",i); 
		p=getpch(PCB); 
		printf("\n process name: "); 
		scanf("%s",p->name); 
		printf(" process pivot: "); 
		scanf("%d",&p->super); 
		printf(" process needing time: "); 
		scanf("%d",&p->ntime); 
		printf("\n"); 
		p->rtime=0;p->state='w'; 
		p->link=NULL; 
		sort();
	} 
} 

int space() 
{ 
	int l=0; PCB* pr=ready; 
	while(pr!=NULL) 
	{ 
		l++; 
		pr=pr->link; 
	} 
	return(l); 
} 

void disp(PCB * pr) 
{ 
	printf("\n qname \t state \t super \t ndtime \t runtime \n"); 
	printf("|%s\t",pr->name); 
	printf("|%c\t",pr->state); 
	printf("|%d\t",pr->super); 
	printf("|%d\t",pr->ntime); 
	printf("|%d\t",pr->rtime); 
	printf("\n"); 
} 

void check() 
{ 
	PCB* pr; 
	printf("\n **** the running process is :%s",p->name);
	disp(p); 
	pr=ready; 
	printf("\n ****the wait list is:\n"); 
	while(pr!=NULL) 
	{ 
		disp(pr); 
		pr=pr->link; 
	} 
} 

void destroy() 
{ 
	printf("\n process[%s] has finish.\n",p->name); 
	free(p); 
} 

void running()
{ 
	(p->rtime)++; 
	if(p->rtime==p->ntime) 
		destroy(); 
	else 
	{ 
		(p->super)--; 
		p->state='w'; 
		sort();
	} 
} 

int main()
{ 
	int len,h=0; 
	char ch; 
	input(); 
	len=space(); 
	while((len!=0)&&(ready!=NULL)) 
	{ 
		ch=getchar(); 
		h++; 
		printf("\n The execute number:%d \n",h); 
		p=ready; 
		ready=p->link; 
		p->link=NULL; 
		p->state='R'; 
		check(); 
		running(); 
		printf("\n \n continue..."); 
		ch=getchar(); 
	} 
	printf("\n\nfinish\n");
	ch=getchar(); 
	return 0;
} 
