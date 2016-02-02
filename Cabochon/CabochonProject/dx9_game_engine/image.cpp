// 2016. 1. 31.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// �ڵ��� �Ϻδ� å�� �������� �ʾ�, �ҽ��ڵ带 ���� ���۷������� �ٿ�޾� �ٿ�����. Ch 5.

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

		// ��ü ���� ���.
		if (width == 0)
			width = textureManager->getWidth();
		spriteData.width = width;
		// ��ü ���̸� ���.
		if (height == 0)
			height = textureManager->getHeight();
		spriteData.height = height;
		
		cols = ncols;
		// cols�� 0�̶�� 1�� ���.
		if (cols == 0)
			cols = 1;
		
		//currentFrame �� �׸��� ���� spriteData.rect�� �����Ѵ�.
		spriteData.rect.left = (currentFrame % cols) * spriteData.width;
		// ������ �𼭸� + 1
		spriteData.rect.right = spriteData.rect.left + spriteData.width;
		spriteData.rect.top = (currentFrame / cols) * spriteData.height;
		// �Ʒ��� �𼭸� +1
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
	�Ϲ������� ������ �� 1 �� ȣ��ȴ�.
	frameTime�� �̵��̳� �ִϸ��̼��� �ӵ��� �����ϴ� �� ���ȴ�.
*/
void Image::update(float frameTime)
{
	// �ִϸ��̼� ������ �ִ� ��������Ʈ���
	if (endFrame - startFrame > 0)
	{
		animTimer += frameTime;	//��ü ��� �ð�.
		if (animTimer > frameDelay)
		{
			animTimer -= frameDelay;
			currentFrame++;

			if (currentFrame < startFrame || currentFrame > endFrame)
			{
				// �ݺ��� �ִ� ��������Ʈ ���
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

// �̹����� ���� �������� �����Ѵ�.
void Image::setCurrentFrame(int c)
{
	if (c >= 0)
	{
		currentFrame = c;
		animComplete = false;
		setRect(); // spriteData.rect ����.
	}
}

// currentFrame�� �׸� spriteData.rect�� �����Ѵ�.
inline void Image::setRect()
{
	spriteData.rect.left = (currentFrame % cols) * spriteData.width;
	// ������ �𼭸� + 1
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (currentFrame / cols) * spriteData.height;
	// �Ʒ��� �𼭸� + 1
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
}