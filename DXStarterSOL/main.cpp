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


/*
Blank solution - setup DX11 and blank the screen
*/

const int MAX_COLOURS = 8;
Vector4 gColours[MAX_COLOURS];
int gCycle = 0;
float gTime = 0;
DirectX::SpriteFont *gpFont = nullptr, *gpFont2 = nullptr;
DirectX::SpriteBatch *gpSpriteBatch = nullptr;
float gResTimer = 0;
int gFrameCounter = 0;
float gFrameTimer = 0;

void InitGame(MyD3D& d3d)
{
	gColours[0] = Colors::White;
	gColours[1] = Colors::Black;
	gColours[2] = Colors::Red;
	gColours[3] = Colors::Green;
	gColours[4] = Colors::Blue;
	gColours[5] = Colors::Yellow;
	gColours[6] = Colors::Cyan;
	gColours[7] = Colors::Magenta;

	gpSpriteBatch = new SpriteBatch(&d3d.GetDeviceCtx());
	assert(gpSpriteBatch);


}


//any memory or resources we made need releasing at the end
void ReleaseGame()
{
	delete gpFont;
	gpFont = nullptr;

	delete gpFont2;
	gpFont2 = nullptr;

	delete gpSpriteBatch;
	gpSpriteBatch = nullptr;
}

//called over and over, use it to update game logic
void Update(float dTime, MyD3D& d3d)
{
	gTime += dTime;
	if (gTime > 0.5f)
	{
		gCycle++;
		if (gCycle >= MAX_COLOURS)
			gCycle = 0;
		gTime = 0;
	}
}

//called over and over, use it to render things
void Render(float dTime, MyD3D& d3d)
{
	WinUtil& wu = WinUtil::Get();
	float alpha = (float)wu.GetData().clientWidth/(1024 - wu.GetData().minClientWidth);
	if (alpha > 1)
		alpha = 1;
	Vector4 colour = Colours::Green + (Colours::Red - Colours::Green) * alpha;
	
	//d3d.BeginRender(gColours[gCycle]);
	d3d.BeginRender(colour);
	gpSpriteBatch->Begin();

	Vector2 scrn{ (float)wu.GetData().clientWidth, (float)wu.GetData().clientHeight };
	string msg = "POOPER";
	Vector2 pos = Vector2(0, 0);
	RECT dim = gpFont->MeasureDrawBounds(msg.c_str(), Vector2(0,0));
	pos = Vector2{ (scrn.x / 2) - (dim.right / 2), (scrn.y / 2) - (dim.bottom / 2) };
	gpFont->DrawString(gpSpriteBatch, msg.c_str(), pos);

	msg = "FEZZ";
	RECT dim2 = gpFont2->MeasureDrawBounds(msg.c_str(), Vector2(0,0));
	pos = Vector2{ (scrn.x / 2), pos.y + (dim2.bottom-dim2.top)*1.2f };
	gpFont2->DrawString(gpSpriteBatch, msg.c_str(), pos, Colours::Black, 0, Vector2((float)dim2.right/2.f,0));
	 
	if (gResTimer > GetClock())
	{
		stringstream ss;
		ss << "New resolution:" << wu.GetData().clientWidth << " x " << wu.GetData().clientHeight;
		pos.y += (dim2.bottom - dim2.top) * 1.2f;
		RECT dim3 = gpFont2->MeasureDrawBounds(ss.str().c_str(), Vector2(0,0));
		gpFont2->DrawString(gpSpriteBatch, ss.str().c_str(), pos, Colours::Black, 0, Vector2((float)dim3.right / 2.f, 0));
	}
	 
	static int fps = 0;
	if (GetClock() > gFrameTimer)
	{
		fps = gFrameCounter;
		gFrameCounter = 0;
		gFrameTimer = GetClock() + 1;
	}

	wstringstream ss;
	ss.str(L"");
	ss << L"FPS: " << setfill(L' ') << setw(5) << fps << L" GPU:" << d3d.GetGPUDesc();
	RECT dim3 = gpFont->MeasureDrawBounds(ss.str().c_str(), Vector2(0,0));
	pos = Vector2(0,wu.GetData().clientHeight - (float)dim3.bottom*1.2f );
	gpFont->DrawString(gpSpriteBatch, ss.str().c_str(), pos, Colours::Black, 0, Vector2(0, 0));

	gpSpriteBatch->End();
	d3d.EndRender();
}

//if ALT+ENTER or resize or drag window we might want do
//something like pause the game perhaps, but we definitely
//need to let D3D know what's happened (OnResize_Default).
void OnResize(int screenWidth, int screenHeight, MyD3D& d3d)
{
	gResTimer = GetClock() + 2;
	d3d.OnResize_Default(screenWidth, screenHeight);
}

//messages come from windows all the time, should we respond to any specific ones?
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
	}

	//default message handling (resize window, full screen, etc)
	return WinUtil::Get().DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

//main entry point for the game
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{

	int w(1024), h(768);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Fezzy", MainWndProc, true))
		assert(false);

	MyD3D d3d;
	if (!d3d.InitDirect3D(OnResize))
		assert(false);
	WinUtil::Get().SetD3D(d3d);
	InitGame(d3d);

	bool canUpdateRender;
	float dTime = 0;
	while (WinUtil::Get().BeginLoop(canUpdateRender))
	{
		if (canUpdateRender)
		{
			Update(dTime, d3d);
			Render(dTime, d3d);
		}
		dTime = WinUtil::Get().EndLoop(canUpdateRender);
		gFrameCounter++;
	}

	ReleaseGame();
	d3d.ReleaseD3D(true);	
	return 0;
}