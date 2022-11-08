#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <ctime>
#include <windows.h>
#include <stack>

using namespace std;

//��ͼ�࣬����
class Maze
{
private:
    int edge;
    vector<int> hasCome;
    vector<vector<int>> map;    
    
public:
    Maze(int dege);     //���캯��������ʱִ��
    ~Maze();    //����������ɾ��ʱִ��
    void show();    //��ʾ��ͼ
    void Radom(int row, int col, default_random_engine e);   //���������ͼ
    void Init();
    const vector<int> hasPath(int row, int col);  //�ж���û��ͨ·
    vector<vector<int>> getMap();
};

Maze::~Maze(){}
Maze::Maze(int edge){
    if(edge%2 == 0) edge++;
    this->edge = edge;
    
    //��ʼ��vector��������ά��ʼ��
    this->map.resize(edge);
    for(int i=0; i<edge; i++){
        this->map[i].resize(edge);
    }

    //��ʼ����ͼ��ȫΪǽ
    for(int i=0; i<edge; i++){
        for(int j=0; j<edge; j++){
            if(i==0 || i==edge-1 || j==0 || j==edge-1) map[i][j] = 1;
            else{
                if(i%2==0 || j%2==0) map[i][j] = 1;
                else map[i][j] = 0;
            }
        }
    }
}

void Maze::Init(){
    for(int i=0; i<edge; i++){
        for(int j=0; j<edge; j++){
            if(map[i][j] == 2) map[i][j] =0;
        }
    }
}

void Maze::show(){
    system("cls");

    for(int i=0; i<this->edge; i++){
        for(int j=0; j<this->edge; j++){
            if(this->map[i][j] == 1) cout << "��" ;
            else if(map[i][j] == 2) cout << "��";
            else cout << "  ";
        }
        cout << endl;
    }
}

void Maze::Radom(int row, int col, default_random_engine e){

    if(row < 1 || row > edge-1 || col < 1 || col > edge-1) return;
    
    vector<int> path = Maze::hasPath(row,col);

    if(path.size() == 0) return;
    uniform_int_distribution<int> u(0,path.size());

    for(int i=0; i<path.size();){
        int index = u(e)%path.size();
        switch(path[index]){
            case 1:     //��
                if(map[row+2][col] != 2){
                    map[row+1][col] = 2;
                    map[row+2][col] = 2;
                    Radom(row+2, col, e);
                }
                break;    
            case 2:     //��
                if(map[row-2][col] != 2){
                    map[row-1][col] = 2;
                    map[row-2][col] = 2;
                    Radom(row-2, col, e);
                }
                break;
            case 3:     //��
                if(map[row][col+2] != 2){
                    map[row][col+1] = 2;
                    map[row][col+2] = 2;
                    Radom(row, col+2, e);
                }
                break; 
            case 4:     //��
                if(map[row][col-2] != 2){
                    map[row][col-1] = 2;
                    map[row][col-2] = 2;
                    Radom(row, col-2, e);
                }
                break; 
        }
        path.erase(path.begin()+index);
    }
}

const vector<int> Maze::hasPath(int row, int col){
    vector<int> t;;
    if(row-2 >0 && map[row-2][col] == 0) t.push_back(2);
    if(row+2 <edge && map[row+2][col] == 0) t.push_back(1);
    if(col-2 >0 && map[row][col-2] == 0) t.push_back(4);
    if(col+2 <edge && map[row][col+2] == 0) t.push_back(3);
    return t;
}

vector<vector<int>> Maze::getMap(){
    return this->map;
}


//�����
class Player
{
private:
    bool isEnd = false;
    int edge;
    vector<vector<int>> maze;
    stack<vector<int>> node;
public:
    Player(vector<vector<int>> mazeMap, int e);
    ~Player();
    void findOut();     //Ѱ�ҳ���
    void Show();
};

Player::~Player(){}
Player::Player(vector<vector<int>> mazeMap, int e){
    this->maze = mazeMap;
    if(e%2 == 0){
        e++;
    }
    this->edge = e;
}

void Player::Show(){
    system("cls");

    for(int i=0; i<this->edge; i++){
        for(int j=0; j<this->edge; j++){
            if(this->maze[i][j] == 1) cout << "��" ;
            else if(maze[i][j] == 2) cout << "��";
            else cout << "  ";
        }
        cout << endl;
    }
}

void Player::findOut(){
    int row = 1, col = 1;
    vector<int> coordinate;
    coordinate.push_back(row);
    coordinate.push_back(col);
    maze[row][col] = 2;
    node.push(coordinate);

    while(!node.empty() && !isEnd){
        vector<int> cur = node.top();
        row = cur[0]; col = cur[1];
        
        if(row == edge-2 && col == edge-2){
            maze[row][col] = 2;
             isEnd = true;
        } else if(row+1 < edge && maze[row+1][col] == 0){
            coordinate[0] = row+1;
            coordinate[1] = col;
            node.push(coordinate);
            maze[row+1][col] = 2;
            Show();
            Sleep(1000);
        } else if(col+1 < edge && maze[row][col+1] == 0){
            coordinate[0] = row;
            coordinate[1] = col+1;
            node.push(coordinate);
            maze[row][col+1] = 2;
            Show();
            Sleep(1000);
        } else if(col-1 > 0 && maze[row][col-1] == 0){
            coordinate[0] = row;
            coordinate[1] = col-1;
            node.push(coordinate);
            maze[row][col-1] = 2;
            Show();
            Sleep(1000);
        } else if(row-1 > 0 && maze[row-1][col] == 0){
            coordinate[0] = row-1;
            coordinate[1] = col;
            node.push(coordinate);
            maze[row-1][col] = 2;
            Show();
            Sleep(1000);
        } else {
            maze[row][col] = 3;
            node.pop();
        }
    }
}

/**
 * @brief 
 * Main()������������
 * @return int 
 */
int main(){
    default_random_engine e;    //���������
    e.seed(time(0));

    cout << "������ĵ�ͼ(0-50) ?";
    int x;
    cin >> x;
    Maze maze(x);   //��ͼ��
    

    maze.Radom(1,1,e);  //������ɵ�ͼ
    maze.Init();
    maze.show();    //չʾ��ͼ

    getchar();  //����س�
    cout << "����Ϊ������ɵ�ͼ���������Ѱ�ҳ��ڡ�" << endl;
    getchar();

    Player user(maze.getMap(),x);  //�����
    user.findOut();
    user.Show();

    cout << "���������������������˳�" << endl;
    getchar();

    return 0;
}
