#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>
float global_time=0.0;

struct event{
        float time;
        float arrivaltime;
        float servicetime;
        float idletime;
        int tellerno;
        int action;
        // 1: arrival 
        // 2: service comppleted 
        // 3: teller completed serving
        // 4: teller compteled idle time
        struct event* next;
        struct event* prev;
};
struct tellerQueue{
        struct event* head;
        struct event* tail;
       
};
void add_tellerQueue(struct tellerQueue** list,float arrivaltime, float servicetime, float idletime, float time){
        struct event* newnode = (struct event*) malloc(sizeof(struct event));
     newnode->arrivaltime=arrivaltime;
     newnode->servicetime=servicetime;
     newnode->action=0;
     newnode->idletime=idletime;
     newnode->tellerno=0;
     newnode->time=time;
     newnode->next=NULL; 
     if ((*list)->head == NULL) {
          (*list)->head = (struct event*) malloc(sizeof(struct event));
          (*list)->tail = (struct event*) malloc(sizeof(struct event));
          (*list)->head = newnode;
          (*list)->tail = newnode;    
     }
     else{
          struct event* node = (*list)->head;
          while(node!=NULL){
               node = node->next;
          }
          if(node==NULL){
               newnode->prev = (*list)->tail;
               ((*list)->tail)->next = newnode;
               (*list)->tail = newnode;
          }
         
     }
        return;

}
void add_customer(struct tellerQueue** list,float arrivaltime, float servicetime, float idletime, int action, int tellerno, float time){
           struct event* newnode = (struct event*) malloc(sizeof(struct event));
     newnode->arrivaltime=arrivaltime;
     newnode->servicetime=servicetime;
     newnode->action=action;
     newnode->idletime=idletime;
     newnode->tellerno=tellerno;
     newnode->time=time;
     newnode->next=NULL;
     if ((*list)->head == NULL) {
          (*list)->head = (struct event*) malloc(sizeof(struct event));
          (*list)->tail = (struct event*) malloc(sizeof(struct event));
          (*list)->head = newnode;
          (*list)->tail = newnode;
         
     }
     else{
          struct event* node = (*list)->head;
          while(node!=NULL){
               node = node->next;
          }
          if(node==NULL){
               newnode->prev = (*list)->tail;
               ((*list)->tail)->next = newnode;
               (*list)->tail = newnode;
          }
         
     }
        return;
}
struct EventQueue {
     struct event* head;
     struct event* tail;
     int count;
};

void add_event(struct EventQueue** list,float arrivaltime, float servicetime, float idletime, int action, int tellerno, float time){
        struct event* newnode = (struct event*) malloc(sizeof(struct event));
     newnode->arrivaltime=arrivaltime;
     newnode->servicetime=servicetime;
     newnode->action=action;
     newnode->idletime=idletime;
     newnode->tellerno=tellerno;
     newnode->time=time;
     newnode->next=NULL;
     if ((*list)->head == NULL) {
          (*list)->head = (struct event*) malloc(sizeof(struct event));
          (*list)->tail = (struct event*) malloc(sizeof(struct event));
          (*list)->head = newnode;
          (*list)->tail = newnode;
          (*list)->count = 1;
     }
     else{
          struct event* node = (*list)->head;
          while(node!=NULL){
               float x = node->time;
               float y = time;
               if(x>y){
                    if(node==(*list)->head){
                         node->prev = newnode;
                         newnode->next = node;
                         (*list)->head = newnode;
                    }
                    else{
                         newnode->next = node;
                         (node->prev)->next = newnode;
                         newnode->prev = node->prev;
                         node->prev = newnode;
                    }
                    break;
               }
               node = node->next;
          }
          if(node==NULL){
               newnode->prev = (*list)->tail;
               ((*list)->tail)->next = newnode;
               (*list)->tail = newnode;
          }
          (*list)->count = ((*list)->count)+1;
     }
        return;
}
void print(struct EventQueue** list){
        if((*list)->head==NULL){
                printf("%s\n","NULL");
        }else{
            struct event* current=(*list)->head;
            while(current!=NULL){
                   float time=current->time;
                   printf("%f %d \n",time,current->action); 
                   current=current->next;
            }    
        }
}
void initial_arrival(float simulationTime, int customers,int tellers ,struct EventQueue** list){

       
        
       
        for( int i=0;i<customers;i++){
                 

                float arrTime = (simulationTime * rand())/(float)RAND_MAX;
              //  printf("%f\n",arrTime);
                // global_time=arrTime+global_time;
                
                add_event(list,arrTime,0.0,0.0,1,0,arrTime);
               
        }
        for(int i=0;i<tellers;i++){
              float random=(rand()%600);
              random=random/60;
              //global_time=global_time+random;
             // printf("%f\n",random);

              add_event(list,0.0,0.0,random,4,i+1,random );  
        }

}


int length_events( struct EventQueue** list){
        struct event* current=(*list)->head;
        int count=0;
        if(current==NULL){
                return count;
        }else{
                while(current!=NULL){
                        count++;
                        current=current->next;
                }
                return count;
        }
}
struct event* delete_event(struct EventQueue** list){
        if((*list)->head==NULL){
                return NULL;
        }else{
            struct event* node = (*list)->head;
            (*list)->head=node->next;
            return node;    
        }
}
struct event* delete_customer(struct tellerQueue** list){
         if((*list)->head==NULL){
                return NULL;
        }else{
            struct event* node = (*list)->head;
            (*list)->head=node->next;
            //(node->next)->prev=(*list)->head;
            return node;    
        }
}
bool eventqueue_empty( struct EventQueue** list){
        return (*list)->head==NULL;
}
bool tellerqueue_empty( struct tellerQueue** list){
        return (*list)->head==NULL;
}
struct event* do_sevice(struct event* event, float averageServiceTime){
        float serviceTime = 2*averageServiceTime*rand()/(float)RAND_MAX;
        event->servicetime=serviceTime;
        return event;        
}
void check(struct tellerQueue* teller[],struct event* going, int tellers, struct EventQueue** list,float averageServiceTime,float idle,int graph){
        int a= going->tellerno;
        struct tellerQueue* temp=teller[a-1];
        int len=length(&teller[a-1]);
        if(len==0){
               // printf("%s\n","lennnnnnnnnn");
                int max=length(&teller[a-1]);
                int i;
                int k;
                for(i=0;i<tellers;i++){
                        int len=length(&teller[i]);
                        //printf("length and i := %d %d \n",len, i);
                        if(len>max){
                                max=len;
                                break;
                                
                        }
                }
                // printf("%s %d   %d\n","lennnnnnnnnn   ",max,i);
                if(max!=0){
                        struct event* temp1=delete_customer(&teller[i]);
                        // struct event* temp2=do_sevice(temp1,averageServiceTime);
                        float serviceTime = 2*averageServiceTime*rand()/(float)RAND_MAX;
                        temp1->servicetime=serviceTime;
                        float time=idle+(temp1->servicetime);
                        add_event(list,temp1->arrivaltime, temp1->servicetime, temp1->idletime, 2, a,time );
                        //printf("%s%d%s%f\n","Teller ",a," is completed a service at t",)
                }else{
                       // if(idle<7.0){
                        float random=(rand()%150);
                        random=random/60;
                        //going->idletime=random;
                        float temp1=idle;
                        temp1=random+temp1;
                        add_event(list,0.0,0.0,random,4,a,temp1); 
                      //  printf("%s\n","check");
                      if(graph==0){
                        printf("%s%d%s%f%s%f\n","Teller ",a," did not find any customer at t ",idle," so went for other duties with idle time of ",random);
                      }
                }
        }else{
                // printf("%s\n","check----------");
                // printf("%d\n",a);
                struct event* temp1=delete_customer(&teller[a-1]);
                // printf("%s\n","////////////");
                float serviceTime = 2*averageServiceTime*rand()/(float)RAND_MAX;
                temp1->servicetime=serviceTime;
                //printf("ooooooooooooo%f\n",serviceTime);
                float time=idle+(temp1->servicetime);
          
               
                add_event(list,temp1->arrivaltime, temp1->servicetime, temp1->idletime, 2, a,time );  


        }
}
void arrival(struct tellerQueue* teller[], int tellers,struct event* going){
       // printf("%s\n","arrival");
        int temp=shortest(teller,tellers);
        //printf("%d\n",temp);
        add_customer(&teller[temp-1],going->arrivaltime, going->servicetime, going->idletime, going-> action,temp, going->time);

}
int shortest(struct tellerQueue* teller[],int tellers){
        int x;
        int y;
       
        int arr[tellers];
        int k=0;
        int smallest=length(&teller[0]);
       // printf("%s\n","length=======");
        for(int i=0;i<tellers;i++){
               
                x= length(&teller[i]);
               // printf("%d\n",x);
                if(x<smallest){
                        smallest=x;
                } 
                
        }
      //  printf("smallest %d\n",smallest);
      // printf("%s\n","length=======");
        for(int i=0;i<tellers;i++){
                y= length(&teller[i]);
                if(smallest==y){
                       
                        arr[k]=i;
                        k++;
                       //  printf("%d %d %d\n",i,y,k);
                }
        }
       // printf("%s\n","&&&&&&&&&");
        for(int i=0;i<k;i++){
              //  printf("%d\n",arr[i]);
        }
        //  printf("%d\n",k);
        // printf("%s\n","&&&&&&&&&");
        int flag=rand()%(k);
        //  printf("%s\n","shortest]]]]]]]]]]]]");
        //  printf("%d\n",flag);
        return (arr[flag]+1);
}
float execution(struct EventQueue** EventQueue,struct tellerQueue* teller[], int tellers,float averageServiceTime,float simualationtime,int graph){
      //  printf("%s\n","*******");
        float avg=0.0;
         //float avg=0.0;
        float wait=0.0;
        float totalidle=0.0;
     while(!eventqueue_empty(EventQueue)){
        //      int len=length_events(&EventQueue);
        //         printf("%d\n",len);
                
             struct event* temp= delete_event(EventQueue);
             
             int tel= temp->tellerno;
             float idle=temp->time;
              
             if((temp->action)==4){
                // printf("idle =======%d\n",4);
                 totalidle=totalidle+temp->idletime;
                 if(graph==0){ 
                 printf("%s%d%s%f%s%f\n","Teller ",tel," is completed his/her idle time of ",temp->idletime," at t ",idle);
                 }
                if(idle<simualationtime){
                check(teller,temp,tellers,EventQueue,averageServiceTime,idle,graph);
                }
             }else if ((temp->action)==3){
                //      printf("=======%d\n",3);
                //      printf("%s\n","kapil verma");
             }else if ((temp->action)==2){
                       // printf("completing service========%d\n",2);
                        float time=temp->time;
                        avg=avg+(time-temp->arrivaltime);
                        if(((time-temp->arrivaltime)-temp->servicetime)>wait){
                        wait=(time-temp->arrivaltime)-temp->servicetime;
                        }
                        if(graph==0){
                        printf("%s%d%s%f%s%f\n","Teller ",tel," is completd a service at t ",time," with service time ",temp->servicetime);
                       // int len=length(&teller[0]);
                       // printf("%d\n",len);
                        }
                        if(time<simualationtime){
                        check(teller,temp,tellers,EventQueue,averageServiceTime,idle,graph);
                        }
                        
             }else if(( temp->action)==1){
               // printf("arriving new customer =======%d\n",1);
              //  global_time=temp->arrivaltime;                   //changed made
                arrival(teller,tellers,temp);
                if(graph==0){
                printf("%s%f\n","New customer is arrived at ",temp->time);
                }
             }else{

             }
     }
     if(graph==0){
       printf("\n%s%f\n","Maximum wait is ",wait);
        printf("%s%f\n","Total idle time spent by tellers are ",totalidle);
     }
     return avg;
}

int length(struct tellerQueue** list){
        //printf("%s\n","##########");
        struct event* current=(*list)->head;
        int count=0;
        if(current==NULL){
                return count;
        }else{
                while(current!=NULL){
                        count++;
                        current=current->next;
                }
                return count;
        }
}
void complete(struct tellerQueue** tellerlist,struct event* going, int tellers, struct EventQueue** list,float averageServiceTime,float idle,int graph){
       //printf("%s\n","completed************");
        int tel= going->tellerno;
       //  printf("%s\n","completed************");
        
        int len=length(tellerlist);
        // printf("%s\n","completed************");
        if(len==0){
                float random=(rand()%150);
                random=random/60;
                //going->idletime=random;
                float temp1=idle;
                temp1=random+temp1;
                add_event(list,0.0,0.0,random,4,tel,temp1); 
                //  printf("%s\n","check");
                if(graph==0){
                printf("%s%d%s%f%s%f\n","Teller ",tel," did not find any customer at t ",idle," so went for other duties with idle time of ",random);
                } 
        }else{
                struct event* temp1=delete_customer(tellerlist);
              //   printf("%s\n","////////////");
                float serviceTime = 2*averageServiceTime*rand()/(float)RAND_MAX;
                temp1->servicetime=serviceTime;
                //printf("ooooooooooooo%f\n",serviceTime);
                float time=idle+(temp1->servicetime);      
                add_event(list,temp1->arrivaltime, temp1->servicetime, temp1->idletime, 2, tel,time );    
        }
}
float execution1(struct EventQueue** EventQueue,struct tellerQueue** tellerQueue, int tellers,float averageServiceTime,float simualationtime,int graph){
        float avg=0.0;
        float wait=0.0;
        float totalidle=0.0;
        while(!eventqueue_empty(EventQueue)){
             struct event* temp= delete_event(EventQueue);
             int action=temp->action;
             int tel= temp->tellerno;
             float idle=temp->time;
             if(action==1){
              //  printf("%s\n","action 1");
                // arrival(teller,tellers,temp);
                if(graph==0){
                printf("%s%f\n","New customer is arrived at ",temp->time);
                }
                add_customer(tellerQueue,temp->arrivaltime, temp->servicetime, temp->idletime, 0, 0,idle); 
               // int a=length(tellerQueue);
              ///  printf("$$$$$$$$$$$$$$$$$$$   %d\n",a); 
                //printf("%s%f\n","New customer is arrived at ",temp->time);
             }else if(action==2){
                 //  printf("%s\n","action 2");   

                float time=temp->time;
                avg=avg+(time-temp->arrivaltime); 
                if(((time-temp->arrivaltime)-temp->servicetime)>wait){
                wait=(time-temp->arrivaltime)-temp->servicetime;
                }
                if(graph==0){
                printf("%s%d%s%f%s%f\n","Teller ",tel," is completd a service at t ",time," with service time ",temp->servicetime);
                // int len=length(&teller[0]);
                // printf("%d\n",len);
                }
                if(time<simualationtime){
                        complete(tellerQueue,temp, tellers, EventQueue, averageServiceTime,idle,graph);
                }
             }else if (action==3){

             }else if(action==4){
              //  printf("%s\n","action 4");
               // int a=length(tellerQueue);
              //   printf("$$$$$$$$$$$$$$$$$$$   %d\n",a);
              totalidle=totalidle+temp->idletime; 
              if(graph==0){
                printf("%s%d%s%f%s%f\n","Teller ",tel," is completed his/her idle time of ",temp->idletime," at t ",idle);
              }
                if(idle<simualationtime){
                       // printf("%s\n","*****************************");
                        complete(tellerQueue,temp, tellers, EventQueue, averageServiceTime,idle,graph);
                        
                }
             }   
        }
        if(graph==0){
        printf("\n%s%f\n","Maximum wait is ",wait);
        printf("%s%f\n","Total idle time spent by tellers are ",totalidle);
        }
        return avg;
}

int main(int argc, char* argv[]){
        struct EventQueue* EventQueue= NULL;
        EventQueue = (struct EventQueue*)malloc(sizeof(struct EventQueue));
        int customers=atoi(argv[1]);
        int tellers=atoi(argv[2]);
        float simulationTime=atof(argv[3]);
        float avgservicetime=atof(argv[4]);
        struct tellerQueue* teller[tellers];
        for(int i=0;i<tellers;i++){
                struct tellerQueue* EventQueue1= NULL;
                EventQueue1= (struct tellerQueue*)malloc(sizeof(struct tellerQueue));
                teller[i]=EventQueue1;
        }
        printf("%s%d\n","CUSTOMERS :=",customers);
        printf("%s%d\n","TELLERS :=",tellers);
        printf("%s%f\n","SIMULATIONTIME :=",simulationTime);
        printf("%s%f\n","AVGSERVICETIME :=",avgservicetime);
        printf("%s\n","**********************MULTI LINES EVENTS***********************");
        printf("%s\n\n\n","*************KAPIL IS KEEPING RECORDS OF EVERY EVENTS*************");
        initial_arrival(simulationTime,customers,tellers,&EventQueue);
        float avg=execution(&EventQueue,teller,tellers,avgservicetime,simulationTime,0);
        float totalavgspent=avg/customers;
        
        printf("%s%f\n","Total service time is ",avg);
        printf("%s%f\n","avg time spent by a customer in a bank ",totalavgspent);
        printf("%s\n","type of queuing is multilines.");
        //printf("%s\n","");
        printf("\n\n%s\n","*********************ALL EVENTS ARE FINISH*********************");
        printf("\n\n\n");
        printf("%s\n","*********************SINGLE LINE EVENTS***********************");
        printf("%s\n","*************KAPIL KEEPING RECORDS OF EVERY EVENTS*************");
        struct EventQueue* EventQueue1= NULL;
        EventQueue1 = (struct EventQueue*)malloc(sizeof(struct EventQueue));
        struct tellerQueue* tellerQueue= NULL;
        tellerQueue= (struct tellerQueue*)malloc(sizeof(struct tellerQueue));

        initial_arrival(simulationTime,customers,tellers,&EventQueue1);
       
        avg=execution1(&EventQueue1,&tellerQueue,tellers,avgservicetime,simulationTime,0);
        totalavgspent=avg/customers;
        printf("%s%f\n","Total service time is ",avg);
        printf("%s%f\n","avg time spent by a customer in a bank ",totalavgspent);
        printf("\n\n%s\n\n","*********************ALL EVENTS ARE FINISH*********************");
        // doing analysis by drawing graph
        char* commandsForGnuplot[]={"set term pngcairo","set output \"graph.png\"","set title \"Avg. time spent by customers Vs Total no of tellers\"","set xlabel \"(No of tellers) ---->\"","set ylabel \"(Average time spent by customers) ---->\"","plot \"data.txt\" with lines","set terminal png","replot","set output"};
        int noofcommands=9;
        FILE * temp = fopen("data.txt", "w");
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
        for(int i=0;i<10;i++){
                 struct EventQueue* EventQueue2= NULL;
                EventQueue2 = (struct EventQueue*)malloc(sizeof(struct EventQueue));
                struct tellerQueue* tellerQueue1= NULL;
                tellerQueue1= (struct tellerQueue*)malloc(sizeof(struct tellerQueue));

                initial_arrival(simulationTime,customers,(tellers+i),&EventQueue2);
        
                float avg1=execution1(&EventQueue2,&tellerQueue1,(tellers+1),avgservicetime,simulationTime,1);
                float totalavgspent1=avg1/customers;
                 fprintf(temp, "%d %lf\n", tellers+i,totalavgspent1);
        }

       int i;
       for(i=0; i<noofcommands; i++){
	     fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
	}
     fclose(temp);
       

        return 0;
}

