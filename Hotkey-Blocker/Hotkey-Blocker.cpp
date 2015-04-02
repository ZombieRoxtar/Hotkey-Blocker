/*
	This program was written by Chris Roxby
*/

#include <iostream>
#include <windows.h>
using namespace std;

bool keepGoing = true;
int cappedKeys[] =
{
        VK_DIVIDE, /* Exit Key */
        VK_F1,
        VK_F2,
        VK_F3,
        VK_F4
};
const static auto arraySize = sizeof(cappedKeys) / sizeof(int);

/* This is our message callback */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main()
{
	/* Create window class */
    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = "MessageWindowClass";
    RegisterClassEx(&wc);

    /* Create window (uses HWND_MESSAGE as the parent window to create message only window) */
    HWND messageWindow = CreateWindow(wc.lpszClassName, "HotkeyMesageWindow", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
    if(!messageWindow)
    {
        cerr<< "Can't create a window for messaging!" <<endl;
        exit(1);
    }

	SetConsoleTitle("Hotkey Blocker");
	printf( "To exit press Num Pad Divide.\n" ); /* Why doesn't this key get passed? */

	bool errorKey = false;
	for( int i = 0; i < arraySize; i++ )
	{
		if ( !RegisterHotKey( NULL, i, !MOD_ALT, cappedKeys[i] )) /* ALT is only ignored here b/c of F4 */
		{
			errorKey = true;
			printf( "Something went wrong with hotkey #%d!\n", i );
                        /* Why not terminate the program here? */
		}
	}
	if( !errorKey )
		printf( "Ready to rock and roll!\n" );

	/* Main message loop */
	MSG msg;
	do
	{
            if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 )
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
	    Sleep(10);
	}while(keepGoing);
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int daKey;
    HWND fgWindow;

    switch (message)
    {
    case WM_HOTKEY:
        daKey = msg.wParam;
        if (daKey == 0 )
                keepGoing = false;
        fgWindow = GetForegroundWindow();
        PostMessage( h, WM_KEYDOWN, cappedKeys[daKey], 0 );
        PostMessage( h, WM_KEYUP, cappedKeys[daKey], 0 );
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
