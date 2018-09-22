#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <sstream>
#include <algorithm>
#include <functional>
#include <list>
#include <map>
using namespace std;
#if 1
//Dijkstra算法的代码实现（c++）

int g[][6] =
{
	{ 0, INT_MAX, 10, INT_MAX, 30, 100 },
	{ INT_MAX, 0, 5, INT_MAX, INT_MAX, INT_MAX },
	{ INT_MAX, INT_MAX, 0, 50, INT_MAX, INT_MAX },
	{ INT_MAX, INT_MAX, INT_MAX, 0, INT_MAX, 10 },
	{ INT_MAX, INT_MAX, INT_MAX, 20, 0, 60 },
	{ INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0 },
};

//记录起点到每个点的最短路径信息
struct Dis
{
	string path;
	int value;
	bool visit;
	Dis()
	{
		path = "";
		value = 0;
		visit = false;
	}
};

class Graph_dj
{
public:
	int vexnum; //顶点个数
	int edge; //边个数
	int **arc; //邻接矩阵
	Dis* dis; //各个顶点的最短路径信息
public:
	Graph_dj(int vexnum, int ege);
	~Graph_dj();

	//bool check_ege_value(int start, int end, int value);
	//void createGraph();
	void print();
	void Dijkstra(int begin);
	void print_path(int begin);

};

Graph_dj::Graph_dj(int vexnum, int ege)
{
	vexnum = 6;//for test
	ege = 8;
	this->vexnum = vexnum;
	this->edge = ege;
	//arc = g;
	dis = new Dis[vexnum];
	arc = new int*[vexnum];
	for (int i = 0; i < vexnum; i++)
	{
		arc[i] = new int[vexnum];
		for (int j = 0; j < vexnum; j++)
		{
			arc[i][j] = g[i][j];
		}
	}
}
Graph_dj::~Graph_dj()
{
	delete dis;
	for (int i = 0; i < vexnum; i++)
	{
		delete arc[i];
	}
	delete arc;
}

void Graph_dj::print()
{
	cout << "图：" << endl;
	for (int i = 0; i < vexnum; i++)
	{
		for (int j = 0; j < vexnum; j++)
		{
			if (arc[i][j] == INT_MAX)
				cout << "∞" << '\t';
			else
				cout << arc[i][j] << '\t';
		}
		cout << endl;
	}
}

void Graph_dj::print_path(int begin)
{
	cout << "以V1为起点的图的最短路径：" << endl;
	for (int i = 0; i < vexnum; i++)
	{
		if (dis[i].value != INT_MAX)
		{
			cout << dis[i].path << " = " << dis[i].value << endl;
		}
		else
			cout << dis[i].path << " 不通 " << endl;
	}
}


void Graph_dj::Dijkstra(int begin)
{
	for (int i = 0; i < vexnum; i++)
	{
		dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = arc[begin - 1][i];
	}
	dis[begin - 1].value = 0;
	dis[begin = 1].visit = true;

	int count = 1;
	//计算剩下的顶点的最短路径 vexnum - 1个
	while (count < vexnum)
	{
		int tindex = 0;
		int min = INT_MAX;
		//找 最小的值
		for (int i = 0; i < vexnum; i++)
		{
			if (!dis[i].visit && dis[i].value < min)
			{
				min = dis[i].value;
				tindex = i;
			}
		}
		//将最小的值 设置为已访问完毕
		dis[tindex].visit = true;
		++count;
		//刷新最小的值 所关联的 点dis
		for (int i = 0; i < vexnum; i++)
		{
			if (arc[tindex][i] != INT_MAX && !dis[i].visit && dis[tindex].value + arc[tindex][i] < dis[i].value)
			{
				dis[i].value = dis[tindex].value + arc[tindex][i];
				dis[i].path = dis[tindex].path + "-->V" + to_string(i + 1);
			}
		}
	}
}

int main()
{
	Graph_dj dj(6, 8);
	dj.print();
	dj.Dijkstra(1);
	dj.print_path(1);

	return 0;
}
#endif

#if 0
//A* 算法
const int cost1 = 10; //直移动距离
const int cost2 = 14; //斜着移动距离

struct Point
{
	int x, y;
	int F, G, H;
	Point* parent;
	Point(int _x, int _y): x(_x), y(_y), F(0), G(0), H(0), parent(NULL)
	{
	}
};

class Astar
{
public :
	void initStar(vector< vector<int> > &_maze);
	list<Point*> getPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner);
private:
	Point* findPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner);
	vector<Point*> getSurroundPoints(const Point* point, bool isIgnoreCore) const;
	bool isCanReach(const Point* point, const Point* target, bool isIgnoreCore) const;
	Point* isInList(const list<Point*> &list, const Point* point) const;
	Point* getLeastPoint();

	int calcG(Point* temp_start, Point* point);
	int calcH(Point* point, Point* end);
	int calcF(Point* point);

private:
	vector<vector<int>> maze;
	list<Point*> openList;   //开启列表
	list<Point*> closeList;  //关闭列表
};

void Astar::initStar(vector< vector<int> > &_maze)
{
	maze = _maze;
}

int Astar::calcG(Point* temp_start, Point* point)
{
	int extraG = (abs(temp_start->x - point->x) + abs(temp_start->y - point->y) == 1) ? cost1 : cost2;
	int fatherG = point->parent == NULL ? 0 : point->parent->G;

	return extraG + fatherG;
}
int Astar::calcH(Point* point, Point* end)
{
	return (int)(sqrt(pow(end->x - point->x, 2) + pow(end->y - point->y, 2)) * cost1);

}
int Astar::calcF(Point* point)
{
	return point->G + point->H;
}

Point* Astar::getLeastPoint()
{
	if (!openList.empty())
	{
		Point* p = openList.front();
		for (list<Point*>::iterator it = openList.begin(); it != openList.end(); it++)
		{
			if (p->F > (*it)->F)
			{
				p = *it;
			}
		}
		return p;
	}
	return NULL;
}

Point *Astar::findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner)
{
	//begin 
	openList.push_back(new Point(startPoint.x, startPoint.y));
	while (!openList.empty())
	{
		Point* curPoint = getLeastPoint();
		openList.remove(curPoint);
		closeList.push_back(curPoint);

		auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
		for (auto &target : surroundPoints)
		{
			//如果节点不在开放列表里， 放进去
			if (!isInList(openList, target))
			{
				target->parent = curPoint;
				target->G = calcG(curPoint, target);
				target->H = calcH(target, &endPoint);
				target->F = calcF(target);

				openList.push_back(target);
			}//如果节点在开放列表里， 计算G值， 判断是否需要修改
			else
			{
				int tempG = calcG(curPoint, target);
				if (tempG < target->G)
				{
					target->parent = curPoint;
					target->G = tempG;
					target->F = calcF(target);
				}
			}

			//是否找到终点
			Point* resPoint = isInList(openList, &endPoint);
			if (resPoint != NULL)
			{
				return resPoint;
			}
		}
	}
	return NULL;
}

Point* Astar::isInList(const list<Point*> &list, const Point* point) const
{
	for (auto p : list)
	{
		if (p->x == point->x && p->y == point->y)
			return p;
	}
	return NULL;
}


bool Astar::isCanReach(const Point* point, const Point* target, bool isIgnoreCore) const
{
	if (target->x<0 || target->x > maze.size() - 1
		|| target->y<0 || target->y>maze[0].size() - 1
		|| maze[target->x][target->y] == 1
		|| target->x == point->x&&target->y == point->y
		|| isInList(closeList, target)) //如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false
		return false;

	if (abs(point->x - target->x) + abs(point->y - target->y) == 1)
	{
		return true;
	}
	else if (maze[point->x][target->y] == 0 && maze[target->x][point->y] == 0)
	{
		return true;
	}
	else
		return isIgnoreCore;
}

vector<Point*> Astar::getSurroundPoints(const Point* point, bool isIgnoreCore) const
{
	vector<Point *> surroundPoints;
	for (int i = point->x - 1; i <= point->x + 1; i++)
	{
		for (int j = point->y - 1; j <= point->y + 1; j++)
		{
			if (isCanReach(point, new Point(i, j), isIgnoreCore))
			{
				surroundPoints.push_back(new Point(i, j));
			}
		}
	}
	return surroundPoints;
}

list<Point*> Astar::getPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner)
{
	Point* result = findPath(startPoint, endPoint, isIgnoreCorner);
	list<Point*> path;
	while (result)
	{
		path.push_back(result);
		result = result->parent;
	}
	openList.clear();
	closeList.clear();

	return path;
}


int main()
{
	//初始化地图，用二维矩阵代表地图，1表示障碍物，0表示可通
	vector<vector<int>> maze = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1 },
		{ 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	Astar astar;
	astar.initStar(maze);

	//设置起始和结束点
	Point start(1, 1);
	//Point end(6, 10);
	Point end(3, 3);
	//A*算法找寻路径
	list<Point *> path = astar.getPath(start, end, true);
	//打印
	for (auto &p : path)
		cout << '(' << p->x << ',' << p->y << ')' << endl;

	system("pause");
	return 0;
}
#endif
