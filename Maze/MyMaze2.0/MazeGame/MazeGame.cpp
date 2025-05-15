#include "MazeGame.h"

using namespace std;

#define DelayTime 500   // ms

const char* UnitContentIcon[] = { "  ",  "■" , "□", "  ", "++"};

enum class UnitContent {
    eWall = 0,
    eRoad = 1,
    ePassed = 2,
    eStart = 3,
    eEnd = 4
};

enum class Direction {
    eDown = 1,
    eUp = 2,
    eRight = 3,
    eLeft = 4
};

//地图类，矩阵
class Maze
{
private:
    int edge;
    vector<int> hasCome;
    vector<vector<int>> map;

public:
    Maze(int dege);     //构造函数：创建时执行
    ~Maze();    //析构函数：删除时执行
    void show();    //显示地图
    void Radom(int row, int col, default_random_engine e);   //随机生产地图
    void Init(int start_row = -1, int start_col = -1, int target_row = -1, int target_col = -1);
    const vector<Direction> hasPath(int row, int col);  //判断有没有通路
    vector<vector<int>> getMap();
};

Maze::~Maze() {}
Maze::Maze(int edge) {
    if (edge % 2 == 0) edge++;
    this->edge = edge;

    //初始化vector容器，二维初始化
    this->map.resize(edge);
    for (int i = 0; i < edge; i++) {
        this->map[i].resize(edge);
    }

    //初始化地图，全为墙
    for (int i = 0; i < edge; i++) {
        for (int j = 0; j < edge; j++) {
            if (i == 0 || i == edge - 1 || j == 0 || j == edge - 1) map[i][j] = 1;
            else {
                if (i % 2 == 0 || j % 2 == 0) map[i][j] = 1;
                else map[i][j] = 0;
            }
        }
    }
}

void Maze::Init(int start_row, int start_col, int target_row, int target_col) {
    for (int i = 0; i < edge; i++) {
        for (int j = 0; j < edge; j++) {
            if (map[i][j] == 2) map[i][j] = 0;
        }
    }

    start_row = start_row == -1 ? 1 : start_row;
	clamp(start_row, 1, edge - 1);

    start_col = start_col == -1 ? 1 : start_col;
	clamp(start_col, 1, edge - 1);

    target_row = target_row == -1 ? edge - 2 : target_row;
	clamp(target_row, 1, edge - 1);

    target_col = target_col == -1 ? edge - 2 : target_col;
	clamp(target_col, 1, edge - 1);

    map[start_row][start_col] = static_cast<int>(UnitContent::eStart);
    map[target_row][target_col] = static_cast<int>(UnitContent::eEnd);
}

void Maze::show() {
    system("cls");

    for (int i = 0; i < this->edge; i++) {
        for (int j = 0; j < this->edge; j++) {
            if (this->map[i][j] == 1) cout << UnitContentIcon[1];
            else if (map[i][j] == 2) cout << UnitContentIcon[2];
            else if (map[i][j] == 3) cout << UnitContentIcon[3];
            else if (map[i][j] == 4) cout << UnitContentIcon[4];
            else cout << UnitContentIcon[0];
        }
        cout << endl;
    }
}

void Maze::Radom(int row, int col, default_random_engine e) {

    if (row < 1 || row > edge - 1 || col < 1 || col > edge - 1) return;

    vector<Direction> path = Maze::hasPath(row, col);

    if (path.size() == 0) return;
    uniform_int_distribution<int> u(0, path.size());

    for (int i = 0; i < path.size();) {
        int index = u(e) % path.size();
        switch (path[index]) {
        case Direction::eDown:     //下
            if (map[row + 2][col] != 2) {
                map[row + 1][col] = 2;
                map[row + 2][col] = 2;
                Radom(row + 2, col, e);
            }
            break;
        case Direction::eUp:     //上
            if (map[row - 2][col] != 2) {
                map[row - 1][col] = 2;
                map[row - 2][col] = 2;
                Radom(row - 2, col, e);
            }
            break;
        case Direction::eRight:     //右
            if (map[row][col + 2] != 2) {
                map[row][col + 1] = 2;
                map[row][col + 2] = 2;
                Radom(row, col + 2, e);
            }
            break;
        case Direction::eLeft:     //左
            if (map[row][col - 2] != 2) {
                map[row][col - 1] = 2;
                map[row][col - 2] = 2;
                Radom(row, col - 2, e);
            }
            break;
        }
        path.erase(path.begin() + index);
    }
}

const vector<Direction> Maze::hasPath(int row, int col) {
    vector<Direction> t;;
    if (row - 2 > 0 && map[row - 2][col] == 0) t.push_back(Direction::eUp);
    if (row + 2 < edge && map[row + 2][col] == 0) t.push_back(Direction::eDown);
    if (col - 2 > 0 && map[row][col - 2] == 0) t.push_back(Direction::eLeft);
    if (col + 2 < edge && map[row][col + 2] == 0) t.push_back(Direction::eRight);
    return t;
}

vector<vector<int>> Maze::getMap() {
    return this->map;
}


//玩家类
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
    void findOut();     //寻找出口
    void Show();
};

Player::~Player() {}
Player::Player(vector<vector<int>> mazeMap, int e) {
    this->maze = mazeMap;
    if (e % 2 == 0) {
        e++;
    }
    this->edge = e;
}

void Player::Show() {
    system("cls");

    for (int i = 0; i < this->edge; i++) {
        for (int j = 0; j < this->edge; j++) {
            if (this->maze[i][j] == 1) cout << UnitContentIcon[1];
            else if (maze[i][j] == 2) cout << UnitContentIcon[2];
            else if (maze[i][j] == 3) cout << UnitContentIcon[3];
            else if (maze[i][j] == 4) cout << UnitContentIcon[4];
            else cout << UnitContentIcon[0];
        }
        cout << endl;
    }
}

void Player::findOut() {
    int row = 1, col = 1;
    vector<int> coordinate;
    coordinate.push_back(row);
    coordinate.push_back(col);
    maze[row][col] = 2;
    node.push(coordinate);

    while (!node.empty() && !isEnd) {
        vector<int> cur = node.top();
        row = cur[0]; col = cur[1];

        if (row + 1 < edge) {
			if (maze[row + 1][col] == 0) {
				coordinate[0] = row + 1;
				coordinate[1] = col;
				node.push(coordinate);
				maze[coordinate[0]][coordinate[1]] = 2;
				Show();
				Sleep(DelayTime);
				continue;
			}
			else if (maze[row + 1][col] == 4) {
				isEnd = true;
				break;
			}
		}
        if (col + 1 < edge) {
			if (maze[row][col + 1] == 0) {
				coordinate[0] = row;
				coordinate[1] = col + 1;
				node.push(coordinate);
				maze[coordinate[0]][coordinate[1]] = 2;
				Show();
				Sleep(DelayTime);
				continue;
			}
			else if (maze[row][col + 1] == 4) {
				isEnd = true;
				break;
			}
		}
        if (col - 1 > 0) {
			if (maze[row][col - 1] == 0) {
				coordinate[0] = row;
				coordinate[1] = col - 1;
				node.push(coordinate);
				maze[coordinate[0]][coordinate[1]] = 2;
				Show();
				Sleep(DelayTime);
				continue;
			}
			else if (maze[row][col - 1] == 4) {
				isEnd = true;
				break;
			}
		}
        if (row - 1 > 0) {
			if (maze[row - 1][col] == 0) {
				coordinate[0] = row - 1;
				coordinate[1] = col;
				node.push(coordinate);
				maze[coordinate[0]][coordinate[1]] = 2;
				Show();
				Sleep(DelayTime);
				continue;
			}
			else if (maze[row - 1][col] == 4) {
				isEnd = true;
				break;
			}
		}

		maze[row][col] = 3;
		node.pop();
    }
}

/**
 * @brief
 * Main()函数，主函数
 * @return int
 */
int main() {
    default_random_engine e;    //随机数引擎
    e.seed(time(0));

    cout << "建造多大的地图(3-15) ?";
    int x;
    cin >> x;
    x = max(3, x);
    x = min(15, x);
    Maze maze(x);   //地图类


    maze.Radom(1, 1, e);  //随机生成地图
    maze.Init();
    maze.show();    //展示地图

    getchar();  //清除回车
    cout << "以上为随机生成地图，按任意键寻找出口。" << endl;
    getchar();

    Player user(maze.getMap(), x);  //玩家类
    user.findOut();
    user.Show();

    cout << "已完成搜索，输入任意键退出" << endl;
    getchar();

    return 0;
}
