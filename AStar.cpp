#include "stdafx.h"
#include "AStar.h"
char AStar::ma = 'o';
char AStar::tuong = '%';
char AStar::end = 'G';
char AStar::start = 'P';
AStar::AStar()
{

}
void AStar::khoiTao()
{
	//cấp phát cho n dòng m cột
	this->KC = new float*[n];
	this->L = new int*[n];
	this->Path = new ViTri*[n];

	for (int i = 0; i < n; i++)
	{
		KC[i] = new float[m];
		L[i] = new int[m];
		Path[i] = new ViTri[m];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			KC[i][j] = 0;
			L[i][j] = 0;
		}
	}
}
void AStar::docFile(ifstream& in)
{
	string temp;
	while (!in.eof())
	{
		getline(in, temp);
		if (temp.size() != 0)
			a.push_back(temp);
	}
	n = a.size();
	m = a[0].size();
	khoiTao();
	bool p = true, g = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] == end && g)
			{
				G.nhap(i, j);
				g = false;
			}
			else if (a[i][j] == start&&p)
			{
				P.nhap(i, j);
				p = false;
			}
			else if(!p&&!g){
				in.close();
				return;
			}
			else {

			}

		}
	}


	if (p == false || g == false)
	{
		cout << "PACMAN hoac DIEM THUC AN KHONG DUNG KY TU YEU CAU\n";
	}
	in.close();
	
}

char** AStar::xuatFile(ofstream&out)
{

	//Cap phat mang kq
	if (L[G.x][G.y] != 1) {
		out << -1;
		return NULL;
	}
	char** kq = new char*[n];
	for (int i = 0; i < n; i++)
	{
		kq[i] = new char[m];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j ++)
		{
			kq[i][j] = a[i][j];
		}
	}

	int x = Path[G.x][G.y].x;
	int y = Path[G.x][G.y].y;

	while (Path[x][y].x !=P.x|| Path[x][y].y !=P.y)
	{
		int i = Path[x][y].x;
		int j = Path[x][y].y;
		kq[x][y] = 'O';

		x = i;
		y = j;
	}
	kq[x][y] = 'O';
	//xuat file ra

	for (int i = 0; i < n; i ++)
	{
		for (int j = 0; j < m; j ++)
		{
			out << kq[i][j];
		}
		out << endl;
	}
	//delete mang kq
	return kq;
}

void AStar::AStar_Algorithm()
{

	node s(P,0,kc2Diem(P.x,P.y,G.x,G.y));//Khởi tạo node tại vị trí PacMan đang đứng,chi phí thực sự là 0 và f = ước lượng (#0) ;
	pq.push(s);//bỏ s vào hàng đợi ưu tiên
	while (!pq.empty() && L[G.x][G.y] != 1)//Trong khi hàng đợi đang còn phần tử và chưa lấy node G ra
	{
		node u = pq.top();//Lấy đỉnh PQ
		pq.pop();//Xóa đỉnh đó đi
		int i = u.vt.x;//Hoành độ
		int j = u.vt.y;//Tung độ
		L[i][j] = 1;//Đánh dấu cái đỉnh đó có vị trí bao gồm tung độ y và hoành độ x đã lấy
		//Xét 4 vị trí xung quanh nó
		//Tại vị trí dòng i-1, cột j
			if (a[i-1][j] != ma && a[i - 1][j] != tuong && i >=1 && L[i-1][j] != 1)//Nếu điểm ở trên nằm trong mê cung và chưa được lấy ra là điểm có thể đi được hoặc là điểm đích
			{
				int kc = u.g + 1;//Cộng dồn khoảng cách thực sự
				float h = this->kc2Diem(i - 1 , j, G.x, G.y);
				float f = kc + h;
				
				ViTri vt(i - 1, j);
				node temp(vt,kc,f);//Khởi tạo node vs đỉnh i,kc = kc cộng dồn

				if (KC[i-1][j] == 0)//Nếu chưa có đỉnh nào gọi nó
				{
					KC[i-1][j] = f;//Cập nhật kc cho đỉnh
					Path[i - 1][j].nhap(i, j);//Cập nhật đỉnh cha gọi nó
					pq.push(temp);//Bỏ vào hàng đợi

				}
				else //Nếu đã có đỉnh gọi nó rồi
				{
					if (f < KC[i-1][j])//Nếu khoảng cách hiện tại < khoảng cách trước
					{
						KC[i-1][j] = f;
						Path[i - 1][j].nhap(i, j);
						pq.push(temp);//Bỏ vào hàng đợi

					}
				}
			}
			//xét tại vị trí dòng i+1 cột j
			if (a[i + 1][j] !=ma && a[i + 1][j] != tuong && i< n-1 && L[i + 1][j] != 1)//Nếu điểm ở trên nằm trong mê cung và chưa được lấy ra
			{
				int kc = u.g + 1;//Cộng dồn khoảng cách thực sự
				float h = this->kc2Diem(i + 1, j, G.x, G.y);
				float f = kc + h;
				ViTri vt(i + 1, j);
				node temp(vt, kc, f);//Khởi tạo node vs đỉnh i,kc = kc cộng dồn

				if (KC[i + 1][j] == 0)//Nếu chưa có đỉnh nào gọi nó
				{
					KC[i + 1][j] = f;//Cập nhật kc cho đỉnh
					Path[i + 1][j].nhap(i, j);//Cập nhật đỉnh cha gọi nó
					pq.push(temp);//Bỏ vào hàng đợi

				}
				else //Nếu đã có đỉnh gọi nó rồi
				{
					if (f < KC[i + 1][j])//Nếu khoảng cách hiện tại < khoảng cách trước
					{
						KC[i + 1][j] = f;
						Path[i + 1][j].nhap(i, j);
						pq.push(temp);//Bỏ vào hàng đợi

					}
				}
			}
		
			//xét tại vị trí dòng i cột j-1
			if (a[i][j-1] != ma && a[i][j-1] != tuong && j>0 && L[i][j-1] != 1)//Nếu điểm ở trên nằm trong mê cung và chưa được lấy ra
			{
				int kc = u.g + 1;//Cộng dồn khoảng cách thực sự
				float h = this->kc2Diem(i, j-1, G.x, G.y);
				float f = kc + h;
				ViTri vt(i, j-1);
				node temp(vt, kc, f);//Khởi tạo node vs đỉnh i,kc = kc cộng dồn

				if (KC[i][j-1] == 0)//Nếu chưa có đỉnh nào gọi nó
				{
					KC[i][j - 1] = f;//Cập nhật kc cho đỉnh
					Path[i][j - 1].nhap(i, j);//Cập nhật đỉnh cha gọi nó
					pq.push(temp);//Bỏ vào hàng đợi

				}
				else //Nếu đã có đỉnh gọi nó rồi
				{
					if (f < KC[i][j - 1])//Nếu khoảng cách hiện tại < khoảng cách trước
					{
						KC[i][j - 1] = f;
						Path[i][j - 1].nhap(i, j);
						pq.push(temp);//Bỏ vào hàng đợi

					}
				}
			}

			//xét tại vị trí dòng i cột j+1
			if (a[i][j + 1] != ma && a[i][j+1] != tuong && j < m -1 && L[i][j + 1] != 1)//Nếu điểm ở trên nằm trong mê cung và chưa được lấy ra
			{
				int kc = u.g + 1;//Cộng dồn khoảng cách thực sự
				float h = this->kc2Diem(i, j+1, G.x, G.y);
				float f = kc + h;
				ViTri vt(i, j + 1);
				node temp(vt, kc, f);//Khởi tạo node vs đỉnh i,kc = kc cộng dồn

				if (KC[i][j + 1] == 0)//Nếu chưa có đỉnh nào gọi nó
				{
					KC[i][j + 1] = f;//Cập nhật kc cho đỉnh
					Path[i][j + 1].nhap(i, j);//Cập nhật đỉnh cha gọi nó
					pq.push(temp);//Bỏ vào hàng đợi

				}
				else //Nếu đã có đỉnh gọi nó rồi
				{
					if (f < KC[i][j + 1])//Nếu khoảng cách hiện tại < khoảng cách trước
					{
						KC[i][j + 1] = f;
						Path[i][j + 1].nhap(i, j);
						pq.push(temp);//Bỏ vào hàng đợi

					}
				}
			}

	}
}


float AStar::kc2Diem(int x1, int y1, int x2, int y2)
{
	double kq =  sqrt((float)(x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)*1.0);
	return (float) kq;
}




AStar::~AStar()
{
	for (int i = 0; i < n; i++)
	{
		delete[]Path[i];
		delete[]L[i];
		delete[]KC[i];
	}
	while (!pq.empty())pq.pop();
	delete Path;
	delete L;
	delete KC;
}
