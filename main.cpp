#include "pch.h"

#include "framework.h"
#include "Client.h"

#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst; // 현재 인스턴스입니다.
HWND      g_hWnd;// Main Window Handle                                 

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(HINSTANCE hInstance // 프로그램이 실행되었을때 메모리 시작 주소
    , HINSTANCE hPrevInstance
    , LPWSTR lpCmdLine
    , int nCmdShow)
{     
    // CRT 메모리 릭 디버그
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(231);

    // 생성 시킬 윈도우 설정
    MyRegisterClass(hInstance);

    // 윈도우 하나 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{1024, 768})))
    {
        return false;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg = {};    
   
    while (true)
    {   
        // true = 메세지가 있었다.
        // false = 메세지가 없었다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            // 메세지 처리
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg); // 메세지가 발생한 윈도우의 프로시저 함수를 호출시킨다. (메세지 처리를 위해서)
            }
        }
        else
        {
            // Game Run
            CCore::GetInst()->update();
        }     
    }       


    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;// MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = L"MyWindowKey";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 윈도우 생성
   // 윈도우 ==> 커널 오브젝트
   // 생성시킨 윈도우의 핸들(ID) 를 받는다.
   g_hWnd = CreateWindowW(L"MyWindowKey", L"MyGame", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, true);
   UpdateWindow(g_hWnd);

   return TRUE;
}


#include "CStageMgr.h"
#include "CStage_Tool.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case ID_TILECOUNT:
            case ID_TILE_SAVE:
            case ID_TILE_LOAD:
            {
                CStage* pCurStage = CStageMgr::GetInst()->GetCurStage();
                CStage_Tool* pToolStage = dynamic_cast<CStage_Tool*>(pCurStage);

                if (nullptr != pToolStage)
                {
                    pToolStage->Proc(wmId);                            
                }                
            }   
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
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
           
      
         
            EndPaint(hWnd, &ps);
        }
        break;

    /*case WM_KEYDOWN:
    
        break;

    case WM_MOUSEMOVE:

        break;
    case WM_TIMER:

        break;*/
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
