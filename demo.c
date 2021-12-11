/*
The Author Is LiYILONG
STUDENT ID IS 3120190971352
WARING:Please respect the fruits of my labor and don't copy my code
*/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

const int RR=1;//时间片
const int PP=3;//优先级下调数
int nowtime=0;
int allAriave=0;
int allRun=0;

typedef struct PCB{
    char process_name;
    int arrive_time;
    int need_time;
    int priority_number;
    int have_run_time;
    int turnaround_time;
    struct PCB* next;
}PCB;

PCB* HeadNode(){
         PCB* Node=(PCB*)malloc(sizeof(PCB));
    if(Node==NULL){
        printf("空间内存不足");
        return Node;
    }
    Node->process_name='N';
    Node->arrive_time=-1;
    Node->need_time=-1;
    Node->priority_number=-1;
    Node->have_run_time=-1;
    Node->turnaround_time=-1;
    Node->next=NULL;
    return Node;
    }

PCB* CreatePCB(
    char process_name, 
    int arrive_time,
    int need_time,
    int priority_number)
{
    PCB* Node=(PCB*)malloc(sizeof(PCB));
    if(Node==NULL){
        printf("空间内存不足");
        return Node;
    }
    Node->process_name=process_name;
    Node->arrive_time=arrive_time;
    Node->need_time=need_time;
    Node->priority_number=priority_number;
    Node->have_run_time=0;
    Node->turnaround_time=0;
    Node->next=NULL;
    return Node;
}

void ShowPCB(PCB* myqueue){
    PCB* fristNode=myqueue->next;
    int cn=0;
    for (PCB* i= fristNode;(i!=fristNode)||(cn==0);i=i->next){
         if(i==NULL){
             printf("This queue is NULL!\n");
            break;
        }
        printf("process_name=%c\t",i->process_name);
        //printf("Arrive_Time=%d\t",i->arrive_time);
        printf("Need_Time=%d\t",i->need_time);
        printf("Priority_Number=%d\t",i->priority_number);
        printf("Have_Run_Time=%d\n",i->have_run_time);
        //printf("Turnaround_Time=%d\t",i->turnaround_time);
         if(i->next==NULL){
            //printf("NextNode=NULL\n");
            break;
        }else{
            //printf("NextNode=%c\n",i->next->process_name);
             }
        cn++;
    }
}

void ShowPCB2(PCB* myqueue){
    PCB* fristNode=myqueue->next;
    int cn=0;
    for (PCB* i= fristNode;(i!=fristNode)||(cn==0);i=i->next){
         if(i==NULL){
             printf("This queue is NULL!\n");
            break;
        }
        printf("process_name=%c\t",i->process_name);
        // printf("Arrive_Time=%d\t",i->arrive_time);
        // printf("Need_Time=%d\t",i->need_time);
        // printf("Priority_Number=%d\t",i->priority_number);
        // printf("Have_Run_Time=%d\t",i->have_run_time);
        printf("Turnaround_Time=%d\n",i->turnaround_time);
         if(i->next==NULL){
            // printf("NextNode=NULL\n");
            break;
        }else{ 
            // printf("NextNode=%c\n",i->next->process_name);
            }
        cn++;
    }
}

// void ShowTurnaroundTime(PCB* endqueue){
//     for (PCB* i = endqueue->next; i!=NULL;i=i->next)
//     {
//         printf("Turnaround_Time=%d\n",i->turnaround_time);
//     }
// }

void DeletePCB(PCB* myqueue,PCB* node){
    //  printf("Delete_node_name=%c\n",node->process_name);
    //  printf("Delete_node's next=%c\n",node->next->process_name);

    PCB* head=myqueue;
    PCB* firstNode=head->next;
    PCB* EndNode=firstNode->next;
    int c=0;
    // printf("head->next:%c\n",head->next->process_name);
     if(firstNode==node&&node->next!=firstNode){
         for (; EndNode->next!=firstNode; EndNode=EndNode->next)
         {
            //  printf("find The Last Node:%c!\n",EndNode->process_name);
         }
        //  printf("The Last Node is:%c!\n",EndNode->process_name);
            head->next=node->next;
            node->next=NULL;
            EndNode->next=head->next;
            // printf("chose A Delete %c succesed!\n",node->process_name);
        }/*删除第一个节点，并且把最后一个节点的指针指向第二个节点*/
     else if(firstNode==node->next){
            node->next=NULL;
            head->next=NULL;
            // printf("chose B Delete %c succesed!\n",node->process_name);
        }
     else{ 
            for (PCB* i = head->next->next; i != NULL; i=i->next)
         /*从第二个节点开始找，找到了目标节点就把上一个指向下一个，跳过中间这个目标节点*/
         {
             if(i->next==node){
            i->next=node->next;
            node->next=NULL;
            // printf("chose C Delete %c succesed!\n",node->process_name);
            break;
             }
         }
    }
}

void AddPCB(PCB* myqueue,PCB* node){
    PCB* head=myqueue;
    PCB* Last=head;
    while(Last!=NULL){
      if(Last->next!=NULL){
          if((node->priority_number>=Last->priority_number)&&(node->priority_number<=Last->next->priority_number)){
             node->next=Last->next;
             Last->next=node;
             break;
          }
        }
        else if(node->priority_number>=Last->priority_number){
            Last->next=node;
            break;
        }
      Last=Last->next;
    }
  // printf("Add Succeed!\n");
}

void EndNodes(PCB* endqueue,PCB* node){
    if(node->have_run_time==node->need_time){
        AddPCB(endqueue,node);
        DeletePCB(endqueue,node);
    }

}

void RunPCB(PCB* runqueue,PCB* readyqueue,PCB* endqueue){
    //printf("Runing is beagin!\n");
    PCB* ReadyHead=readyqueue;
    PCB* RunHead=runqueue;
    PCB* EndHead=endqueue;
    PCB* Node=readyqueue->next;
    //对Redayqueue进行操作
    ReadyHead->next=Node->next;//把就绪列的第二个节点接到头节点后面
    Node->next=NULL;
    RunHead->next=Node;
    // printf("-------------------------Readyqueue:-------------------------\n");
    // ShowPCB(ReadyHead);
    // printf("--------------------------Runqueue:-------------------------\n");
    //ShowPCB(RunHead);
    // printf("-------------------------Start Run!-----------------------\n");
    //printf("now run node is %c\n",Node->process_name);
    Node->have_run_time=Node->have_run_time+RR;
    Node->priority_number=Node->priority_number+PP;
    nowtime=nowtime+RR;
    printf("------------------------------------------------------Runing Queue:--------------------------------------------------------\n");
    ShowPCB(runqueue);
    printf("------------------------------------------------------Ready Queue:--------------------------------------------------------\n");
    ShowPCB(readyqueue);
    RunHead->next=NULL;//完成了运行，删除节点
    //printf("------------------------------Runing succesed---------------\n");
    // printf("--------------------------Runqueue:-------------------------\n");    
   
    //printf("--------------------------Readyque:------------------------\n");
    //ShowPCB(readyqueue);
  
    if(Node->have_run_time==Node->need_time){
        Node->next=NULL;
        PCB* Last=EndHead;
        while (Last->next!=NULL)
        {
            Last=Last->next;
        }
        Last->next=Node;
    }else{
        AddPCB(readyqueue,Node);//返回节点到就绪队列
    }
    // printf("--------------------------Readyque------------------------\n");
    // ShowPCB(readyqueue);

    if(readyqueue->next==NULL){
        allRun=1;
        //printf("readyqueue is NULL\n");
    }
    //printf("------------------Now Time is %d seconds-------------------\n",nowtime);
}

void ArriveNodes(PCB* noqueue,PCB* readyqueue,PCB* endqueue){
    if(noqueue->next==NULL){
        printf("Noqueue is NULL\n");
        allAriave=1;
    }
    //printf("Beagin Arriving!\n");
    PCB* head=NULL;
    PCB* Node=NULL;/*记录一个节点*/
    for (PCB* i = noqueue->next; i!=NULL;)
    {
        if(i->arrive_time<=nowtime){
            if(i->next!=NULL){
                Node=i->next;
            }
            //printf("ArriveNode:%c\n",i->process_name);
            //ShowPCB(noqueue);
            DeletePCB(noqueue,i);
            AddPCB(readyqueue,i);
           // printf("ArriveNode succesed!\n");

            i=Node;
            head=noqueue;
            if(noqueue->next==NULL){
                printf("Here is not arrive node!\n");
                break;
            }

            //printf("Delete after a Nodeis :%c\n",i->process_name);
        }
        else if(i->arrive_time>nowtime){
            printf("----------------------------------------------------Not Entered Queue:----------------------------------------------------\n");
            ShowPCB(noqueue);
            printf("------------------------------------------------------Ready Queue:--------------------------------------------------------\n");
            ShowPCB(readyqueue);
            printf("------------------------------------------------------End Queue:-----------------------------------------------------------\n");
            ShowPCB(endqueue);
            // printf("Other Nodes Arrive time more than Now time\n");
            break;
        }
        else{ 
            i=i->next;
            if(i->next==head->next){
            break;
            }
        }
    }
}
void main(){
    char PCB_Name[6]={'A','B','C','D','E','F'};
    int Arrive_Time[6]={0,0,1,1,3,5};
    int Need_Time[6]={4,5,5,4,4,4};
    int Priority_Number[6]={3,2,0,10,5,2};/*创建进程的信息*/
    // printf("---------Create--Not enterd queue-------------------------------------1\n");
    PCB* Not_entered_queue=HeadNode();
    PCB* Before_Node=NULL;/*表示上一个节点，用来接住下一个节点*/
    Before_Node=Not_entered_queue;/*把表头的地址赋给“上一个节点”*/
    for(int i=0;i<6;i++){
            PCB* New_PCB=CreatePCB(PCB_Name[i],Arrive_Time[i],Need_Time[i],Priority_Number[i]);
            Before_Node->next=New_PCB;
            Before_Node=New_PCB;
    }
    Before_Node->next=Not_entered_queue->next;/*把最后一个节点的指向第一个节点*/
    /*把进程的信息写道未就绪链表里面*/
    // printf("---------Create Not enterd queue is Ok!-------------------------------2\n");
    // /*上述代码是创建未进入队列*/
    // printf("This is a Not enterd queue:\n");
    // ShowPCB(Not_entered_queue);
    // /*读取PCB中的信息*/
    // printf("------------Create---Ready queue---------------------------------------3\n");
    PCB* Ready_queue=HeadNode();//创建活动队列队头
    PCB* Run_queue=HeadNode();
    PCB* End_queue=HeadNode();
    int cn=0;
    while(1){
        printf("----------------------------------------------------now time is %d seconds--------------------------------------------------------\n",nowtime);
        if(allAriave!=1){
            ArriveNodes(Not_entered_queue,Ready_queue,End_queue);
            }
        // printf("------------Not_enter_queue:---------------------------------------------4\n");
        // ShowPCB(Not_entered_queue);
        // printf("------------Ready_queue:------------------------------------------------5\n");
        // ShowPCB(Ready_queue);
        // printf("------------Run:------------------------------------------------6\n");
        // printf("-----------------------------------------------------------------\n");
        if(allRun!=1){
            RunPCB(Run_queue,Ready_queue,End_queue); 
            }

        if(allRun==1&&allAriave==1){
            break;
        }
        cn++;
        // printf("allAriave=%d\n",allAriave);
        // printf("AllRun=%d\n",allRun);
        printf("---------------------------------------------------Have runed %d times----------------------------------------------------\n",cn);

        printf("----------------------------------------------------Not Entered Queue:----------------------------------------------------\n");
        ShowPCB(Not_entered_queue);
        printf("------------------------------------------------------Ready Queue:--------------------------------------------------------\n");
        ShowPCB(Ready_queue);
        printf("------------------------------------------------------Runing Queue:--------------------------------------------------------\n");
        ShowPCB(Run_queue);
        printf("------------------------------------------------------End Queue:-----------------------------------------------------------\n");
        ShowPCB(End_queue);
    }

    for (PCB* i = End_queue->next; i!=NULL; i=i->next)
    {
        i->turnaround_time=nowtime-i->arrive_time;
    }
    
    printf("----------------------------------------------------------End queue-----------------------------------------------------------------\n");
    ShowPCB2(End_queue);

    for (PCB* i = End_queue; i!=NULL; i=i->next)
    {
        free(i);
    }
    
    for (PCB* i = Run_queue; i!=NULL; i=i->next)
    {
        free(i);
    }

    for (PCB* i = Not_entered_queue; i!=NULL; i=i->next)
    {
        free(i);
    }

    for (PCB* i = Ready_queue; i!=NULL; i=i->next)
    {
        free(i);
    }    
}
