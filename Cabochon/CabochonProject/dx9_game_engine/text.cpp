// 2016. 2. 10.

#include "text.h"

Text::Text()
	:Image()
{
	file = NULL;
	graphics = NULL;
	color = graphicsNS::WHITE;
	backColor = TRANSCOLOR;
	align = textNS::LEFT;
	width = textNS::GRID_WIDTH - 3;
	height = textNS::GRID_HEIGHT - 3;
	fontHeight = textNS::FONT_HEIGHT;
	spriteData.width = 0;
	spriteData.height = 0;
	spriteData.rect.bottom = 1;
	spriteData.rect.right = 1;
	for (int row = 0; row < textNS::ROWS; row++)
	{
		for (int col = 0; col < textNS::COLUMNS; col++)
		{
			fontData[row][col].left = MAXINT;
			fontData[row][col].right = 0;
		}
	}
	proportional = false;
	proportionalSpacing = textNS::PROPORTIONAL_SPACING;
	underline = false;
	bold = false;
	tabSize = textNS::TAB_SIZE;
}

Text::~Text()
{
	Image::Image();
}

bool Text::initialize(Graphics*g, const char* file)
{
	try {
		graphics = g;
		UINT w, h;

		// 글꼴 텍스처를 불러와 각 문자의 정확한 위치를 찾기 위해 픽셀마다 검사를 수행한다.
		// 글꼴 텍스처를 시스템 메모리로 불러 와 락을 걸 수 있게 한다.
		HRESULT result = graphics->loadTextureSystemMem(file, TRANSCOLOR, w, h, textureData);
		if (FAILED(result))
		{
			SAFE_RELEASE(textureData);
			return false;
		}

		// textureData.width , textureData.height 는 글꼴 텍스처 전체의 크기를 포함하고 있다.
		// 각 문자는 1px 크기의 경계선을 가지며, ROWS * COLS 개의 문자가 있다.
		// 픽셀 데이터에 접근 하기 위해 필요한 글꼴 텍스처에 락을 건다.
		D3DLOCKED_RECT rect;
		result = textureData->LockRect(0, &rect, NULL, D3DLOCK_READONLY);
		if (FAILED(result))
		{
			SAFE_RELEASE(textureData);
			return false;
		}

		// 글꼴에 있는 문자의 각 행에 대해
		for (DWORD row = 0; row < textNS::ROWS; row++)
		{
			// 글꼴에 있는 문자의 각 열에 대해
			for (DWORD col = 0; col < textNS::COLUMNS; col++)
			{
				fontData[row][col].left = MAXINT;				// font Data를  초기화 한다.
				fontData[row][col].right = 0;

				// 각 문자를 픽셀 단위로 처리한다.
				// for y = 위쪽 픽셀; y <= 아래쪽 픽셀; y++
				for (DWORD y = row*textNS::GRID_HEIGHT + 1; y < (row + 1)*textNS::GRID_HEIGHT - 1; y++)
				{
					// 텍스처의 스캔라인 시작점을 가리키는 포인터를 가져온다.
					DWORD* pBits = (DWORD*)((BYTE*)rect.pBits + y*rect.Pitch);

					// 해당 픽셀라인을 처리한다.
					for (DWORD x = col * textNS::GRID_WIDTH + 1; x < (col + 1)*textNS::GRID_WIDTH - 1; x++)
					{
						// 해당 픽셀을 가져 온다.
						DWORD dwPixel = pBits[x];
						// 알파 값이 투명이 아니라면
						if ((dwPixel & 0xff000000) != 0x00)
						{
							// 해당 픽셀이 더 왼쪽에 있다면 문자의 왼쪽 모서리로 저장한다. 
							if (x < fontData[row][col].left)
								fontData[row][col].left = x;
							// 해당 픽셀이 더 오른쪽에 있다면 문자의 오른쪽 모서리로 저장한다.
							if (x>fontData[row][col].right)
								fontData[row][col].right = x;
						}
					}
				}
			}
		}

		// 텍스처에 대한 작업이 끝났으므로, 락을 해제한다.
		textureData->UnlockRect(0);
		// 글꼴 텍스처를 해제한다.
		// 글꼴 간격을 얻기 위해 필요했었다.
		SAFE_RELEASE(textureData);
		// 사용을 위해 글꼴 이미지를 텍스처 매니저로 불러온다.
		if (!fontTexture.initialize(graphics, file))
			return false;
		if (!Image::initialize(graphics, textNS::FONT_WIDTH, textNS::FONT_HEIGHT, 0, &fontTexture))
			return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void Text::setXY(int x2, int y2)
{
	if (x2 < 0 || y2 < 0)
		return;
	spriteData.x = (float)x2;
	spriteData.y = (float)y2;
}

void Text::print(const std::string& str)
{
	print(str, (int)spriteData.x, (int)spriteData.y);
}

void Text::print(const std::string& str, int x, int y, textNS::Alignment al)
{
	align = al;
	print(str, x, y);
	align = textNS::LEFT;
}

void Text::print(const std::string& str, int x, int y)
{
	UCHAR ch = 0, chN = 0;
	std::string str2;
	width = textNS::FONT_WIDTH;
	int scaledWidth = static_cast<int>(textNS::FONT_WIDTH*spriteData.scale);
	float saveY = 0;
	int tabX = 0, tabW = 0;

	spriteData.x = (float)x;
	spriteData.y = (float)y;
	doAlign(str);

	for (UINT i = 0; i < str.length(); i++)
	{
		ch = str.at(i); 

		// 표시 가능한 문자라면
		if (ch > textNS::MIN_CHAR && ch <= textNS::MAX_CHAR)
		{
			chN = ch - textNS::MIN_CHAR;			// min_char 인덱스를 0으로 만든다.
			spriteData.rect.top = chN / textNS::COLUMNS * textNS::GRID_HEIGHT + 1;
			spriteData.rect.bottom = spriteData.rect.top + textNS::FONT_HEIGHT;
			if (proportional)
			{
				spriteData.rect.left = fontData[chN / textNS::COLUMNS][chN % textNS::COLUMNS].left;
				// DirectX는 오른쪽 + 1 을 원한다.
				spriteData.rect.right = fontData[chN / textNS::COLUMNS][chN % textNS::COLUMNS].right + 1;
				width = spriteData.rect.right - spriteData.rect.left;
				// 폭 전체를 사용하는 문자라면 간격을 추가하지 않는다.
				if (width >= textNS::FONT_WIDTH)
				{
					width = textNS::FONT_WIDTH;		// 폭을 제한한다.
					spriteData.rect.left = chN % textNS::COLUMNS * textNS::GRID_WIDTH + 1;
					spriteData.rect.right = spriteData.rect.left + textNS::FONT_WIDTH;
				}
				// 폭 전체를 사용하지 않는다면 문자 사이에 간격을 추가한다.
				else
					width += proportionalSpacing;
				scaledWidth = static_cast<int>(width*spriteData.scale);
				drawChar(ch);
			}
			// 고정된 피치.
			else
			{
				width = textNS::FONT_WIDTH;
				spriteData.rect.left = chN % textNS::COLUMNS * textNS::GRID_WIDTH + 1;
				spriteData.rect.right = spriteData.rect.left + textNS::FONT_WIDTH;
				drawChar(ch);
			}
			spriteData.x += scaledWidth;
		}
		// 표시할 수 없는 문자.
		else
		{
			switch (ch)
			{
			case ' ':		// 공백.
				if (proportional)
				{
					width = textNS::FONT_WIDTH / 2;
					scaledWidth = static_cast<int>(width*spriteData.scale);
				}
				drawChar(' ');
				spriteData.x += scaledWidth;
				break;
			// 개행 문자는 한 줄을 아래로 내리고 왼쪽 모서리를 화면의 왼쪽 모서리가 아닌 화면 내 X 위치의 시작점으로 설정한다.
			case '\n':		// 개행 문자.
				spriteData.x = (float)x;
				spriteData.y += static_cast<int>(height*spriteData.scale);
				saveY = spriteData.y;
				str2 = str.substr(i, str.length());
				doAlign(str2);
				spriteData.y = saveY;
				break;
			// X 위치의 시작점을 반환한다.
			case '\r':		// 캐리지 리턴.
				spriteData.x = (float)x;
				str2 = str.substr(i, str.length());
				doAlign(str2);
				break;
			case '\t':		// 탭.
				width = textNS::FONT_WIDTH;
				scaledWidth = static_cast<int>(width*spriteData.scale);
				tabX = static_cast<int>(spriteData.x) / (scaledWidth*tabSize);
				tabX = (tabX + 1)*scaledWidth*tabSize;
				tabW = tabX - static_cast<int>(spriteData.x);
				while (tabW > 0)
				{
					if (tabW >= scaledWidth)
					{
						drawChar(' ');
						spriteData.x += scaledWidth;
					}
					else
					{
						// 문자의 소수 부분은 탭의 위치를 통해 정렬한다.
						width = tabW;
						drawChar(' ');
						spriteData.x += tabW;
					}
					tabW -= scaledWidth;
				}
				break;
			case '\b':		// 백스페이스.
				spriteData.x -= scaledWidth;
				if (spriteData.x < 0)
					spriteData.x = 0;
				break;
			case '\v':		// 수직 탭.
				spriteData.y += static_cast<int>(height*spriteData.scale);
				break;
			case 0x01:		// 글꼴 서명 문자.
				spriteData.rect.top = 1;
				spriteData.rect.bottom = 1 + textNS::FONT_HEIGHT;
				spriteData.rect.left = 1;
				spriteData.rect.right = 1 + textNS::FONT_WIDTH;
				draw(spriteData);
				spriteData.x += scaledWidth;
				break;
			}
		}
	}
}

void Text::doAlign(const std::string& str)
{
	if (spriteData.texture == NULL)
		return;

	UINT w, h;
	switch (align){
	case textNS::CENTER:
		getWidthHeight(str, w, h);
		spriteData.x -= w / 2;
		break;
	case textNS::RIGHT:
		getWidthHeight(str, w, h);
		spriteData.x -= w;
		break;
	case textNS::CENTER_MIDDLE:
		getWidthHeight(str, w, h);
		spriteData.x -= w / 2;
		spriteData.y -= h / 2;
		break;
	case textNS::CENTER_BOTTOM:
		getWidthHeight(str, w, h);
		spriteData.x -= w / 2;
		spriteData.y -= h;
		break;
	case textNS::LEFT_BOTTOM:
		getWidthHeight(str, w, h);
		spriteData.y -= h;
		break;
	case textNS::RIGHT_BOTTOM:
		getWidthHeight(str, w, h);
		spriteData.x -= w;
		spriteData.y -= h;
		break;
	}

}

void Text::getWidthHeight(const std::string& str, UINT& w, UINT& h)
{
	if (spriteData.texture == NULL)
		return;

	UCHAR ch = 0, chN = 0;
	width = textNS::FONT_WIDTH;
	int scaledWidth = static_cast<int>(width*spriteData.scale);
	int strW = 0;
	h = 0;
	int stringWidth = 0;

	for (UINT i = 0; i < str.length(); i++)
	{
		ch = str.at(i);

		// 표시 가능한 문자라면.
		if (ch>textNS::MIN_CHAR && ch <= textNS::MAX_CHAR)
		{
			chN = ch - textNS::MIN_CHAR;	// min_char 인덱스를 0으로 만든다.
			if (proportional)
			{
				spriteData.rect.left = fontData[chN / textNS::COLUMNS][chN % textNS::COLUMNS].left;
				// DirectX 스프라이트 폭에 대해 +1을 한다.
				spriteData.rect.right = fontData[chN / textNS::COLUMNS][chN % textNS::COLUMNS].right + 1;
				scaledWidth = static_cast<int>(width*spriteData.scale);
			}
			// 고정된 피치.
			else
			{
				width = textNS::FONT_WIDTH;
				spriteData.rect.left = chN % textNS::COLUMNS + textNS::GRID_WIDTH + 1;
				spriteData.rect.right = spriteData.rect.left + textNS::FONT_WIDTH;
			}
			stringWidth += scaledWidth;
		}
		// 표시할 수 없는 문자.
		else
		{
			switch (ch)
			{
			case ' ':
				if (proportional)
				{
					width = (textNS::FONT_WIDTH) / 2;
					scaledWidth = static_cast<int>(width*spriteData.scale);
				}
				stringWidth += scaledWidth;
				break;
			case '\n':
				if (strW == 0)
					strW = stringWidth;
				stringWidth = 0;
				h += static_cast<int>(height*spriteData.scale);
				break;
			case '\r':
				if (strW == 0)
					strW = stringWidth;
				stringWidth = 0;
				break;
			case '\t':
			{
				width = textNS::FONT_WIDTH;
				scaledWidth = static_cast<int>(width*spriteData.scale);
				int tabX = static_cast<int>(spriteData.x) / (scaledWidth*tabSize);
				tabX = (tabX + 1)*scaledWidth*tabSize;
				int tabW = tabX - static_cast<int>(spriteData.x);
				while (tabW > 0)
				{
					if (tabW >= scaledWidth)
						stringWidth += scaledWidth;
					else
					{
						width = tabW;
						stringWidth += tabW;
					}
					tabW -= scaledWidth;
				}
			}
			break;
			case '\b':
				stringWidth -= scaledWidth;
				if (stringWidth < 0)
					stringWidth = 0;
				break;
			case 0x01:
				stringWidth += scaledWidth;
				break;
			}
		}
	}
	if (strW == 0)
		strW = stringWidth;
	w = strW;
	return;
}

void Text::drawChar(UCHAR ch)
{
	// 스프라이트 데이터를 복사한다.
	SpriteData sd2 = spriteData;
	if (backColor != TRANSCOLOR)
	{
		spriteData.rect.top = (textNS::SOLID - textNS::MIN_CHAR) / textNS::COLUMNS*textNS::GRID_HEIGHT + 1;
		spriteData.rect.bottom = spriteData.rect.top + textNS::GRID_HEIGHT - 2;
		spriteData.rect.left = (textNS::SOLID - textNS::MIN_CHAR) % textNS::COLUMNS*textNS::GRID_WIDTH + 1;
		spriteData.rect.right = spriteData.rect.left + width;
		draw(backColor);
		spriteData.rect = sd2.rect;
	}
	if (underline)
	{
		spriteData.rect.top = (textNS::UNDERLINE - textNS::MIN_CHAR) / textNS::COLUMNS*textNS::GRID_HEIGHT + 1;
		spriteData.rect.bottom = spriteData.rect.top + textNS::LEFT - 2;
		spriteData.rect.left = (textNS::UNDERLINE - textNS::MIN_CHAR) % textNS::COLUMNS*textNS::GRID_WIDTH + 1;
		spriteData.rect.right = spriteData.rect.left + width;
		draw(color);
		spriteData.rect = sd2.rect;
	}
	// 표시 가능한 문자라면 문자를 표시한다.
	if (ch>textNS::MIN_CHAR&&ch<=textNS::MAX_CHAR)
	{
		draw(spriteData, color);
		if (bold)
		{
			spriteData.x += textNS::BOLD_SIZE*spriteData.scale;
			draw(spriteData, color);
			spriteData.x = sd2.x;
		}
	}
}

void Text::onLostDevice()
{
	try {
		if (!initialized)
			return;
		fontTexture.onLostDevice();
	}
	catch (...){}
}

void Text::onResetDevice()
{
	try {
		if (!initialized)
			return;
		fontTexture.onResetDevice();
	}
	catch (...){}
}