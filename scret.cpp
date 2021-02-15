#include <Windows.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
void ChangeTitleThread()
{
	srand(time(0)); //Helps the rand() function out so it won't produce the same number every time.
	while (1) //Enter our loop.
	{
		int random1 = rand() % 999999 + 100000; //Pick a random number between these two
		int random2 = rand() % 52999 + 1510; //...
		int random3 = rand() % 614613455 + 513;
		int random4 = rand() % 613463176 + 3146662;
		std::string title; //Declare our title string
		title.append(std::to_string(random1)); //Append each number to our title
		title.append(std::to_string(random2)); //...
		title.append(std::to_string(random3));
		title.append(std::to_string(random4));
		SetConsoleTitleA(title.c_str()); //Set our console title to our string, use .c_str() to turn it into a LPCSTR.
		Sleep(500); //Sleep for half a second.
	}
}
 
void DetectDebuggerThread()
{
	BOOL result; //Create a result boolean for our result to be stored.
	LPCSTR DetectedWindows[] = { "x64dbg", "IDA: Quick start", "IDA v6.8.150423" }; //Add your own debuggers!
	//Just finding windows may not be enough, so try to include your own process checker.
 
	while (1) //Enter our loop.
	{
		if (IsDebuggerPresent()) //Our first check, probably the simpliest.
		{
			printf("Debuger found! Exitting...");
			Sleep(1500);
			exit(0);
		}
		CheckRemoteDebuggerPresent(GetCurrentProcess(), &result); //Get a handle to our current process and send our result to the our boolean.
		if (result || result == 1) //Check to see if our result is true.
		{
			printf("Debuger found! Exitting...");
			Sleep(1500);
			exit(0);
		}
		SetLastError(0); //Set last error to 0 so it won't conflict with our check.
		OutputDebugStringA("Using a debugger?"); //Send a little message to the debugger.
		if (GetLastError() != 0) //If the message passed without error (Meaning it was sent to the debugger)
		{
			printf("Debuger found! Exitting...");
			Sleep(1500);
			exit(0);
		}
 
		for (int i = 0; i < 3; i++) //Loop thru our array of detected debugger windows.
		{
			if (FindWindowA(0, DetectedWindows[i]) != 0) //Check to see if FindWindow found a debugger that matches our name.
			{
				printf("Debuger found! Exitting...");
				Sleep(1500);
				exit(0);
			}
		}
	}
}
 
void main()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DetectDebuggerThread, 0, 0, 0); //Create our threads
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ChangeTitleThread, 0, 0, 0);
 
	//put your code here (replace while(1) pls)
	while (1)
	{
		
	}
}
