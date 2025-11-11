#include "Text.h"

void Text::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	RECT dim = rm.findFont(fontName)->MeasureDrawBounds(msg.c_str(), Vector2(0, 0));
	rm.findFont(fontName)->DrawString(&batch, msg.c_str(), pos, colour, 0, { 0, 0 }, scale);
}
