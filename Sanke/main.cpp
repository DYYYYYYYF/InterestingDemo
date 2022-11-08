#include <iostream>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <stdlib.h>

#define SIDESIZE 21

using namespace std;

typedef struct LinkList{
    int x;
    int y;
    LinkList *next;
    LinkList *prep;
    LinkList *tail;
    void init(){
        this->x = -1;
        this->y = -1;
        this->next = NULL;
        this->tail = this;
        this->prep = this->tail;

    }
    LinkList* findTail(){
        if(tail) return tail;
        return NULL;
    }
    bool insertTail(int x, int y){
        LinkList *newNode = new LinkList;
        newNode -> init();
        newNode -> x = x;
        newNode -> y = y;
        newNode -> prep = tail;
        this->tail->next = newNode;
        this->tail = newNode;
        return true;
    }
    bool insertHead(int x, int y){
        
        LinkList *newNode = new LinkList;
        newNode -> x = x;
        newNode -> y = y;
        newNode -> next = next;
        newNode -> prep = this;
        this->next = newNode;
        newNode -> next -> prep = newNode;
        return true;
    }
    int* getVal(){
        int *val = (int *)malloc(sizeof(int) * 2);
        val[0] = this->x;
        val[1] = this->y;
        return val;
    }

    void deleteTail(){
        if(!tail) return;
        LinkList *t = tail;
        tail->prep->next = NULL;
        tail = tail->prep;
        delete t;
    }
}LinkList, *listNode;

/**
 * @brief ?????
 * ??? map
 * 
 */
class Map{
    private:
        int score = 0;
        int speed = 500;
       int* node = (int *)malloc(sizeof(int) * 2);
    public:
        int** map = (int**)malloc(sizeof(int *) * SIDESIZE);
        Map();
        ~Map();
        void showMap();
        void randNode();
        int* getNodeXY();
        int getScore();
        void addScore();
        int getSpeed();
        void changeSpeed();
};
Map::Map(){
    srand((int)time(0));
    for(int i=0 ;i<SIDESIZE; i++){
        map[i] = (int *)malloc(sizeof(int) * SIDESIZE);
    }
    for(int row=0; row<SIDESIZE; row++){
        for(int col=0; col<SIDESIZE; col++){
            if(row == 0 || col == 0 || row == SIDESIZE-1 || col == SIDESIZE-1) map[row][col] = 1;
        }
    }
    randNode();
}
Map::~Map(){}
void Map::showMap(){
 for(int row=0; row<SIDESIZE; row++){
        for(int col=0; col<SIDESIZE; col++){
            if(map[row][col] == 1) cout << "■" ;
            else cout << "  ";
        }
        cout << endl;
    }
}

void Map::randNode(){
    do{
        node[0] = rand() % (SIDESIZE-4) + 2;
        node[1] = rand() % (SIDESIZE-4) + 2;
    }while(map[node[0]][node[1]] == 1);
map[node[0]][node[1]] = 1;

    // if(map[node[0]][node[1]] == 1) node[0] = rand() % (SIDESIZE-2) + 1;

    // map[10][10] = 1;
}

int* Map::getNodeXY(){
    return this->node;
}

int Map::getScore(){
    return this->score;
}

void Map::addScore(){
    this->score++;
}

int Map::getSpeed(){
    return this->speed;
}

void Map::changeSpeed(){
    this->speed -= 10;
}

class Sanke{
    private:
        int direction = 0;  //???????
        Map *map;
        LinkList *body = (LinkList *)malloc(sizeof(LinkList));
    public:
        Sanke(Map *map);
        ~Sanke();
        void setDirection(int dir);
        int move(); //???
        bool addBody(int x, int y); //??????
        bool isLife();
        int getDir(){return this->direction;}
        void eatNode();
};
Sanke::~Sanke(){}
Sanke::Sanke(Map *map){
    this->body->init();
    this->map = map;
}

bool Sanke::addBody(int x, int y){
    bool f = body->insertTail(x, y);
    if(f)  map->map[x][y] = 1;
    return f;
}

int Sanke::move(){
    LinkList *t = this->body->next;
    LinkList *r = this->body->tail;
    int row = t->x;
    int col = t->y;

    map->map[r->x][r->y] = 0;
    this->body->deleteTail();

    eatNode();

    if(t->x-1 > 0 && t->x+1 < SIDESIZE-1 && t->y-1 > 0 && t->y+1 < SIDESIZE-1){
        switch(this->direction){
            case 0: this->body->insertHead(++row,col); map->map[row][col] = 1; break;   //up
            case 1: this->body->insertHead(--row,col); map->map[row][col] = 1; break;   //down
            case 2: this->body->insertHead(row,++col); map->map[row][col] = 1; break;   //right
            case 3: this->body->insertHead(row,--col); map->map[row][col] = 1; break;   //left
            default : this->body->x++;break;
        }
    } else {return -1;}

    

    return this->direction;
}

bool Sanke::isLife(){
    if(!body->next) return false;
    LinkList *t = this->body->next;
    LinkList *o = t->next;
    while(t && o){

        if(o->x == t->x && o->y == t->y) return false;
        o = o->next;
    }
    return body->next->x > 1 && body->next->x < SIDESIZE-2 && body->next->y > 1 && body->next->y < SIDESIZE-2;
}

void Sanke::setDirection(int d){
    this->direction = d;
}

void Sanke::eatNode(){
    int* temp = this->map->getNodeXY();
    if(body->next->x == temp[0] && body->next->y == temp[1]){
        this->map->randNode();
        body->insertHead(body->next->x, body->next->y);
        map->map[body->next->x][body->next->y] = 1;
        this->map->addScore();
        this->map->changeSpeed();
    }
}

int main(){
    Map map;
    Sanke sanke(&map);
    int i = 0;
    char in;

    sanke.addBody(12,12);
    sanke.addBody(12,13);
    sanke.addBody(12,14);
    sanke.addBody(12,15);
    sanke.addBody(12,16);
    sanke.addBody(13,16);

    while(sanke.isLife()){
        if(_kbhit()){
            in = _getch();
            switch((int)in){
                case 72 :{  //down
                    if(sanke.getDir() == 1 || sanke.getDir() == 0) ;
                    else sanke.setDirection(1); break;
                }
                case 75 :{  //left
                    if(sanke.getDir() == 2 || sanke.getDir() == 3) ;
                    else sanke.setDirection(3); break;
                }
                case 77 :{  //right
                    if(sanke.getDir() == 2 || sanke.getDir() == 3) ;
                    else sanke.setDirection(2); break;
                }
                case 80 :{  //up
                    if(sanke.getDir() == 1 || sanke.getDir() == 0) ;
                    else sanke.setDirection(0); break;
                }
                default : break;
            }
        } else {
            cout << "得分：" << map.getScore() << "     速度：" << map.getSpeed() << endl;
            sanke.move();           
            map.showMap();

            Sleep(map.getSpeed());
            system("cls");    
        } 
    }
    cout << "Game Over!" << endl;
    cout << "得分：" << map.getScore() << endl;
 
    getchar();
    return 0;
}