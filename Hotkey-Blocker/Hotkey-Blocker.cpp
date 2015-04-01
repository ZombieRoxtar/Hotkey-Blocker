/*
	This program was written by Chris Roxby
*/

#include <stdio.h>
#include "Windows.h"

void main()
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
	int arraySize = sizeof(cappedKeys) / sizeof(int); /* I thought a managed array would make the program easier to edit later? */
	printf( "To exit press Num Pad Divide twice.\n" ); /* Why do I need press this one twice? */

	bool errorKey = false;
	for (int i = 0; i < arraySize; i++)
	{
		if ( !RegisterHotKey( NULL, i, !MOD_ALT, cappedKeys[i] )) /* ALT is only ignored here b/c of F4 */
		{
			errorKey = true;
			printf( "Something went wrong with hotkey #%d!\n", i );
		}
	}
	if( !errorKey)
	{
		printf( "Ready to rock and roll!\n" );
	}

	MSG msg = {0};
	do
	{
		if (msg.message == WM_HOTKEY)
        {
			int daKey = 0;
			switch (msg.wParam)
			{
			case 0:
				keepGoing = false;
				break;
			case 1:
				daKey = 1;
				break;
			case 2:
				daKey = 2;
				break;
			case 3:
				daKey = 3;
				break;
			case 4:
				daKey = 4;
			}
				HWND h = GetForegroundWindow();
				PostMessage( h, WM_KEYDOWN, cappedKeys[daKey], 0 );
				PostMessage( h, WM_KEYUP, cappedKeys[daKey], 0 );
				/*
					I really couldn't care about PostMessage vs Send Message,
					but I want to be sure both messages are received and in that order.
				*/
        }
	} while (( GetMessage(&msg, NULL, 0, 0) != 0 ) && keepGoing );
}