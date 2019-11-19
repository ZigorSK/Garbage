#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>


#define PI 3.14159265
#define Dx 5
#define Dy 5
#define SCALE 1.15
#define scale 0.95

#define R -0.033
#define L 0.033

#define _CRT_SECURE_NO_WARNINGS

void DrawFigure_and_fill(double A[][3], int flag)
{


	int array_x[4000], array_y[4000], *arr_x = array_x, *arr_y = array_y, count = 0, flag_repeat;

	if (flag)
	{
		HWND sHwnd = GetForegroundWindow();
		HDC hdc = GetDC(sHwnd);

		srand(time(NULL));

		int R1 = rand() % 100 + 100;
		int R2 = rand() % 100 + 100;
		int R3 = rand() % 100 + 100;

		for (int i = 0; i < 4; i++)
		{
			int B[2][3] = { {round(A[i][0]),round(A[i][1]),A[i][2]} ,{round(A[i + 1][0]),round(A[i + 1][1]),A[i + 1][2]} };

			int dx = abs(B[0][0] - B[1][0]);
			int dy = abs(B[0][1] - B[1][1]);
			int sx = B[0][0] < B[1][0] ? 1 : -1;
			int sy = B[0][1] < B[1][1] ? 1 : -1;
			int err = (dx > dy ? dx : -dy) / 2;
			int e2 = err;

			while (1)
			{
				SetPixel(hdc, B[0][0], B[0][1], RGB(R1, R2, R3));

				//Заполняем массив граничных точек фигуры
				if (count < 4000)// Если в массиве есть место
				{
					flag_repeat = B[0][1];
					if (flag_repeat != *(arr_y + count - 1))
					{
						*(arr_x + count) = B[0][0];//Запоминаем x
						*(arr_y + count) = B[0][1];//ЗАпоминаем y

						count++;
					}

				}
				else// Если Массив переполнен
				{
					flag_repeat = B[0][1];
					if (flag_repeat != *(arr_y + count - 1))
					{
						arr_x = (int *)realloc(arr_x, sizeof(int)*(count + 1));
						arr_y = (int *)realloc(arr_y, sizeof(int)*(count + 1));

						*(arr_x + count) = B[0][0];//Запоминаем x
						*(arr_y + count) = B[0][1];//ЗАпоминаем y

						count++;
					}
				}

				if (B[0][0] == B[1][0] && B[0][1] == B[1][1]) break;
				e2 = err;

				if (e2 > -dx)
				{
					err -= dy; B[0][0] += sx;
				}

				if (e2 < dy)
				{
					err += dx; B[0][1] += sy;
				}
			}
		}
		//Посрочная заливка, используя граничные точкив массивах arr_x And arr_y

		//Сортируем массивы по Y(Если Y равны, то по х)
		count--;

		int tmp;
		int noSwap;

		for (int i = count - 1; i >= 0; i--)
		{
			noSwap = 1;
			for (int j = 0; j < i; j++)
			{
				
				if (arr_y[j] > arr_y[j + 1])
				{
					tmp = arr_y[j];
					arr_y[j] = arr_y[j + 1];
					arr_y[j + 1] = tmp;

					tmp = arr_x[j];
					arr_x[j] = arr_x[j + 1];
					arr_x[j + 1] = tmp;
					noSwap = 0;
				}
				
			}
			if (noSwap == 1)
				break;
		}

		//ЗАносим в массив точки по определённому Y Сортируем их и если по этому y не вершина фгуры, заливаем линию
		int count_x = 0, count_y = 0, now_y = arr_y[0];
		int mas_x[3];

		do {

			count_x = 0;

			while (1)
			{
				*(mas_x + count_x) = *(arr_x + count_y);
				count_x++;
				count_y++;

				if (now_y != arr_y[count_y])	break;
			}

			//сортируем массив и заливаем линию
			if (count_x == 2)
			{
				if (*mas_x > *(mas_x + 1))
				{
					int tmp = *mas_x;
					*mas_x = *(mas_x + 1);
					*(mas_x + 1) = tmp;
				}

				while (*mas_x != *(mas_x + 1))
				{
					SetPixel(hdc, *mas_x, now_y, RGB(R1, R2, R3));
					*mas_x = *mas_x + 1;
				}
			}
			now_y = *(arr_y + count_y );
		} while (count_y < count);

		
		if (count > 4000)
		{
			free(arr_x);
			free(arr_y);
		}
		ReleaseDC(sHwnd, hdc);
	}
	else
		{
		HWND sHwnd = GetForegroundWindow();
		HDC hdc = GetDC(sHwnd);

		for (int i = 0; i < 4; i++)
		{
			int B[2][3] = { {round(A[i][0]),round(A[i][1]),A[i][2]} ,{round(A[i + 1][0]),round(A[i + 1][1]),A[i + 1][2]} };

			int dx = abs(B[0][0] - B[1][0]);
			int dy = abs(B[0][1] - B[1][1]);
			int sx = B[0][0] < B[1][0] ? 1 : -1;
			int sy = B[0][1] < B[1][1] ? 1 : -1;
			int err = (dx > dy ? dx : -dy) / 2;
			int e2 = err;

			while (1)
			{
				SetPixel(hdc, B[0][0], B[0][1], RGB(0, 0, 0));

				//Заполняем массив граничных точек фигуры
				if (count < 4000)// Если в массиве есть место
				{
					flag_repeat = B[0][1];
					if (flag_repeat != *(arr_y + count - 1))
					{
						*(arr_x + count) = B[0][0];//Запоминаем x
						*(arr_y + count) = B[0][1];//ЗАпоминаем y

						count++;
					}

				}
				else// Если Массив переполнен
				{
					flag_repeat = B[0][1];
					if (flag_repeat != *(arr_y + count - 1))
					{
						arr_x = (int *)realloc(arr_x, sizeof(int)*(count + 1));
						arr_y = (int *)realloc(arr_y, sizeof(int)*(count + 1));

						*(arr_x + count) = B[0][0];//Запоминаем x
						*(arr_y + count) = B[0][1];//ЗАпоминаем y

						count++;
					}
				}

				if (B[0][0] == B[1][0] && B[0][1] == B[1][1]) break;
				e2 = err;

				if (e2 > -dx)
				{
					err -= dy; B[0][0] += sx;
				}

				if (e2 < dy)
				{
					err += dx; B[0][1] += sy;
				}
			}
		}
		//Посрочная заливка, используя граничные точкив массивах arr_x And arr_y

		//Сортируем массивы по Y(Если Y равны, то по х)
		count--;

		int tmp;
		int noSwap;

		for (int i = count - 1; i >= 0; i--)
		{
			noSwap = 1;
			for (int j = 0; j < i; j++)
			{

				if (arr_y[j] > arr_y[j + 1])
				{
					tmp = arr_y[j];
					arr_y[j] = arr_y[j + 1];
					arr_y[j + 1] = tmp;

					tmp = arr_x[j];
					arr_x[j] = arr_x[j + 1];
					arr_x[j + 1] = tmp;
					noSwap = 0;
				}

			}
			if (noSwap == 1)
				break;
		}

		//ЗАносим в массив точки по определённому Y Сортируем их и если по этому y не вершина фгуры, заливаем линию
		int count_x = 0, count_y = 0, now_y = arr_y[0];
		int mas_x[3];

		do {

			count_x = 0;

			while (1)
			{
				*(mas_x + count_x) = *(arr_x + count_y);
				count_x++;
				count_y++;

				if (now_y != arr_y[count_y])	break;
			}

			//сортируем массив и заливаем линию
			if (count_x == 2)
			{
				if (*mas_x > *(mas_x + 1))
				{
					int tmp = *mas_x;
					*mas_x = *(mas_x + 1);
					*(mas_x + 1) = tmp;
				}

				while (*mas_x != *(mas_x + 1))
				{
					SetPixel(hdc, *mas_x, now_y, RGB(0, 0, 0));
					*mas_x = *mas_x + 1;
				}
			}
			now_y = *(arr_y + count_y);
		} while (count_y < count);


		if (count > 4000)
		{
			free(arr_x);
			free(arr_y);
		}
		ReleaseDC(sHwnd, hdc);
	}

}

void move_x(double A[][3], int flag)
{
	int dx = flag ? Dx : -Dx;
	double B[3][3] = { {1,0,0},{0,1,0},{dx, 0, 1} };

	double tmp[3] = { 0,0, };
	for (int i = 0; i < 4; i++)
	{
		tmp[0] = (A[i][0] * B[0][0] + A[i][1] * B[1][0] + A[i][2] * B[2][0]);
		tmp[1] = (A[i][0] * B[0][1] + A[i][1] * B[1][1] + A[i][2] * B[2][1]);
		tmp[2] = (A[i][0] * B[0][2] + A[i][1] * B[1][2] + A[i][2] * B[2][2]);

		A[i][0] = tmp[0];
		A[i][1] = tmp[1];
		A[i][2] = tmp[2];
	}
	A[4][0] = A[0][0];
	A[4][1] = A[0][1];
}

void move_y(double A[][3], int flag)
{
	int dy = flag ? -Dy : Dy;
	double B[3][3] = { {1,0,0},{0,1,0},{0, dy, 1} };

	double tmp[3] = { 0,0, };
	for (int i = 0; i < 4; i++)
	{
		tmp[0] = (A[i][0] * B[0][0] + A[i][1] * B[1][0] + A[i][2] * B[2][0]);
		tmp[1] = (A[i][0] * B[0][1] + A[i][1] * B[1][1] + A[i][2] * B[2][1]);
		tmp[2] = (A[i][0] * B[0][2] + A[i][1] * B[1][2] + A[i][2] * B[2][2]);

		A[i][0] = tmp[0];
		A[i][1] = tmp[1];
		A[i][2] = tmp[2];
	}
	A[4][0] = A[0][0];
	A[4][1] = A[0][1];
}

void Scale(double A[][3], int flag)
{
	double x1 = (A[0][0] + A[1][0] + A[2][0] + A[3][0]) / 4;
	double y1 = (A[0][1] + A[1][1] + A[2][1] + A[3][1]) / 4;
	double U = flag ? SCALE : scale;
	double B[3][3] = { {U,0,0},{0,U,0},{x1 - U * x1, y1 - U * y1, 1} };
	double tmp[3] = { 0,0, };
	for (int i = 0; i < 4; i++)
	{
		tmp[0] = (A[i][0] * B[0][0] + A[i][1] * B[1][0] + A[i][2] * B[2][0]);
		tmp[1] = (A[i][0] * B[0][1] + A[i][1] * B[1][1] + A[i][2] * B[2][1]);
		tmp[2] = (A[i][0] * B[0][2] + A[i][1] * B[1][2] + A[i][2] * B[2][2]);

		A[i][0] = tmp[0];
		A[i][1] = tmp[1];
		A[i][2] = tmp[2];
	}
	A[4][0] = A[0][0];
	A[4][1] = A[0][1];
}
void rot(double A[][3], int flag)
{
	double x1 = (A[0][0] + A[1][0] + A[2][0] + A[3][0]) / 4;
	double y1 = (A[0][1] + A[1][1] + A[2][1] + A[3][1]) / 4;
	double U = flag ? R : L;
	double B[3][3] = { {cos(U),sin(U),0},{(-sin(U)),cos(U),0},{(x1*(1 - cos(U)) + y1 * sin(U)),(y1*(1 - cos(U)) - x1 * sin(U)), 1} };
	double tmp[3] = { 0,0, };
	for (int i = 0; i < 4; i++)
	{
		tmp[0] = (A[i][0] * B[0][0] + A[i][1] * B[1][0] + A[i][2] * B[2][0]);
		tmp[1] = (A[i][0] * B[0][1] + A[i][1] * B[1][1] + A[i][2] * B[2][1]);
		tmp[2] = (A[i][0] * B[0][2] + A[i][1] * B[1][2] + A[i][2] * B[2][2]);

		A[i][0] = tmp[0];
		A[i][1] = tmp[1];
		A[i][2] = tmp[2];
	}
	A[4][0] = A[0][0];
	A[4][1] = A[0][1];
};



int main()
{
	system("chcp 1251");

	double A[5][3] = { {0, 0, 1 } , {0, 0, 1} , {0, 0, 1 } , {0, 0, 1} , {0, 0, 1 } };
	char choice = '0';
	/*for (int i = 0; i < 4; i++)
	{
		printf("Введите X[%d]:", i);
		scanf("%lf", &A[i][0]);

		printf("Введите Y[%d]:", i);
		scanf("%lf", &A[i][1]);

		A[i][0] += X0;
		A[i][1] += X0;
	}*/
	A[0][0] += 5;
	A[0][1] += 120;
	A[1][0] += 200;
	A[1][1] += 50;
	A[2][0] += 250;
	A[2][1] += 150;
	A[3][0] += 120;
	A[3][1] += 200;
	A[4][0] = A[0][0];
	A[4][1] = A[0][1];
	system("cls");
	do
	{
		DrawFigure_and_fill(A, 1);
		choice = _getch();


		switch (choice)
		{
		case '2'://Сдвиг  вниз
			DrawFigure_and_fill(A, 0);
			move_y(A, 0);
			break;

		case '8'://Сдвиг вверх
			DrawFigure_and_fill(A, 0);
			move_y(A, 1);
			break;

		case '6'://Сдвиг вправо 
			DrawFigure_and_fill(A, 0);
			move_x(A, 1);
			break;

		case '4'://Сдвиг влево
			DrawFigure_and_fill(A, 0);
			move_x(A, 0);
			break;

		case '1'://Уменьшить
			DrawFigure_and_fill(A, 0);
			Scale(A, 0);
			break;

		case '3'://Увеличить
			DrawFigure_and_fill(A, 0);
			Scale(A, 1);
			break;

		case '7'://Вращать влево
			DrawFigure_and_fill(A, 0);
			rot(A, 1);
			break;

		case '9'://Вращать вправо
			DrawFigure_and_fill(A, 0);
			rot(A, 0);
			break;

		default: break;
		}

	} while (choice != '0');


	return 0;
}