/***********************************************************/
//						SDL_Text.h
/***********************************************************/
#include "Globals.h"

// Struct for holding Text
/************************************************************/
// Rendering happens in the following order
// 1. Set text color
// 2. Create the message
// 3. Render to texture
// 4. Query the texture to set the box rects
// 5. Set the text position with box rect
/************************************************************/
struct Text
{
	SDL_Texture* texture;
	SDL_Rect box;
	SDL_Color textColor;
	SDL_Surface* message;
	Text()				{ texture = NULL; box = { 0, 0, 0, 0 }; }
	~Text()				{ SDL_DestroyTexture(texture); texture = NULL; }
	void clearTexture()	{ texture = NULL; box.w = 0; box.h = 0; }

	// Setters
	void setFontColor(int r, int g, int b)					{ textColor = { r, g, b }; }
	void setTextPosition(int a, int b)						{ box = { a, b }; }
	void queryTexture()										{ SDL_QueryTexture(texture, NULL, NULL, &box.w, &box.h); }
	void createMessage(TTF_Font *font, char *newMessage)	{ message = TTF_RenderText_Solid(font, newMessage, textColor); }
	void renderText(SDL_Renderer* render)					{ SDL_CreateTextureFromSurface(render, message); }
};

class SDLText
{
private:
public:
	Text renderToTexture(SDL_Renderer*, TTF_Font *font, string);
	void setColor(SDL_Texture* texture, Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_Texture* texture, SDL_BlendMode blending);
	void setAlpha(SDL_Texture* texture, Uint8 alpha);
	TTF_Font *loadFont(char *, int);
	bool initText();
};