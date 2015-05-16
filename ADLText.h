/***********************************************************/
//						SDL_Text.h
/***********************************************************/
#include "Globals.h"

// Struct for holding Text
struct Text
{
	SDL_Texture* texture;
	SDL_Rect box;
	SDL_Color textColor;
	Text()				{ texture = NULL; box = { 0, 0, 0, 0 }; }
	~Text()				{ SDL_DestroyTexture(texture); texture = NULL; }
	void clearTexture()	{ texture = NULL; box.w = 0; box.h = 0; }
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
	Text setFontColor(int, int, int);
	Text setFontPosition(int, int);
};