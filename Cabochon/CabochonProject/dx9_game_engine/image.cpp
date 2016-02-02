// 2016. 1. 31.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 코드의 일부는 책에 나와있지 않아, 소스코드를 위의 레퍼런스에서 다운받아 붙여넣음. Ch 5.

#include "image.h"

Image::Image()
{
	initialized = false;
	spriteData.width = 2;
	spriteData.height = 2;
	spriteData.x = 0.0;
	spriteData.y = 0.0;
	spriteData.scale = 1.0;
	spriteData.angle = 0.0;
	spriteData.rect.left = 0;       // used to select one frame from multi-frame image
	spriteData.rect.top = 0;
	spriteData.rect.right = spriteData.width;
	spriteData.rect.bottom = spriteData.height;
	spriteData.texture = NULL;      // the sprite texture (picture)
	spriteData.flipHorizontal = false;
	spriteData.flipVertical = false;
	cols = 1;
	textureManager = NULL;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	frameDelay = 1.0;               // default to 1 second per frame of animation
	animTimer = 0.0;
	visible = true;                 // the image is visible
	loop = true;                    // loop frames
	animComplete = false;
	graphics = NULL;                // link to graphics system
	colorFilter = graphicsNS::WHITE; // WHITE for no change
}

Image::~Image()
{}

bool Image::initialize(Graphics* g, int width, int height, int ncols, TextureManager* textureM)
{
	try {
		graphics = g;
		textureManager = textureM;
		spriteData.texture = textureManager->getTexture();

		// 전체 폭을 사용.
		if (width == 0)
			width = textureManager->getWidth();
		spriteData.width = width;
		// 전체 높이를 사용.
		if (height == 0)
			height = textureManager->getHeight();
		spriteData.height = height;
		
		cols = ncols;
		// cols가 0이라면 1을 사용.
		if (cols == 0)
			cols = 1;
		
		//currentFrame 을 그리기 위해 spriteData.rect를 구성한다.
		spriteData.rect.left = (currentFrame % cols) * spriteData.width;
		// 오른쪽 모서리 + 1
		spriteData.rect.right = spriteData.rect.left + spriteData.width;
		spriteData.rect.top = (currentFrame / cols) * spriteData.height;
		// 아래쪽 모서리 +1
		spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
	}
	catch (...) { return false; }
	initialized = true;
	return true;
}

void Image::draw(COLOR_ARGB color)
{
	if (!visible || graphics == nullptr)
		return;
	spriteData.texture = textureManager->getTexture();
	if (color == graphicsNS::FILTER)
		graphics->drawSprite(spriteData, colorFilter);
	else
		graphics->drawSprite(spriteData, color);
}

void Image::draw(SpriteData sd, COLOR_ARGB color)
{
	if (!visible || graphics == nullptr)
		return;
	sd.rect = spriteData.rect;
	sd.texture = textureManager->getTexture();
	if (color == graphicsNS::FILTER)
		graphics->drawSprite(sd, colorFilter);
	else
		graphics->drawSprite(sd, color);
}

void Image::flipHorizontal(bool flip)
{
	spriteData.flipHorizontal = flip;
}

void Image::flipVertical(bool flip)
{
	spriteData.flipVertical = flip;
}

/*
	일반적으로 프레임 당 1 번 호출된다.
	frameTime은 이동이나 애니메이션의 속도를 조절하는 데 사용된다.
*/
void Image::update(float frameTime)
{
	// 애니메이션 동작이 있는 스프라이트라면
	if (endFrame - startFrame > 0)
	{
		animTimer += frameTime;	//전체 경과 시간.
		if (animTimer > frameDelay)
		{
			animTimer -= frameDelay;
			currentFrame++;

			if (currentFrame < startFrame || currentFrame > endFrame)
			{
				// 반복이 있는 스프라이트 라면
				if (loop == true)
					currentFrame = startFrame;
				else
				{
					currentFrame = endFrame;
					animComplete = true;
				}
				setRect();
			}
		}
	}
}

// 이미지의 현재 프레임을 설정한다.
void Image::setCurrentFrame(int c)
{
	if (c >= 0)
	{
		currentFrame = c;
		animComplete = false;
		setRect(); // spriteData.rect 설정.
	}
}

// currentFrame에 그릴 spriteData.rect를 설정한다.
inline void Image::setRect()
{
	spriteData.rect.left = (currentFrame % cols) * spriteData.width;
	// 오른쪽 모서리 + 1
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (currentFrame / cols) * spriteData.height;
	// 아래쪽 모서리 + 1
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
}