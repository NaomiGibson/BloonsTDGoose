#pragma once
#include <d3d11.h>
#include "SimpleMath.h"
#include "WindowUtils.h"
#include "D3DUtil.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/*
Intercept and process raw input data events
*/
class Input {
private:
	enum {
		RAWBUFF_SIZE = 512, MAX_BUTTONS = 3, LBUTTON = 0, MBUTTON = 1, RBUTTON = 2
	};
	unsigned char inBuffer[RAWBUFF_SIZE];
	bool mButtons[MAX_BUTTONS];		//button presses
	Vector2 mMouseScreen;			//absolute position on screen
	Vector2 mMouseMove;				//amount the mouse moved last update
public:

	//messages come from windows all the time, should we respond to any specific ones?
	LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Tell Windows we want raw keyboard input as well as the usual stuff
	void RegisterForRawInput();
	//get the absolute mouse position, not raw input, just standard windows is fine
	void GetMousePosAbsolute(Vector2& pos);
	//watch for any mouse button presses, bypass the usual windows message
	//and get the raw data
	void RawInputEvent(HRAWINPUT rawInput);
	const bool& getButtonPresses() { return mButtons; }
	const Vector2& getMouseScreenPos() { return mMouseScreen; }
	const Vector2& getMouseMove() { return mMouseMove; }
};