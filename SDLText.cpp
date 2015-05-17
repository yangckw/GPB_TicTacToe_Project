#include "ADLText.h"

void SDLText::setColor(SDL_Texture* texture, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void SDLText::setBlendMode(SDL_Texture* texture, SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(texture, blending);
}

void SDLText::setAlpha(SDL_Texture* texture, Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}

Text SDLText::renderToTexture(SDL_Renderer* render, TTF_Font *font, string myText)
{
	SDL_Texture* newTexture = NULL;
	Text text;							// Text Object
	
	if (text.texture != NULL)	{ text.clearTexture(); }

	//Load image at specified path
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, myText.c_str(), text.textColor);

	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(render, textSurface);
		if (newTexture != NULL)
		{
			//Get image dimensions
			text.box.w = textSurface->w;
			text.box.h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}

	text.texture = newTexture; // Load everything into text

	return text;
}

TTF_Font *SDLText::loadFont(char *fontName, int size)
{
	TTF_Font *tempFont;
	tempFont = TTF_OpenFont(fontName, size);

	return tempFont;
}

bool SDLText::initText()
{
	bool success = true;

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
		success = false;
	}
	return success;
}