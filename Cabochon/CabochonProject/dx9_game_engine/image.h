// 2016. 1. 31.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 5.

#ifndef _IMAGE_H
#define _IMAGE_H

#include "graphics.h"
#include "texture_manager.h"

class Image
{
private:
	Graphics* graphics;
	TextureManager* textureManager;
	SpriteData spriteData;
	COLOR_ARGB colorFilter;

	int cols;
	int startFrame;
	int endFrame;
	int currentFrame;
	double frameDelay;
	double animTimer;

	HRESULT hr;
	bool loop;
	bool visible;
	bool initialized;
	bool animComplete;

public:    
	Image();
	virtual ~Image();
	/*
		Image 객체를 초기화 한다.
		Pre :	g = Graphics 를 가리키는 포인터.
				width = 이미지의 픽셀 단위 폭 (0=텍스처 전체의 폭을 사용).
				height = 이미지의 픽셀 단위 높이 0=텍스처 전체의 높이를 사용).
				ncols = 텍스처의 행 수(0은 1과 같다).
				textureM = TextureManager를 가리키는 포인터.		
	*/
	bool initialize(Graphics* g, int width, int height, int ncols, TextureManager* textureM);
	/*
		color 을 필터로 사용해 이미지를 그린다.
		color 매개변수는 선택적이며 default parameter 는 흰색이다.
		pre : spriteBegin()이 호출된다.
		post : spriteEnd()가 호출된다.
	*/
	virtual void draw(COLOR_ARGB color = graphicsNS::WHITE);
	/*
		지정한 SpriteData를 사용해 이미지를 그린다.
		현재 SpriteData.rect는 텍스처를 선택하는 데 사용된다.
		pre : spriteBegin()이 호출된다.
		post : spriteEnd()가 호출된다.
	*/
	virtual void draw(SpriteData sd, COLOR_ARGB color);

	// 게임 아이템을 갱신한다.
	virtual void update(float frameTime);

	//getters
	const virtual SpriteData& getSpriteInfo() { return spriteData; }
	virtual bool getVisible() { return visible; }
	virtual float getX() { return spriteData.x; }
	virtual float getY() { return spriteData.y; }
	virtual float getScale() { return spriteData.scale; }
	virtual int getWidth() { return spriteData.width; }
	virtual int getHeight() { return spriteData.height; }
	virtual float getCenterX() { return spriteData.x + spriteData.width / 2 * getScale(); }
	virtual float getCenterY() { return spriteData.y + spriteData.height / 2 * getScale(); }
	virtual float getDegrees() { return spriteData.angle*(180.0f / (float)PI); }
	virtual float getRadians() { return spriteData.angle; }
	virtual float getFrameDelay() { return frameDelay; }
	virtual int getStartFrame() { return startFrame; }
	virtual int getEndFrame() { return endFrame; }
	virtual int getCurrentFrame() { return currentFrame; }
	virtual RECT getSpriteDataRect(){ return spriteData.rect; }
	virtual bool getAnimationComplete() { return animComplete; }
	virtual COLOR_ARGB getColorFilter() { return colorFilter; }

	//setters
	virtual void setX(float newX) { spriteData.x = newX; }
	virtual void setY(float newY){ spriteData.y = newY; }
	virtual void setScale(float s){ spriteData.scale = s; }
	virtual void setDegrees(float deg){ spriteData.angle = deg*((float)PI / 180.0f); }
	virtual void setRadians(float rad){ spriteData.angle = rad; }
	virtual void setVisible(bool b){ visible = b; }
	virtual void setFrameDelay(float d){ frameDelay = d; }
	virtual void setFrames(int s, int e){ startFrame = s; endFrame = e; }
	virtual void setCurrentFrame(int c);
	virtual void setRect();
	virtual void setSpriteDataRect(RECT r){ spriteData.rect = r; }
	virtual void setLoop(bool lp){ loop = lp; }
	virtual void setAnimationComplete(bool a){ animComplete = a; }
	virtual void setColorFilter(COLOR_ARGB color){ colorFilter = color; }

	// 이미지를 수평으로 뒤집는다. (거울처럼)
	virtual void flipHorizontal(bool flip);
	// 이미지를 수직으로 뒤집는다.
	virtual void flipVertical(bool flip);
};

#endif