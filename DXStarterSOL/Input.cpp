#include "Input.h"

//messages come from windows all the time, should we respond to any specific ones?
LRESULT CALLBACK Input::MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
	switch (msg)
	{
		// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 27:
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			return 0;
		}
	case WM_INPUT:
		//	//grab raw keyboard events
		//	RawInputEvent((HRAWINPUT)lParam);
		break;
		//}
	}

	//default message handling (resize window, full screen, etc)
	return WinUtil::Get().DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

/*
Tell Windows we want raw keyboard input as well as the usual stuff
*/
void Input::RegisterForRawInput()
{
	RAWINPUTDEVICE rid;
	//these ids trigger mouse input
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	// adds HID keyboard and also optionally ignores legacy keyboard messages
	rid.dwFlags = RIDEV_INPUTSINK;// RIDEV_NOLEGACY;   
	rid.hwndTarget = WinUtil::Get().GetMainWnd();

	// RIDEV_NOLEGACY will stop normal message pump WM_CHAR type messages
	// sometimes we might want that, for now we'll leave it, then we can
	// still use the normal message pump for things like player name entry

	if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE) {
		MessageBox(0, "Cannot get keyboard and mouse input", 0, 0);
		assert(false);
	}
}

//get the absolute mouse position, not raw input, just standard windows is fine
void Input::GetMousePosAbsolute(Vector2& pos)
{
	POINT mpos;
	if (GetCursorPos(&mpos))
	{
		if (ScreenToClient(WinUtil::Get().GetMainWnd(), &mpos))
		{
			pos = Vector2((float)mpos.x, (float)mpos.y);
		}
	}
}
//watch for any mouse button presses, bypass the usual windows message
//and get the raw data
void Input::RawInputEvent(HRAWINPUT rawInput)
{
	UINT dwSize(0);

	UINT res = GetRawInputData(rawInput, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
	if (res != 0)
		return;//bad input so ignore it

	if (dwSize >= RAWBUFF_SIZE)
	{
		DBOUT("Buffer too small. Is " << RAWBUFF_SIZE << " wants " << dwSize);
		assert(false);
	}

	if (GetRawInputData(rawInput, RID_INPUT, inBuffer, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
	{
		DBOUT("GetRawInputData failed");
		assert(false);
	}

	RAWINPUT* raw = (RAWINPUT*)inBuffer;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		unsigned short flags = raw->data.mouse.usButtonFlags;

		if (flags & RI_MOUSE_LEFT_BUTTON_DOWN)
			mButtons[LBUTTON] = true;
		if (flags & RI_MOUSE_LEFT_BUTTON_UP)
			mButtons[LBUTTON] = false;
		if (flags & RI_MOUSE_MIDDLE_BUTTON_DOWN)
			mButtons[MBUTTON] = true;
		if (flags & RI_MOUSE_MIDDLE_BUTTON_UP)
			mButtons[MBUTTON] = false;
		if (flags & RI_MOUSE_RIGHT_BUTTON_DOWN)
			mButtons[RBUTTON] = true;
		if (flags & RI_MOUSE_RIGHT_BUTTON_UP)
			mButtons[RBUTTON] = false;

		Vector2 last(mMouseScreen);
		GetMousePosAbsolute(mMouseScreen);
		mMouseMove = mMouseScreen - last;
	}
}
