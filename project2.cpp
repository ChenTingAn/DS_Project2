#include<iostream>
#include<fstream>
using namespace std;
int row,col,B;

class vertex{
    public:
        char map;
        int visited;
        int length;
};

class Queuenode{
    public:
        Queuenode(int i,int j):posi(i),posj(j),next(0){};
        void setnext(Queuenode* node){
            next=node;
        }
        Queuenode* getnext(){
            return this->next;
        }
        int geti(){
            return posi;
        }
        int getj(){
            return posj;
        }
    private:
        int posi,posj;
        Queuenode* next; 
};

class Queue{
    public:
        Queue():front(0),rear(0){};
        bool isempty(){
            return (front==NULL&&rear==NULL);
        }
        void push(int i,int j){
            if(isempty()){
                front = new Queuenode(i,j);
                rear = front;
                return;
            }
            Queuenode *newnode=new Queuenode(i,j);
            rear->setnext(newnode);
            rear=newnode;
        }
        void pop(){
            if(isempty())   return;
            Queuenode *delenode=front;
            front=front->getnext();
            if(front==NULL)
            rear=NULL;
            delete delenode;
        }
        Queuenode getfront(){
            if(isempty()) return ;
            return *front;
        }
    private:
        Queuenode *front,*rear;
};

class Stacknode{
    public:
        Stacknode(int i,int j):posi(i),posj(j),next(0){};
        void setnext(Stacknode* node){
            next=node;
        }
        Stacknode* getnext(){
            return this->next;
        }
    private:
        int posi,posj;
        Stacknode* next;
};

class Stack{
    public:
        Stack():top(0){};
        bool isempty(){
            return (top==NULL);
        }
        void push(int i,int j){
            if(isempty()){
                top = new Stacknode(i,j);
                return;
            }
            Stacknode *newnode=new Stacknode(i,j);
            top->setnext(newnode);
            top=newnode;
        }
        void pop(){
            if(isempty())   return;
            Stacknode *delenode = top;
            top = top->getnext();
            delete delenode;
        }
        Stacknode gettop(){
            if(isempty()) return ;
            return *top;
        }
    private:
        Stacknode* top;
};

void BFS(int i,int j,vertex** map){
    Queue q;
    q.push(i,j);
    map[i][j].visited=1;
    while(!q.isempty()){
        Queuenode f=q.getfront();
        q.pop();
        i=f.geti();
        j=f.getj();
        if(i>0&&map[i-1][j].map==0){
            if(map[i-1][j].visited==0){
                q.push(i-1,j);
                map[i-1][j].visited=1;
                map[i-1][j].length=map[i][j].length+1;
            }
        }
        if(j>0&&map[i][j-1].map==0){
            if(map[i][j-1].visited==0){
                q.push(i,j-1);
                map[i][j-1].visited=1;
                map[i][j-1].length=map[i][j].length+1;
            }
        }
        if(i<col-1&&map[i+1][j].map==0){
            if(map[i+1][j].visited==0){
                q.push(i+1,j);
                map[i+1][j].visited=1;
                map[i+1][j].length=map[i][j].length+1;
            }
        }
        if(j<row-1&&map[i][j+1].map==0){
            if(map[i][j+1].visited==0){
                q.push(i,j+1);
                map[i][j+1].visited=1;
                map[i][j+1].length=map[i][j].length+1;
            }
        }
    }
}

//reorganize the data of visited and length
void reorganize(vertex** map){
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++){
            if(map[i][j].map=='1'){
                map[i][j].visited=-1;
                map[i][j].length=-1;
            }    
            else{
                map[i][j].visited=0;
                map[i][j].length=0;
            }    
        }
}

int main(){
    vertex **map;
    //read
    ifstream inF("floor.data", ios::in);
    if (!inF) {
        cout << "can't open floor.data" << endl;
        return 1;
    }
    //write
    ofstream outF("final.path", ios::out); 
    if (!outF) {
        cout << "can't open final.path" << endl;
        return 1;
    }
    //cin>>row>>col>>B
    inF>>row>>col>>B;
    //create a map                    
    map=new vertex*[row];                 
    for(int i=0;i<row;i++)              
        map[i]=new vertex[col];
    //cin>>map
    for(int i=0;i<row;i++)              
        for(int j=0;j<col;j++)
            inF>>map[i][j].map;
    //find R and the number of zero    
    int ri,rj,zero_num=0;               
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++){
            if(map[i][j].map=='R'){
                ri=i;
                rj=j;
            }
            if(map[i][j].map=='0'){
                zero_num++;
            }
        }
    reorganize(map);
    BFS(ri,rj,map);    
    return 0;
}