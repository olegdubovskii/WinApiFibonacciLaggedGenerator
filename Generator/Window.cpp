#include <Windows.h>
#include <string>
#include <wingdi.h>
#include <iostream>
#include <fstream>
#include "Generator.h"
#include "Controlls.h"

using namespace std;


Generator * generator;
int numberOfPage = 0;
HINSTANCE mainWindowInstance;
HWND generateButton, sortPageButton, sortAllButton, writeToFileButton, readFromFileButton, nextPageButton, prevPageButton;
HWND lengthEdit, jEdit, kEdit, modEdit, seedEdit, pathEdit;
 

void WINAPI WinRender(HWND hWnd) 
{
		PAINTSTRUCT ps;
		RECT clientRect;
		HDC hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &clientRect);
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(hDC, hPen);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hDC, hBrush);
		SetTextColor(hDC, RGB(0, 0, 0));
		int rectWidth = (clientRect.right - clientRect.left)/16;
		int rectHeight = (clientRect.bottom - clientRect.top - 50)/15;
		unsigned long test;
		vector<unsigned long> matrix = generator->get_numbersMatrix()[numberOfPage];
		int counter = 0;
		string temp;
		wstring fff;
		RECT rect;
		for (int i = 0; i < 15; i++) 
		{
			rect.top = 49 + i * rectHeight;
			rect.bottom = 102 + i * rectHeight;
			for (int j = 0; j < 16; j++) 
			{
				rect.left = 0 + j * rectWidth;
				rect.right = rectWidth + j * rectWidth;
				Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
				if (counter < matrix.size()) 
				{
					test = matrix[counter];
					counter++;
					temp = to_string(test);
					fff = wstring(temp.begin(), temp.end());
					DrawText(hDC, fff.c_str(), temp.size(), &(rect), DT_VCENTER | DT_SINGLELINE | DT_CENTER);
				}
				else 
				{
					continue;
				}
			}
		}
}

void WINAPI CreateButtons(HWND hWnd) 
{
	generateButton = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT("Generate"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 675, 10, 75, 35, hWnd,
		HMENU(GENERATE_BUTTON_PARAM), mainWindowInstance, NULL);

	sortPageButton = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT("SortPage"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 790, 10, 70, 35, hWnd,
		HMENU(SORTPAGE_BUTTON_PARAM), mainWindowInstance, NULL);

	sortAllButton = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT("SortAll"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 900, 10, 70, 35, hWnd,
		HMENU(SORTALL_BUTTON_PARAM), mainWindowInstance, NULL);

	writeToFileButton = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT("WriteToFile"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 1000, 10, 90, 35,
		hWnd, HMENU(WRITE_TO_FILE_PARAM), mainWindowInstance, NULL);

	prevPageButton = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT("<<"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 1480, 10, 25, 35, hWnd,
		HMENU(PREVPAGE_BUTTON_PARAM), mainWindowInstance, NULL);

	nextPageButton = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT(">>"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 1510, 10, 25, 35, hWnd,
		HMENU(NEXTPAGE_BUTTON_PARAM), mainWindowInstance, NULL);

}

void WINAPI CreateEdits(HWND hWnd) 
{
	lengthEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | ES_LEFT, 5, 25, 100, 20, hWnd,
		HMENU(LENGTH_EDIT_PARAM), mainWindowInstance, NULL);

	jEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | ES_LEFT, 115, 25, 53, 20, hWnd,
		HMENU(J_EDIT_PARAM), mainWindowInstance, NULL);

	kEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | ES_LEFT, 178, 25, 53, 20, hWnd,
		HMENU(K_EDIT_PARAM), mainWindowInstance, NULL);

	modEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | ES_LEFT, 241, 25, 100, 20, hWnd,
		HMENU(SEED_EDIT_PARAM), mainWindowInstance, NULL);

	seedEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | ES_LEFT, 351, 25, 300, 20, hWnd,
		HMENU(SEED_EDIT_PARAM), mainWindowInstance, NULL);

	pathEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | ES_LEFT, 1120, 25, 350, 20, hWnd,
		HMENU(SEED_EDIT_PARAM), mainWindowInstance, NULL);
}

void WINAPI CreateLabels(HWND hWnd) 
{
	CreateWindow(TEXT("static"), TEXT("Length:"), WS_CHILD | WS_VISIBLE, 35, 5, 50, 20, hWnd, NULL, mainWindowInstance, NULL);
	CreateWindow(TEXT("static"), TEXT("J value:"), WS_CHILD | WS_VISIBLE, 115, 5, 60, 20, hWnd, NULL, mainWindowInstance, NULL);
	CreateWindow(TEXT("static"), TEXT("K value:"), WS_CHILD | WS_VISIBLE, 178, 5, 60, 20, hWnd, NULL, mainWindowInstance, NULL);
	CreateWindow(TEXT("static"), TEXT("Mod:"), WS_CHILD | WS_VISIBLE, 275, 5, 35, 20, hWnd, NULL, mainWindowInstance, NULL);
	CreateWindow(TEXT("static"), TEXT("Seed:"), WS_CHILD | WS_VISIBLE, 480, 5, 40, 20, hWnd, NULL, mainWindowInstance, NULL);
	CreateWindow(TEXT("static"), TEXT("Path:"), WS_CHILD | WS_VISIBLE, 1285, 5, 40, 20, hWnd, NULL, mainWindowInstance, NULL);
}

bool WINAPI CheckErrors(long long arrayLength, int j, int k, long long mod, string seed) 
{
	if (arrayLength <= 0) 
	{
		MessageBox(NULL, TEXT("Array input error"), TEXT("Error"), MB_OK);
		return false;
	}
	if (seed.size() <= 0)
	{
		MessageBox(NULL, TEXT("Seed input error"), TEXT("Error"), MB_OK);
		return false;
	}
	if (j == k || j > seed.size() || k > seed.size() || k<0|| j<0) 
	{
		MessageBox(NULL, TEXT("Lags input error"), TEXT("Error"), MB_OK);
		return false;
	}
	if (mod<=0 || mod > 4294967296) 
	{
		MessageBox(NULL, TEXT("Mod input error"), TEXT("Error"), MB_OK);
		return false;
	}
	return true;
}

void writeToFile(const char* fileName)
{
	wstring output;
	int counter = generator->get_length();
	for (int i = 0; i < generator->get_length(); i++)
	{
		for (int j = 0; j < 240; j++) {
			if (counter == 0)
				break;
			output += to_wstring(generator->get_numbersMatrix()[i][j]) + TEXT("\n");
			counter--;
		}
	}
	
	wofstream out;
	out.open(fileName);
	out << output << endl;
	out.close();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	long long arrayLength, mod;
	int j, k;
	string seed, path;
	wstring ws, wpath;

	wchar_t* arrayLengthL = new wchar_t[MAX_INPUT];
	wchar_t* modL = new wchar_t[MAX_INPUT];
	wchar_t* jL = new wchar_t[MAX_INPUT];
	wchar_t* kL = new wchar_t[MAX_INPUT];
	wchar_t* seedL = new wchar_t[MAX_INPUT];
	wchar_t* pathL = new wchar_t[MAX_INPUT];
	switch (message)
	{		
	case WM_CREATE:
		CreateWindow(TEXT("static"), TEXT(""), WS_CHILD | WS_VISIBLE, 0, 0, 1535, 50, hWnd, NULL, NULL, NULL);
		CreateButtons(hWnd);
		CreateEdits(hWnd);
		CreateLabels(hWnd);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case GENERATE_BUTTON_PARAM:
			if (generator != nullptr) 
			{
				delete generator;
			}
			GetWindowText(lengthEdit, arrayLengthL, MAX_INPUT);
			GetWindowText(jEdit, jL, MAX_INPUT);
			GetWindowText(kEdit, kL, MAX_INPUT);
			GetWindowText(modEdit, modL, MAX_INPUT);
			GetWindowText(seedEdit, seedL, MAX_INPUT);
			arrayLength = _wtoll(arrayLengthL);
			j = _wtoi(jL);
			k = _wtoi(kL);
			mod = _wtoll(modL);
			ws = wstring(seedL);
			seed = string(ws.begin(), ws.end());
			if (!CheckErrors(arrayLength, j, k, mod, seed)) 
			{
				break;
			}
			generator = new Generator(j, k, mod, seed, arrayLength);
			generator->generateMatrix();
			InvalidateRect(hWnd, NULL, true);
			WinRender(hWnd);
			break;
		case NEXTPAGE_BUTTON_PARAM:
			if (generator != nullptr) 
			{
				if (numberOfPage < generator->get_pages() - 1) 
				{
					numberOfPage++;
					InvalidateRect(hWnd, NULL, true);
					WinRender(hWnd);
				}
				else {
					MessageBox(hWnd, TEXT("You're on the last page"), TEXT("Error"), MB_OK);
				}
			}
			else {
				MessageBox(hWnd, TEXT("Matrix is not generated"), TEXT("Error"), MB_OK);
			}
			break;
		case PREVPAGE_BUTTON_PARAM:
			if (generator != nullptr) 
			{
				if (numberOfPage > 0) 
				{
					numberOfPage--;
					InvalidateRect(hWnd, NULL, true);
					WinRender(hWnd);
				}
				else {
					MessageBox(hWnd, TEXT("You're on the first page"), TEXT("Error"), MB_OK);
				}
			}
			else {
				MessageBox(hWnd, TEXT("Matrix is not generated"), TEXT("Error"), MB_OK);
			}
			break;
		case SORTPAGE_BUTTON_PARAM:
			if (generator != nullptr) 
			{
				generator->sortPage(numberOfPage);
				InvalidateRect(hWnd, NULL, true);
				WinRender(hWnd);
			}
			else 
			{
				MessageBox(hWnd, TEXT("Matrix is not generated"), TEXT("Error"), MB_OK);
			}
			break;
		case SORTALL_BUTTON_PARAM:
			if (generator != nullptr) 
			{
				generator->sortAll();
				InvalidateRect(hWnd, NULL, true);
				WinRender(hWnd);
			}
			else 
			{
				MessageBox(hWnd, TEXT("Matrix is not generated"), TEXT("Error"), MB_OK);
			}
			break;
		case WRITE_TO_FILE_PARAM:
			if (generator != nullptr) 
			{
				GetWindowText(pathEdit, pathL, MAX_INPUT);
				wpath = wstring(pathL);
				path = string(wpath.begin(), wpath.end());
				if (path.compare("") == 0) {
					MessageBox(hWnd, TEXT("Invalid path"), TEXT("Error"), MB_OK);
					break;
				}
				writeToFile(path.data());
				MessageBox(hWnd, TEXT("Success"), TEXT("!"), MB_OK);
			}
			else
			{
				MessageBox(hWnd, TEXT("Matrix is not generated"), TEXT("Error"), MB_OK);
			}
			break;
		}
		break;
	case WM_DESTROY:
		delete generator;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("WindowClass");
	wcex.hIconSm = wcex.hIconSm;

	if (RegisterClassEx(&wcex) == NULL) 
	{
		return 1;
	}

	HWND hWnd = CreateWindow(TEXT("WindowClass"), TEXT("Coursework"), WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);
	if (hWnd == NULL) 
	{
		return 1;
	}
	mainWindowInstance = hInstance;
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) != NULL) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}