// 1412280.cpp : Defines the entry point for the application.
//
#include "GuessFlag.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//handle button start
HWND start;

//handle button old
HWND handOld[4]; 

//pack i
int i = 0; 
int score = 0;
bool run = 1;

//variable to run game
GuessFlag guessFlag;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND hWnd;

//change picture when answer true
void ChangePicture(HWND hWnd, int i,int score, HWND handButton[]);

//win main
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1412280, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1412280));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1412280));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1412280);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void IntroStart(HWND hWnd) {
	//set font
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(51, 25,
		lf.lfEscapement, lf.lfOrientation, 21,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);
	 start=CreateWindowEx(NULL, L"BUTTON", L"Start game", BS_FLAT | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 200, 270, 350, 90, hWnd, (HMENU)IDC_START, NULL, NULL);
	 SendMessage(start, WM_SETFONT, WPARAM(hFont), TRUE);
	 guessFlag.ThemStart();
}

//change picture when answer is true
void ChangePicture(HWND hWnd,int i, int score, HWND button[]){

	//set font
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(21, 7,
		lf.lfEscapement, lf.lfOrientation, 21,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	//change picture and change score
	guessFlag.AppRun(i);
	guessFlag.Score(score);

	//set button
	button[0]=CreateWindowEx(NULL, L"BUTTON", guessFlag.GetA(i).c_str(),BS_FLAT| WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 85, 300, 250, 60, hWnd, (HMENU)IDC_BUTTON_A, NULL, NULL);
	SendMessage(button[0], WM_SETFONT, WPARAM(hFont), TRUE);
	
	button[1] =CreateWindowEx(NULL, L"BUTTON", guessFlag.GetB(i).c_str(), BS_FLAT | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 400, 300, 250, 60, hWnd, (HMENU)IDC_BUTTON_B, NULL, NULL);
	SendMessage(button[1], WM_SETFONT, WPARAM(hFont), TRUE);

	button[2] =CreateWindowEx(NULL, L"BUTTON", guessFlag.GetC(i).c_str(), BS_FLAT | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 85, 370, 250, 60, hWnd, (HMENU)IDC_BUTTON_C, NULL, NULL);
	SendMessage(button[2], WM_SETFONT, WPARAM(hFont), TRUE);

	button[3] =CreateWindowEx(NULL, L"BUTTON", guessFlag.GetD(i).c_str(), BS_FLAT | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 400, 370, 250, 60, hWnd, (HMENU)IDC_BUTTON_D, NULL, NULL);
	SendMessage(button[3], WM_SETFONT, WPARAM(hFont), TRUE);
	
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindowW(szWindowClass, L"Game guess flag", WS_OVERLAPPEDWINDOW,
      320, 100, 775, 515, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //init gdi and get data
   guessFlag.GetPicture();
   guessFlag.SetAppHandle(hWnd);
   guessFlag.GDIP_Init();

   //get first pack when i=0
   IntroStart(hWnd);
   return TRUE;
}

//detroy handle of button
void DestroyHandButton(HWND handButton[]) {
	for (int i = 0; i < 4; i++)
		DestroyWindow(handButton[i]);
}

//convert handle new to handle button old
void ConverHandToOld(HWND old[], HWND newH[]) {
	for (int i = 0; i < 4; i++)
		old[i] = newH[i];
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {

				HWND handButton[4];
			case IDC_START:
				run = 1;
				score = 0;
				DestroyWindow(start);
				ChangePicture(hWnd, i, score, handButton);
				ConverHandToOld(handOld, handButton);
				break;

				//if answer is a
			case IDC_BUTTON_A :
				if (run == 1) {
					if (guessFlag.GetAnswer(i)[0] == 'A') {
						i++;
						if (i == guessFlag.GetNPack())
							i = 0;
						DestroyHandButton(handOld);
						//pack next
						score++;
						ChangePicture(hWnd, i,score,handButton);
						ConverHandToOld(handOld, handButton);
					}
					else {
						MessageBox(hWnd, L"You choose wrong\nPress OK to continue", L"Game over!", 0);
						run = 0;
						return 0;
					}
				}
				break;

				//if answer is b
			case IDC_BUTTON_B:
				if (run == 1) {
					if (guessFlag.GetAnswer(i)[0] == 'B') {
						i++;
						if (i == guessFlag.GetNPack())
							i = 0;
						DestroyHandButton(handOld);
						//pack next
						score++;
						ChangePicture(hWnd, i, score, handButton);
						ConverHandToOld(handOld, handButton);
					}
					else {
						MessageBox(hWnd, L"You choose wrong\nPress OK to continue", L"Game over!", 0);
						run = 0;
						return 0;
					}
				}
				break;

				//if answer is c
			case IDC_BUTTON_C:
				if (run == 1) {
					if (guessFlag.GetAnswer(i)[0] == 'C') {
						i++;
						if (i == guessFlag.GetNPack())
							i = 0;
						DestroyHandButton(handOld);
						//pack next
						score++;
						ChangePicture(hWnd, i, score, handButton);
						ConverHandToOld(handOld, handButton);
					}
					else {
						MessageBox(hWnd, L"You choose wrong\nPress OK to continue", L"Game over!", 0);
						run = 0;
						return 0;
					}
				}
				break;

				//if answer is d
			case IDC_BUTTON_D:
				if (run == 1) {
					if (guessFlag.GetAnswer(i)[0] == 'D') {
						i++;
						if (i == guessFlag.GetNPack())
							i = 0;
						DestroyHandButton(handOld);
						//pack next
						score++;
						ChangePicture(hWnd, i, score, handButton);
						ConverHandToOld(handOld, handButton);
					}
					else {
						MessageBox(hWnd, L"You choose wrong\nPress OK to continue", L"Game over!", 0);
						run = 0;
						return 0;
					}
				}
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_FILE_NEW:
				run = 1;
				score = 0;

				DestroyHandButton(handOld);
				DestroyWindow(start);
				ChangePicture(hWnd, i,score,handButton);
				ConverHandToOld(handOld, handButton);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		//set score best new in database
		guessFlag.WriteScoreBest();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
