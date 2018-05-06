#pragma once

#include<iostream>
#include<fstream>
#include<string>

#include<queue>
#include<vector>

using namespace std;

#include<cmath>

class ViTri //Vị Trí gồm vị trí dòng và cột
{
public:
	int x, y;
	ViTri()
	{
		x = -1; y = -1;
	}
	ViTri(int i, int j)
	{
		x = i; y = j;
	}
	void nhap(int i, int j)
	{
		x = i; y = j;
	}
	void xuat()
	{
		cout << x << "," << y<<"     ";
	}
};

class node//Add vào trong PQ

{

public:

	ViTri vt;//Tọa độ của PacMan

	int g;//Chi phí thực sự = số bước đi của pacman tới thời điểm hiện tại

	float f;//Chi phí bao gồm G + H //Chi phí thực sự + ước lượng
	node(ViTri _vt,int _g, float _f)
	{
		vt.nhap(_vt.x, _vt.y);
		g = _g;
		f = _f;
	}
};

struct cmp

{
	bool operator() (const node& i, const node&j) const
	{
		return i.f > j.f;
	}
};

class AStar
{
	//Tham khảo https://stackoverflow.com/
	priority_queue<node, vector<node>, cmp> pq;
	//Kết thức tham khảo
	vector<string> a;//Ma trận kề lưu trữ các ky tu

	int** L;//Nhãn đánh dấu node đã vào stack chưa

	ViTri** Path;//Lưu lại đường đi đã đi tới nó

	float** KC;//LLưu Khoảng cách (f)ngắn nhất từ S tới điểm đó

	
public:
	ViTri P, G;//Vị Trí PacMan,Điểm thức ăn
	int n, m;//So đỉnh, số cạnh
	static char ma, tuong,end,start;//Là con ma hoặc là tường, ký tự tượng trưng cho thức ăn và Pacman
	AStar();
	void khoiTao();

	void docFile(ifstream& in);

	char** xuatFile(ofstream&out);

	void AStar_Algorithm();


	float kc2Diem(int x1, int y1, int x2, int y2);

	~AStar();

};


