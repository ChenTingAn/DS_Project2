#include<iostream>
#include<fstream>
using namespace std;

class Queuenode{
    public:
        Queuenode(int i,int j):posi(i),posj(j),length(0),next(0){};
        void setnext(Queuenode* node){
            next=node;
        }
        Queuenode* getnext(){
            return this->next;
        }
    private:
        int posi,posj,length;
        Queuenode* next; 
};

class Queue{
    public:
        Queue():front(0),rear(0){};
        bool isempty();
        void push(int i,int j);
        void pop();
        Queuenode getfront();
    private:
        Queuenode *front,*rear;
};

bool Queue::isempty(){
    return (front==NULL&&rear==NULL);
}

void Queue::push(int i,int j){
    if(isempty()){
        front = new Queuenode(i,j);
        rear = front;
        return;
    }
    Queuenode *newnode=new Queuenode(i,j);
    rear->setnext(newnode);
    rear=newnode;
}

void Queue::pop(){
    if(isempty())   return;
    Queuenode *delenode=front;
    front=front->getnext();
    if(front==NULL)
        rear=NULL;
    delete delenode;
}

Queuenode Queue::getfront(){
    if(isempty()) return ;
    return *front;
}


int main(){
    int row,col,B;
    char **map,**visited;
    //read
    ifstream inF("floor.data", ios::in);
    if (!inF) {
        cout << "can't open floor.data" << endl;
        return 1;
    }
    //cin>>row>>col>>B
    inF>>row>>col>>B;
    //create a map                    
    map=new char*[row];                 
    for(int i=0;i<row;i++)              
        map[i]=new char[col];
    //create a visited array     
    visited=new char*[row];             
    for(int i=0;i<row;i++)              
        visited[i]=new char[col];
    //cin>>map
    for(int i=0;i<row;i++)              
        for(int j=0;j<col;j++)
            inF>>map[i][j];
    //find R and the number of zero and copy data from map to visited    
    int ri,rj,zero_num=0;               
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++){
            visited[i][j]=map[i][j];
            if(map[i][j]=='R'){
                ri=i;
                rj=j;
            }
            if(map[i][j]=='0'){
                zero_num++;
            }
        }
    return 0;
}