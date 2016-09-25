#include "GuessFlag.h"

//constructor
GuessFlag::GuessFlag() {
	nPack = 0;
	runGraphics = NULL;
}

//destructor
GuessFlag::~GuessFlag() {
	delete runGraphics;
}

//run app with pack i
void GuessFlag:: AppRun(int i) {
	SetBackground();
	//set color and erase score
	Gdiplus::SolidBrush  brushRe(Gdiplus::Color(255, 41, 128, 185));
	runGraphics->FillRectangle(&brushRe, 0, 0, 775, 60);

	//Insert title 
	Gdiplus::SolidBrush  brush4(Gdiplus::Color(255, 255, 255, 255));
	Gdiplus::FontFamily  fontFamily(L"Segoe UI");
	Gdiplus::Font        font(&fontFamily, 35, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::PointF      pointF(105.0f, 5.0f);
	runGraphics->DrawString(L"This is the flag of which country?", -1, &font, pointF, &brush4);

	//load picture map
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(data[i].link.c_str(), false);
	runGraphics->DrawImage(bitmap, 195, 70, 350, 200);
}
void GuessFlag::Score(int i) {

	if (i > scoreBest)
		scoreBest = i;

	//convert int to wchar_t
	wchar_t score[4];
	swprintf_s(score, L"%d", i);
	wchar_t best[4];
	swprintf_s(best, L"%d", scoreBest);

	//score
	Gdiplus::SolidBrush  brushErase(Gdiplus::Color(255, 255, 255, 255));
	Gdiplus::PointF      pointNScore(670.0f, 100.0f);
	Gdiplus::FontFamily  fontFamily(L"Segoe UI");

	//label 
	Gdiplus::SolidBrush  brushScore(Gdiplus::Color(255, 142, 68, 173));
	Gdiplus::PointF      pointScore(570.0f, 100.0f);
	Gdiplus::Font        fontScore(&fontFamily, 25, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	runGraphics->DrawString(L"Score : ", -1, &fontScore, pointScore, &brushScore);
	runGraphics->FillRectangle(&brushErase, 670, 100, 50, 37);
	runGraphics->DrawString(score, -1, &fontScore, pointNScore, &brushScore);
	
	//score best
	Gdiplus::PointF      pointBest(570.0f, 150.0f);
	Gdiplus::PointF      pointNBest(670.0f, 150.0f);
	Gdiplus::SolidBrush  brushBest(Gdiplus::Color(255, 0, 0, 255));
	runGraphics->FillRectangle(&brushErase, 670, 150, 50, 37);
	runGraphics->DrawString(L"Best   : ", -1, &fontScore, pointBest, &brushBest);
	runGraphics->DrawString(best, -1, &fontScore, pointNBest, &brushBest);
}

//set handle
void GuessFlag::SetAppHandle(HWND handle)
{
	AppHandle = handle;
}

//init gdi to draw
void GuessFlag::GDIP_Init()
{
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	runGraphics = new Gdiplus::Graphics(GetDC(AppHandle));
}

//get number pack
int GuessFlag::GetNPack() {
	return nPack;
}

//get picture from database
void GuessFlag::GetPicture() {
	wfstream input("DataBase.txt", ios::in);
	int i = 0;
	if (!input.is_open())return;

	//read file and get data
	while (!input.eof()) {
		pack tmp;
		getline(input, tmp.link, L'\t');
		if (i == 0) {
			tmp.link = L".\\DataPictureFlag\\1.png";
			i++;
		}
		else
			tmp.link = L".\\DataPictureFlag\\" + tmp.link + L".png";
		getline(input, tmp.A, L'\t');
		getline(input, tmp.B, L'\t');
		getline(input, tmp.C, L'\t');
		getline(input, tmp.D, L'\t');
		getline(input, tmp.answer, L'\n');
		data.push_back(tmp);
	}
	nPack = data.size()-1;
	input.close();
}

void GuessFlag::ThemStart() {

	//set background title
	Gdiplus::SolidBrush  brushRe(Gdiplus::Color(255, 41, 128, 185));
	runGraphics->FillRectangle(&brushRe, 0, 0, 775, 200);

	//Insert title 
	Gdiplus::SolidBrush  brush4(Gdiplus::Color(255, 255, 255, 255));
	Gdiplus::FontFamily  fontFamily(L"Segoe UI");
	Gdiplus::Font        font(&fontFamily, 35, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::PointF      pointF(105.0f, 25.0f);
	runGraphics->DrawString(L"       GAME GUESS THE FLAG", -1, &font, pointF, &brush4);

	//title id name
	Gdiplus::SolidBrush  brushID(Gdiplus::Color(255, 255, 255, 255));
	Gdiplus::Font        fontId(&fontFamily, 25, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::PointF      pointId(195.0f, 100.0f);
	runGraphics->DrawString(L"      Made by: Trần Hoàng Lâm\n                 ID: 1412280", -1, &fontId, pointId, &brushID);

	ReadScoreBest();
}

//set background
void GuessFlag::SetBackground() {
	
	Gdiplus::SolidBrush  brushRe(Gdiplus::Color(255, 189, 195, 199));
	runGraphics->FillRectangle(&brushRe, 0, 0, 775, 515);
}

//read score best in database
void GuessFlag::ReadScoreBest() {
	fstream input("score.txt", ios::in);
	if (!input.is_open())return;
	input >> scoreBest;
	input.close();
}
//write score best in database
void GuessFlag::WriteScoreBest() {
	fstream output("score.txt", ios::out);
	string score;
	if (!output.is_open())return;
	output << scoreBest;
	output.close();
}
//get variable private
wstring GuessFlag ::GetLink(int i) {
	return data[i].link;
}
wstring GuessFlag::GetA(int i) {
	return data[i].A;
}
wstring GuessFlag::GetB(int i) {
	return data[i].B;
}
wstring GuessFlag::GetC(int i) {
	return data[i].C;
}
wstring GuessFlag::GetD(int i) {
	return data[i].D;
}
wstring GuessFlag::GetAnswer(int i) {
	return data[i].answer;
}