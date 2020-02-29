#include <windows.h> 
#include <stdio.h>
//#include <GL/gl.h> 
//#include <GL/glu.h> 
#include "gameLib.h"

#define TEXTSIZE(A) (ARRAYSIZE(A)-1)

 /* Windows globals, defines, and prototypes */
CHAR szAppName[] = "GDI Windows testing";
HWND  ghWnd;
HDC   ghDC;
//HGLRC ghRC;

//#define SWAPBUFFERS SwapBuffers(ghDC) 
#define BLACK_INDEX     0 
#define RED_INDEX       13 
#define GREEN_INDEX     14 
#define BLUE_INDEX      16 
#define WIDTH           800 
#define HEIGHT          600 

LONG WINAPI MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL bSetupPixelFormat(HDC);

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void InitMyApp()
{
	printf("MyAppTesting");
	WinMain(0, 0, 0, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS   wndclass;

	wndclass.style = 0;
	wndclass.lpfnWndProc = (WNDPROC)MainWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, szAppName);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = szAppName;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
		return FALSE;

	/* Create the frame */
	ghWnd = CreateWindowA(szAppName,
		"GDI Testing window",
		WS_OVERLAPPEDWINDOW,
	//	WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WIDTH,
		HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!ghWnd)
		return FALSE;

	ShowWindow(ghWnd, 5); //Uses nCmdShow always show
	UpdateWindow(ghWnd);
	return FALSE;
}

static int side2 = 0;
void DrawTest()
{
	PAINTSTRUCT    ps;
	HDC hdc;
	LOGBRUSH lb;
	side2+=5;
	side2 = side2 % 300;

	HGDIOBJ hPen = NULL;
	HGDIOBJ hPenOld;
	RECT rc;
	GetClientRect(ghWnd, &rc);


	DWORD dwPenStyle[] = {
						   PS_DASH,
						   PS_DASHDOT,
						   PS_DOT,
						   PS_INSIDEFRAME,
						   PS_NULL,
						   PS_SOLID
	};
	UINT uHatch[] = {
					  HS_BDIAGONAL,
					  HS_CROSS,
					  HS_DIAGCROSS,
					  HS_FDIAGONAL,
					  HS_HORIZONTAL,
					  HS_VERTICAL
	};

	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(0, 0, 255);
	lb.lbHatch = 0;

	hdc = BeginPaint(ghWnd, &ps);

	SetBkMode(hdc, TRANSPARENT);

	SelectObject(hdc, GetStockObject(BLACK_BRUSH));


	Rectangle(ps.hdc, rc.left, rc.top,
		rc.right, rc.bottom);

	SelectObject(hdc, GetStockObject(BLACK_BRUSH));

	for (int i = 0; i < 6; i++)
	{
		hPen = ExtCreatePen(PS_COSMETIC | PS_SOLID,
			1, &lb, 0, NULL);
		hPenOld = SelectObject(hdc, hPen);
		MoveToEx(hdc, rc.left + (i * 20), rc.top, NULL);
		LineTo(hdc, rc.left + (i * 20) + side2 , rc.bottom);
		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);
	}

	EndPaint(ghWnd, &ps);
}


int side = 0;
int number = 0;
/* main window procedure */
LONG WINAPI MainWndProc(
	HWND    hWnd,
	UINT    uMsg,
	WPARAM  wParam,
	LPARAM  lParam)
{
	LONG    lRet = 1;
	PAINTSTRUCT    ps;
	RECT rect;



	LOGBRUSH lb;
	RECT rc;
	HDC hdc;
	int i;
	HGDIOBJ hPen = NULL;
	HGDIOBJ hPenOld;
	DWORD dwPenStyle[] = {
						   PS_DASH,
						   PS_DASHDOT,
						   PS_DOT,
						   PS_INSIDEFRAME,
						   PS_NULL,
						   PS_SOLID
	};
	UINT uHatch[] = {
					  HS_BDIAGONAL,
					  HS_CROSS,
					  HS_DIAGCROSS,
					  HS_FDIAGONAL,
					  HS_HORIZONTAL,
					  HS_VERTICAL
	};


	switch (uMsg) {

	case WM_CREATE:
		ghDC = GetDC(hWnd);
		if (!bSetupPixelFormat(ghDC))
			PostQuitMessage(0);

	//	ghRC = wglCreateContext(ghDC);
	//	wglMakeCurrent(ghDC, ghRC);
		GetClientRect(hWnd, &rect);
		//initializeGL(rect.right, rect.bottom);
		break;

	case WM_PAINT:

	
	//	GetClientRect(hWnd, &rc);
	//	printf("%d\n",rc.bottom);

	//	// Initialize the pen's brush.
	//	lb.lbStyle = BS_SOLID;
	//	lb.lbColor = RGB(0, 0, 255);
	//	lb.lbHatch = 0;

	//

	//	hdc = BeginPaint(hWnd, &ps);

	//	SetBkMode(hdc, TRANSPARENT);

	//	SelectObject(hdc, GetStockObject(BLACK_BRUSH));


	//	Rectangle(ps.hdc, rc.left, rc.top,
	//		rc.right, rc.bottom);


	//	//for (i = 0; i < 6; i++)
	//	//{
	//	//	hPen = ExtCreatePen(PS_COSMETIC | PS_SOLID,
	//	//		1, &lb, 0, NULL);
	//	//	hPenOld = SelectObject(hdc, hPen);
	//	//	MoveToEx(hdc, rc.left + (i * 20), rc.top, NULL);
	//	//	LineTo(hdc, rc.left + (i * 20) + side, rc.bottom);
	//	//	SelectObject(hdc, hPenOld);
	//	//	DeleteObject(hPen);
	//	//}

	//	SetTextColor(hdc, RGB(0,255,0) );

	//	side+=20;
	//	side = side % 500;

	//	HFONT hFont, hOldFont;

	//	// Retrieve a handle to the variable stock font.  
	////	hFont = (HFONT)GetStockObject(OEM_FIXED_FONT);
	//	AddFontResource("apple2.ttf");

	//	hFont = CreateFontA(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
	//		CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("appleII"));
	//	SelectObject(hdc, hFont);





	//





	//	// Select the variable stock font into the specified device context. 
	//	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	//	{
	//		// Display the text string.  
	//	//	TextOutA(hdc, 10, 50, "Sample ANSI_VAR_FONT text\n Hola", 15);
	//		RECT  lprc;
	//		lprc.bottom = 200;
	//		lprc.left = 0;
	//		lprc.right = 400;
	//		lprc.top = 0;

	//		
	//		char texto[] = "System testing\n"
	//			           "Restarting...\n"
	//					   "System testing\n"
	//					   "Restarting...\n"
	//					   "System testing\n"
	//					   "Restarting...\n"
	//					   "System testing\n"
	//					   "Restarting...\n";
	//		number= number+1;
	//		number=number%TEXTSIZE(texto);
	//		DrawText(hdc, texto, number,&lprc, DT_LEFT);
	//		
	//		// Restore the original font.        
	//		SelectObject(hdc, hOldFont);
	//	}

	//	DeleteObject(hFont);

	//	EndPaint(hWnd, &ps);

		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		//resize(rect.right, rect.bottom);
		break;

	case WM_CLOSE:
		if (ghDC)
			ReleaseDC(hWnd, ghDC);
	
		ghDC = 0;

		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		if (ghDC)
			ReleaseDC(hWnd, ghDC);

		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			//longinc += 0.5F;
			break;
		case VK_RIGHT:
			//longinc -= 0.5F;
			break;
		case VK_UP:
			//latinc += 0.5F;
			break;
		case VK_DOWN:
			//latinc -= 0.5F;
			break;
		}

	default:
		lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return lRet;
}

BOOL bSetupPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd, *ppfd;
	int pixelformat;

	ppfd = &pfd;

	ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
	ppfd->nVersion = 1;
	//ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_GDI ;
	ppfd->dwLayerMask = PFD_MAIN_PLANE;
	ppfd->iPixelType = PFD_TYPE_COLORINDEX;
	ppfd->cColorBits = 8;
	ppfd->cDepthBits = 0;
	ppfd->cAccumBits = 0;
	ppfd->cStencilBits = 0;

	pixelformat = ChoosePixelFormat(hdc, ppfd);

	if ((pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0)
	{
		MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
		return FALSE;
	}

	if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE)
	{
		MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
		return FALSE;
	}
	return TRUE;
}




Vertex2f_t Vertex2f(float x, float y)
{
	Vertex2f_t vertex;
	vertex.x = x;
	vertex.y = y;
	return vertex;
}

void DrawLine(Vertex2f_t p1, Vertex2f_t p2)
{

}

void ClearScreen()
{
	
}

void SwapScreen()
{
	MSG msg;
	int EndLoop = FALSE;

	while ((PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE) && (!EndLoop) )
	{
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			EndLoop = TRUE;
			//return;
		}
	}
	RedrawWindow(ghWnd, NULL, NULL, RDW_INVALIDATE | RDW_NOERASE);
}

