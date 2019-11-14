#include<iostream>
#include<fstream>
#include<string>
#include <stdio.h>
using namespace std;

int row,col,B,step=0,zero_num=0;
string filename="temporary.txt";

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
            return *front;
        }
    private:
        Queuenode *front,*rear;
};

class Stacknode{
    public:
        Stacknode(int i,int j):posi(i),posj(j),next(0),pre(0){};
        void setnext(Stacknode* node){
            if(node!=NULL)
                node->setpre(this);          
            next=node;
        }
        void setpre(Stacknode *node){
            pre=node;
        }
        Stacknode* getnext(){
            return this->next;
        }
        Stacknode* getpre(){
            return this->pre;
        }
        int geti(){
            return posi;
        }
        int getj(){
            return posj;
        }
    private:
        int posi,posj;
        Stacknode* next;
        Stacknode *pre;
};

class Stack{
    public:
        Stack():top(0){};
        bool isempty(){
            return top==NULL;
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
            top = top->getpre();
            delete delenode;
            if(top!=NULL)
                top->setnext(NULL);
        }
        Stacknode gettop(){
            return *top;
        }
    private:
        Stacknode* top;
};

void BFS(int i,int j,vertex** map){
    Queue q;
    q.push(i,j);
    map[i][j].visited=1;
    Queuenode test=q.getfront();
    while(!q.isempty()){
        Queuenode f=q.getfront();
        q.pop();
        i=f.geti();
        j=f.getj();
        //left
        if(j>0&&map[i][j-1].map=='0'){
            if(map[i][j-1].visited==0){
                q.push(i,j-1);
                map[i][j-1].visited=1;
                map[i][j-1].length=map[i][j].length+1;
            }
        }
        //up
        if(i>0&&map[i-1][j].map=='0'){
            if(map[i-1][j].visited==0){
                q.push(i-1,j);
                map[i-1][j].visited=1;
                map[i-1][j].length=map[i][j].length+1;
            }
        }
        //right
        if(j<col-1&&map[i][j+1].map=='0'){
            if(map[i][j+1].visited==0){
                q.push(i,j+1);
                map[i][j+1].visited=1;
                map[i][j+1].length=map[i][j].length+1;
            }
        }
        //down
        if(i<row-1&&map[i+1][j].map=='0'){
            if(map[i+1][j].visited==0){
                q.push(i+1,j);
                map[i+1][j].visited=1;
                map[i+1][j].length=map[i][j].length+1;
            }
        }
    }
}

void path(vertex** map){
    //write to temporary.path
    FILE *outtemp;
    outtemp = fopen("temporary.txt", "a");

    /*ofstream outtem("temporary.path",ios::in|ios::out|ios::app); 
    if (!outtem){
        cout << "can't open temporary.path" << endl;
    }*/
    int length=0,posi,posj,ni,nj,fi,fj,chose=0;
    Stack spath;
    //find the farthest postion
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            if(map[i][j].length>length&&map[i][j].map=='0'){
                length = map[i][j].length;
                posi=i;
                posj=j;
                fi=i;
                fj=j;
            }
    //push the farthest postion to stack        
    spath.push(posi,posj);
    map[posi][posj].map='2';
    zero_num--;    
    //find the path to farthest position
    if(map[posi][posj].length>0){
        for(int i=length-1;i>0;i--){
            chose=0;
            //left
            if(posj>0){
                if(i==map[posi][posj-1].length&&map[posi][posj-1].map!='1'){
                    ni=posi;
                    nj=posj-1;
                    chose=1;
                    if(map[posi][posj-1].map=='0'||map[posi][posj-1].map=='R'){
                        posj=nj;
                        spath.push(ni,nj);
                        if(map[ni][nj].map=='0'){
                            map[ni][nj].map='2';
                            zero_num--;
                        }
                        continue;
                    }
                }
            }
            //right
            if(posj<col-1){
                if(i==map[posi][posj+1].length&&map[posi][posj+1].map!='1'){
                    if(chose==0){
                        ni=posi;
                        nj=posj+1;
                        chose=1;
                        if(map[posi][posj+1].map=='0'||map[posi][posj+1].map=='R'){
                            posj=nj;
                            spath.push(ni,nj);
                            if(map[ni][nj].map=='0'){
                                map[ni][nj].map='2';
                                zero_num--;
                            }    
                            continue;
                        }
                    }
                    else if(map[posi][posj+1].map=='0'||map[posi][posj+1].map=='R'){
                        ni=posi;
                        nj=posj+1;
                        posj=nj;
                        spath.push(ni,nj);
                        if(map[ni][nj].map=='0'){
                            map[ni][nj].map='2';
                            zero_num--;
                        }
                        continue;
                    }
                }
            }
            //up
            if(posi>0){
                if(i==map[posi-1][posj].length&&map[posi-1][posj].map!='1'){
                    if(chose==0){
                        ni=posi-1;
                        nj=posj;
                        chose=1;
                        if(map[posi-1][posj].map=='0'||map[posi-1][posj].map=='R'){
                            posi=ni;
                            spath.push(ni,nj);
                            if(map[ni][nj].map=='0'){
                                map[ni][nj].map='2';
                                zero_num--;
                            } 
                            continue;
                        }
                    }
                    else if(map[posi-1][posj].map=='0'||map[posi-1][posj].map=='R'){
                        ni=posi-1;
                        nj=posj;
                        posi=ni;
                        spath.push(ni,nj);
                        if(map[ni][nj].map=='0'){
                            map[ni][nj].map='2';
                            zero_num--;
                        }
                        continue;
                    }
                }
            }
            //down
            if(posi<row-1){
                if(i==map[posi+1][posj].length&&map[posi+1][posj].map!='1'){
                    if(chose==0){
                        ni=posi+1;
                        nj=posj;
                        chose=1;
                        if(map[posi+1][posj].map=='0'||map[posi+1][posj].map=='R'){
                            posi=ni;
                            spath.push(ni,nj);
                            if(map[ni][nj].map=='0'){
                                map[ni][nj].map='2';
                                zero_num--;
                            } 
                            continue;
                        }
                    }
                    else if(map[posi+1][posj].map=='0'||map[posi+1][posj].map=='R'){
                        ni=posi+1;
                        nj=posj;
                        posi=ni;
                        spath.push(ni,nj);
                        if(map[ni][nj].map=='0'){
                            map[ni][nj].map='2';
                            zero_num--;
                        }
                        continue;
                    }
                }
            }
            posi=ni;
            posj=nj;
            spath.push(ni,nj);
        }
        //print stack
        while(!spath.isempty()){
            Stacknode st=spath.gettop();
            fprintf(outtemp,"%d %d\n",st.geti(),st.getj());
            //outtem<<st.geti()<<" "<<st.getj()<<endl;
            step++;
            spath.pop();
        }
        //find the path from farthest position to R 
        Queue qpath;     
        posi=fi;
        posj=fj;       
        for(int i=length-1;i>=0;i--){
            chose=0;
            //left
            if(posj>0){
                if(i==map[posi][posj-1].length&&map[posi][posj-1].map!='1'){
                    ni=posi;
                    nj=posj-1;
                    chose=1;
                    if(map[posi][posj-1].map=='0'||map[posi][posj-1].map=='R'){
                        posj=nj;
                        qpath.push(ni,nj);
                        if(map[ni][nj].map=='0'){
                            map[ni][nj].map='2';
                            zero_num--;
                        }
                        continue;
                    }
                }
            }
            //right
            if(posj<col-1){
                if(i==map[posi][posj+1].length&&map[posi][posj+1].map!='1'){
                    if(chose==0){
                        ni=posi;
                        nj=posj+1;
                        chose=1;
                        if(map[posi][posj+1].map=='0'||map[posi][posj+1].map=='R'){
                            posj=nj;
                            qpath.push(ni,nj);
                            if(map[ni][nj].map=='0'){
                                map[ni][nj].map='2';
                                zero_num--;
                            }
                            continue;
                        }
                    }
                    else if(map[posi][posj+1].map=='0'||map[posi][posj+1].map=='R'){
                        ni=posi;
                        nj=posj+1;
                        posj=nj;
                        qpath.push(ni,nj);
                        if(map[ni][nj].map=='0'){
                            map[ni][nj].map='2';
                            zero_num--;
                        }
                        continue;
                    }
                }
            }
            //up
            if(posi>0){
                if(i==map[posi-1][posj].length&&map[posi-1][posj].map!='1'){
                    if(chose==0){
                        ni=posi-1;
                        nj=posj;
                        chose=1;
                        if(map[posi-1][posj].map=='0'||map[posi-1][posj].map=='R'){
                            posi=ni;
                            qpath.push(ni,nj);
                            if(map[ni][nj].map=='0'){
                                map[ni][nj].map='2';
                                zero_num--;
                            }
                            continue;
                        }
                    }
                    else if(map[posi-1][posj].map=='0'||map[posi-1][posj].map=='R'){
                        ni=posi-1;
                        nj=posj;
                        posi=ni;
                        qpath.push(ni,nj);
                        if(map[ni][nj].map=='0'){
                            map[ni][nj].map='2';
                            zero_num--;
                        }
                        continue;
                    }
                }
            }
            //down
            if(posi<row-1){
                if(i==map[posi+1][posj].length&&map[posi+1][posj].map!='1'){
                    if(chose==0){
                        ni=posi+1;
                        nj=posj;
                        chose=1;
                        if(map[posi+1][posj].map=='0'||map[posi+1][posj].map=='R'){
                            posi=ni;
                            qpath.push(ni,nj);
                            if(map[ni][nj].map=='0'){
                                map[ni][nj].map='2';
                                zero_num--;
                            }
                            continue;
                        }
                    }
                    else if(map[posi+1][posj].map=='0'||map[posi+1][posj].map=='R'){
                        ni=posi+1;
                        nj=posj;
                        posi=ni;
                        qpath.push(ni,nj);
                        if(map[ni][nj].map=='0'){
                            map[ni][nj].map='2';
                            zero_num--;
                        }
                        continue;
                    }
                }
            }
            posi=ni;
            posj=nj;
            qpath.push(ni,nj);
        }
        //print queue
        while(!qpath.isempty()){
            Queuenode qt=qpath.getfront();
            fprintf(outtemp,"%d %d\n",qt.geti(),qt.getj());
            //outtem<<qt.geti()<<" "<<qt.getj()<<endl;
            step++;
            qpath.pop();
        }
    }
    fclose(outtemp);        
}

int main(){
    vertex **map;
    //read floor.data
    ifstream inF("floor.data", ios::in);
    if (!inF) {
        cout << "can't open floor.data" << endl;
        return 1;
    }

    //write to final.path
    ofstream outF("final.path", ios::out); 
    if (!outF) {
        cout << "can't open final.path" << endl;
        return 1;
    }
    //read temporary.path
    ifstream intem("temporary.txt", ios::in);
    if (!intem) {
        cout << "can't open temporary.txt" << endl;
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
    int ri,rj;               
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
    //organize visited and length of every vertex    
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
    BFS(ri,rj,map);
    while(zero_num!=0){
        path(map);   
    }
    outF<<step<<endl;
    outF<<ri<<" "<<rj<<endl;
    int outputi,outputj;
    for(int i=step;i>0;i--){
        intem>>outputi>>outputj;
        outF<<outputi<<" "<<outputj<<endl;
    }
    inF.close();
    outF.close();
    intem.close();
    remove("temporary.txt");
    return 0;
}