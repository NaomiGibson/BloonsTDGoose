#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <iomanip>

#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

#include "Game.h"
//#include "Input.h"


//if ALT+ENTER or resize or drag window we might want do
//something like pause the game perhaps, but we definitely
//need to let D3D know what's happened (OnResize_Default).
void OnResize(int screenWidth, int screenHeight, MyD3D& d3d, bool isFullscreen)
{
	//gResTimer = GetClock() + 2;
	d3d.OnResize_Default(screenWidth, screenHeight, isFullscreen);
}
/*
Intercept and process raw input data events
*/
enum {
	RAWBUFF_SIZE = 512, MAX_BUTTONS = 3, LBUTTON = 0, MBUTTON = 1, RBUTTON = 2
};
unsigned char inBuffer[RAWBUFF_SIZE];
bool mButtons[MAX_BUTTONS];		//button presses
Vector2 mMouseScreen;			//absolute position on screen
Vector2 mMouseMove;				//amount the mouse moved last update


//get the absolute mouse position, not raw input, just standard windows is fine
void GetMousePosAbsolute(Vector2& pos)
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

//when tracking relative mouse motion, reset it after every update
void EndOfUpdate()
{
	mMouseMove = Vector2(0, 0);
}

//watch for any mouse button presses, bypass the usual windows message
//and get the raw data
void RawInputEvent(HRAWINPUT rawInput)
{
	UINT dwSize;

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

//messages come from windows all the time, should we respond to any specific ones?
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
	switch (msg)
	{
		// Respond to a keyboard event.
	case WM_CHAR:
		//switch (wParam)
		//{
		//case 27:
		//case 'q':
		//case 'Q':
		//	PostQuitMessage(0);
		//	break;
		//}
	case WM_INPUT:
		//grab raw keyboard events
		RawInputEvent((HRAWINPUT)lParam);
		break;
	}

	//default message handling (resize window, full screen, etc)
	return WinUtil::Get().DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

/*
Tell Windows we want raw keyboard input as well as the usual stuff
*/
void RegisterForRawInput()
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


//main entry point for the game
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	//Input input;
	//input.RegisterForRawInput();

	int w(1920), h(1080);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Bloons TD Goose", MainWndProc, true))
		assert(false);

	MyD3D d3d;
	if (!d3d.InitDirect3D(OnResize))
		assert(false);
	if (!d3d.InitDirect3D(OnResize))
		assert(false);
	WinUtil::Get().SetD3D(d3d);
	Game game(&d3d);
	game.init();

	RegisterForRawInput();

	bool canUpdateRender;
	float dTime = 0;
	while (WinUtil::Get().BeginLoop(canUpdateRender))
	{
		if (canUpdateRender)
		{
			game.update(dTime, mMouseScreen, mButtons[LBUTTON], mButtons); // dTime, d3d
			game.render(dTime); // dTime, d3d
		}
		dTime = WinUtil::Get().EndLoop(canUpdateRender);
		// gFrameCounter++;
	}

	game.release();
	d3d.ReleaseD3D(true);

	return 0;
}