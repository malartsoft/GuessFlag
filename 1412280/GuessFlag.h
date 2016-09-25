#include <Windows.h>
#include "1412280.h"
#include <gdiplus.h>
#include "Resource.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
using namespace std;
#pragma comment(lib, "gdiplus.lib")

class GuessFlag {
	Gdiplus::GdiplusStartupInput	gdiplusStartupInput;
	ULONG_PTR						gdiplusToken;
	Gdiplus::Graphics*				runGraphics;
	HWND							AppHandle;
	struct pack {
		wstring link;
		wstring A;
		wstring B;
		wstring C;
		wstring D;
		wstring answer;
	};
	vector<pack>data;
	int nPack;
	int scoreBest;
public:
	GuessFlag();
	~GuessFlag();
	void AppRun(int i);
	void SetAppHandle(HWND handle);
	void GDIP_Init();
	void GetPicture();
	int GetNPack();
	void Score(int);
	void ThemStart();
	void SetBackground();
	void ReadScoreBest();
	void WriteScoreBest();
	wstring GetLink(int i);
	wstring GetA(int i);
	wstring GetB(int i);
	wstring GetC(int i);
	wstring GetD(int i);
	wstring GetAnswer(int i);
};