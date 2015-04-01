/*
	This program was written by Chris Roxby
*/

#include <iostream>
#include <windows.h>

int main()
{
	SetConsoleTitle( TEXT( "Hotkey Blocker" ));
	bool keepGoing = true;

	int cappedKeys[] =
	{
		VK_DIVIDE, /* Exit Key */
		VK_F1,
		VK_F2,
		VK_F3,
		VK_F4
	};
	const static int arraySize = sizeof(cappedKeys) / sizeof(int);
	printf( "To exit press Num Pad Divide.\n" ); /* Why doesn't this get passed? */

	bool errorKey = false;
	for( int i = 0; i < arraySize; i++ )
	{
		if ( !RegisterHotKey( NULL, i, !MOD_ALT, cappedKeys[i] )) /* ALT is only ignored here b/c of F4 */
		{
			errorKey = true;
			printf( "Something went wrong with hotkey #%d!\n", i );
		}
	}
	if( !errorKey )
		printf( "Ready to rock and roll!\n" );

	MSG msg = {0};
	while (( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 ) || keepGoing )
	{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
		if (msg.message == WM_HOTKEY)
        {
			int daKey = msg.wParam;
			if (daKey == 0 )
				keepGoing = false;
			HWND h = GetForegroundWindow();
			PostMessage( h, WM_KEYDOWN, cappedKeys[daKey], 0 );
			PostMessage( h, WM_KEYUP, cappedKeys[daKey], 0 );
			/*
				I really couldn't care about PostMessage vs Send Message,
				but I want to be sure both messages are received and in that order.
			*/
        }
	}
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}