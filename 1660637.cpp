// 1660637.cpp : Defines the entry point for the console application.
//
#include<ctime>
#include "stdafx.h"
#include"AStar.h"
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>

static HWND consoleHandle;
AStar A;

//Khai báo cho phần code giao diện
void DrawGraph();
int DrawCircle(HWND, ViTri, int, int = 0, int = 0, HDC = 0);
void drawMap(char**, int, int, HWND);

int main(int soPT,char*a[])
{
	/*ifstream in("input.txt");
	ofstream out("output.txt");*/

	ifstream in(a[1]);
	ofstream out(a[2]);
	if (soPT != 3)
	{
		cout << "Khong du tham so\n";
		return 0;
	}

	A.docFile(in);
	A.AStar_Algorithm();
	char** kq = A.xuatFile(out);
	if (kq == NULL)
	{
		cout << -1;
		return 0;
	}

	consoleHandle = GetConsoleWindow();
	
	if (consoleHandle) {
		thread t(DrawGraph);

		ViTri vt = A.P;

		do 
		{
			//system("cls");
			drawMap(kq, A.n, A.m, consoleHandle);
			this_thread::sleep_for(chrono::duration<double, std::milli>(200.0));
			

			if (vt.y < A.m && kq[vt.x][vt.y +1] == 'O')
			{
				kq[vt.x][vt.y] = 'X';
				kq[vt.x][vt.y + 1] = 'P';
				vt.nhap(vt.x, vt.y + 1);
			}

			else if (vt.y > 0 && kq[vt.x][vt.y - 1] == 'O')
			{
				kq[vt.x][vt.y] = 'X';
				kq[vt.x][vt.y - 1] = 'P';
				vt.nhap(vt.x, vt.y - 1);
			}

			else if (vt.x > 0  && kq[vt.x-1][vt.y] == 'O')
			{
				kq[vt.x][vt.y] = 'X';
				kq[vt.x-1][vt.y] = 'P';
				vt.nhap(vt.x - 1, vt.y);
			}
			else if (vt.x < A.m && kq[vt.x + 1][vt.y] == 'O')
			{
				kq[vt.x][vt.y] = 'X';
				kq[vt.x+1][vt.y] = 'P';
				vt.nhap(vt.x + 1, vt.y);
			}
			else {
				break;

			}
		} while ((vt.x != A.G.x || vt.y != A.G.y));
		t.join();
	}
	

	
	for (int i = 0; i < A.n; i++)
		delete kq[i];
	delete kq;
	
	out.close();
    return 0;
}

//Các hàm của GUI

void DrawGraph() {

	//DrawCircle(consoleHandle, ViTri(0, 0), 10, RGB(i * 5, i * 15, 255), RGB(206, 255, 0));
}
//Bat dau tham khao source code cua thay
// Vẽ hình tròn C(center, radius)
int DrawCircle(HWND windowHandle, ViTri center, int radius, int color, int fillColor, HDC deviceContext) {
	int a, b = 0;
	// Tạo device context
	if (!deviceContext) deviceContext = GetDC(windowHandle), b = 1;
	// Tạo pen mới với màu yêu cầu
	HPEN newPen = CreatePen(PS_SOLID, 2, color);
	// Chọn pen mới và lưu lại pen cũ
	HPEN oldPen = (HPEN)SelectObject(deviceContext, newPen);
	HBRUSH oldBrush;
	HBRUSH newBrush;

	// Trong trường hợp yêu cầu tô màu cho hình tròn
	if (fillColor) {
		newBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(deviceContext, newBrush);
	}
	else {
		newBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(deviceContext, newBrush);
	}
	// Vẽ hình tròn
	a = Ellipse(deviceContext, center.x - radius, center.y + radius, center.x + radius, center.y - radius);

	// Chọn lại pen cũ
	DeleteObject(SelectObject(deviceContext, oldPen));
	DeleteObject(SelectObject(deviceContext, oldBrush));

	// Giải phóng device context
	if (b) ReleaseDC(windowHandle, deviceContext);
	return a;
}
//ket thuc tham khao 

int drawRec(HWND windowHandle, int left, int top, int right, int bottom, int color, int fillColor, HDC deviceContext = NULL)
{
	int a, b = 0;
	// Tạo device context
	if (!deviceContext) deviceContext = GetDC(windowHandle), b = 1;
	// Tạo pen mới với màu yêu cầu
	HPEN newPen = CreatePen(PS_SOLID, 2, color);
	// Chọn pen mới và lưu lại pen cũ
	HPEN oldPen = (HPEN)SelectObject(deviceContext, newPen);
	HBRUSH oldBrush;
	HBRUSH newBrush;

	if (fillColor) {
		newBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(deviceContext, newBrush);
	}
	else {
		newBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(deviceContext, newBrush);
	}

	a = Rectangle(deviceContext, left, top, right, bottom);
	// Chọn lại pen cũ
	DeleteObject(SelectObject(deviceContext, oldPen));
	DeleteObject(SelectObject(deviceContext, oldBrush));

	//SwapBuffers(deviceContext);
	// Giải phóng device context
	if (b) ReleaseDC(windowHandle, deviceContext);
	return a;

}


void drawMap(char** a, int n, int m, HWND consoleHandle)
{
	int widthWall = 20;//chiều rộng của tường
	int heighWall = 20;//chiều cao của tường
	int wallColor = RGB(255, 0, 0);//Màu của tường
	int pacmanColor = RGB(0, 255, 0);//Màu của pacman
	int	foodColor = RGB(0, 255, 255);//Màu thức ăn
	int pacmanRadius = widthWall/2;//bán kính của pacman
	int foodRadius = widthWall / 2 - 1;//Bán kính thức ăn

	int can = widthWall / 2;//Như căn lề
	int beginX = 100;//hoành độ bắt đầu của tường
	int beginY = 100;//tung độ bắt đầu của tường


	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < m; j++)
		{
			//Nếu  vị trí này là tường => Vẽ 1 ô vuông với (consoleHandle, Left 
			if (a[i][j] == A.tuong)
			{
				drawRec(consoleHandle, beginX, beginY, beginX + widthWall, beginY + heighWall, wallColor, wallColor);
			}
			else if (a[i][j] == A.start) {
				DrawCircle(consoleHandle, ViTri(beginX+ can, beginY+ can), pacmanRadius, pacmanColor, pacmanColor);
			}
			else if (a[i][j] == A.end)
			{
				DrawCircle(consoleHandle, ViTri(beginX + can, beginY + can), foodRadius, foodColor, foodColor);
			}
			beginX += widthWall;

		}
		beginY += heighWall;
		beginX = 100;
	}
}
