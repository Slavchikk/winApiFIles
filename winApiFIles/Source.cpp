
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#define COUNT 500

void ConvertFloat(char* str, float* arr);


void VivodData(float x1, float x2, float D, int resh)
{
	HANDLE fileResult;
	fileResult = CreateFile(L"C:\\Users\\����������\\source\\repos\\winapifiles\\winApiFIles\\3.txt",    // ����������� ����
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (fileResult == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"��� �������� 2222", L"���� ���������", MB_OK);
	}
	DWORD  d = 0;
	OVERLAPPED olf = { 0 };//�������
	char* strNew = (char*)calloc(100000, sizeof(char*));
	
	if (resh == 0)
	{
		strNew = "������� ���";
		//sprintf(strNew, "����� �����: %f", kol);
		olf.Offset = 0xFFFFFFFF;
		olf.OffsetHigh = 0xFFFFFFFF;
		WriteFile(fileResult, strNew, strlen(strNew), &d, &olf);
	}
	if (resh == 1)
	{
		//strNew = text;
		sprintf(strNew, "��������� ����� ���� ������: %f , ����������� �����: %f", x1,D);
		olf.Offset = 0xFFFFFFFF;
		olf.OffsetHigh = 0xFFFFFFFF;
		WriteFile(fileResult, strNew, strlen(strNew), &d, &olf);
	}
	if (resh == 2)
	{
		//strNew = text;
		sprintf(strNew, "��������� ����� ��� �����: x1 = %f , x2 = %f ����������� �����: %f", x1,x2, D);
		olf.Offset = 0xFFFFFFFF;
		olf.OffsetHigh = 0xFFFFFFFF;
		WriteFile(fileResult, strNew, strlen(strNew), &d, &olf);
	}
}

float resh(float a, float b, float c, int resh)
{
	
	FILE* file;
	float D = 0;
	float x;
	float x1;
	float x2;
	
	
		D = b * b - 4 * a * c;
		if (D < 0)
		{
			VivodData(0, 0, 0, 0, "������� ���");
		}
		else if (D == 0)
		{
			x = -b / 2 * a;
			VivodData(x,0,D,1);
		}
		else {
			x1 = -b - sqrt(D) / 2 * a;
			x2 = -b + sqrt(D) / 2 * a;
			VivodData(x1, x2, D, 2);
			
		}
	
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR nCmdLine, int nCmdShow)
{
	//discrm(1, -4, -5);
		system("chcp 1251>nul");

	HANDLE FileHandle = CreateFile(L"C:\\Users\\����������\\source\\repos\\winapifiles\\winApiFIles\\2.txt",//���� � �����
		GENERIC_READ | GENERIC_WRITE,//����� �� �������� ��� �� ������, ��� � �� ������
		FILE_SHARE_READ,//���������� ������ ������ �� ������
		NULL,//��������� ������������ �� ���������
		OPEN_ALWAYS,//����� �������� ����� (�������, ������������ � �.�.)
		FILE_ATTRIBUTE_NORMAL,//�������� ����� �� ���������
		NULL);

	OVERLAPPED olf = { 0 };//�������
	
	LARGE_INTEGER li = { 0 };
	//LPSTR  BufferWrite = L" 1 -3 2";
	li.QuadPart = 1;
	olf.Offset = li.LowPart;
	olf.OffsetHigh = li.HighPart;
	//��������
	

//	WriteFile(FileHandle, BufferWrite, wcslen(BufferWrite) * sizeof(WCHAR), &ActualCount, &olf);

	LPSTR BufferRead = (CHAR*)calloc(COUNT+1, sizeof(CHAR));//
	DWORD ActualCount = 0;

	if (!ReadFile(FileHandle, BufferRead, COUNT, &ActualCount, &olf))
	{
		MessageBox(NULL, L"������ ��� ��������", L"������", NULL);

	}


	float arr[3];
	ConvertFloat(BufferRead, arr);
	float a = arr[0];
	float	b = arr[1];
	float c = arr[2];
	if (a == 0)
	{
		WriteFile(FileHandle, L"a == 0  ������� ���",COUNT, &ActualCount, &olf);
		MessageBox(NULL, L"� ==0 ������� ���", L"������", NULL);
	}
	else
		resh(a, b, c, 1);
	
	getch();


	olf.Offset = ActualCount;
	CloseHandle(FileHandle);
	return 0;
}
void ConvertFloat(char* str, float* arr)
{
	int i = 0;

	char* nstr = str;

	char* tstr;
	float d = 0;

	while (1)
	{
		tstr = nstr;
		d = strtod(nstr, &nstr);

		if (d == 0 && tstr == nstr) break;
		arr[i] = (float)d;

		i += 1;
	}
}



