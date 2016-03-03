// 2016. 2. 17.
#ifndef _MARBLE_BOARD_H
#define _MARBLE_BOARD_H

#include "cabochon_constants.h"
#include "control.h"
#include "marble.h"
#include "object.h"
#include "marble_generator.h"
#include <deque>
#include <array>
namespace controls
{
	using mathematics::scalar;	
	using mathematics::Position;
	using mathematics::IntPosition;
	using components::MarbleColor;

	using MarbleRow = std::vector < components::marble_ptr> ;
	using MarbleRows = std::deque <MarbleRow> ;

	enum class RowType{ None = -1, Even, Odd };
	enum class BoardState{Build, Ready, Play, Animation, GameOver, GameClear};

	class MarbleBoard
		: public Control
	{
	private:
		/*
		// 2016. 2. 17.
		// TODO.-------------------------------------------------------------
		// level 은 Positive 일 경우 load 한 맵,
		// Zero 일경우 끝이 없는 무한 맵
		// Negative 일 경우 랜덤맵을 생성. (level 값은 abs()를 통해 얻음)
		//-------------------------------------------------------------------
		*/
		//const char* levelFile = "data\\level_data.txt";
		//const int maxLevel = 3;

		//int _level;
		BoardState _boardState;
		MarbleRows _marbles;
		bool _dragged;
		std::array<int, (int)MarbleColor::Num> _colorCount;

		//-------------------------------------
		// 2016. 2. 29.
		// Animation 효과. 상수와 변수.
		// if var==0 return; if var<CONST playAnim()
		// if boardState==Anim??
		const int MARBLE_DISAPPEAR_FRAME = 3000; // msec
		const int LINE_DRAG_FRAME = 3000;		// msec

		int _marbleDisappearFrame;	// msec
		int _lineDragFrame;			//msec

		// 삭제 예정 marble 등록.
		std::vector<marble_ptr&> _toRemove;
		bool animationFisinished();

	public:
		MarbleBoard();
		MarbleBoard(const MarbleBoard& rhs) = delete;
		~MarbleBoard();
		MarbleBoard& operator=(const MarbleBoard& rhs) = delete;
		// marbleBoard의 텍스처를 일괄적으로 로드한다.
		void loadTextures(TextureList& textureList);


		// marble_ptr 참조 반환.
		const marble_ptr& getMarble(IntPosition index) const;

		// Marble 이 있을 경우 MarbleColor 반환, 없을 경우엔 MarbleColor::None 반환 (개체에 Color만 None으로 표시하여 없는척)
		MarbleColor existMarble(IntPosition index) const;

		// 해당 색상의 Marble 추가 (실제로는 색깔만 바꾸고 카운트를 올림)
		bool addMarble(IntPosition index, MarbleColor color);

		// 해당 위치의 Marble 삭제 (실제로는 색깔만 None으로, 카운트를 내림)
		bool removeMarble(IntPosition index);

		// 해당 Color를 가진 Marble Instance 생성.
		marble_ptr makeMarble(MarbleColor color);
		marble_ptr makeRandomMarble();
		marble_ptr makeRandomMarble(MarbleColorOn colorRange);

		// 남아있는 marble의 존재 여부와 상관없이 0번 줄을 삭제한다.
		// RowZero는 Line 아래에 있는 Row. 
		void removeRowZero();

		// 해당 색상의 Marble 갯수를 반환한다.
		int getMarbleCount(MarbleColor c) const;

		// 남아있는 Marble 갯수를 반환한다.
		int getMarbleCount() const;

		// 현재 높이(Row 수) 반환. (Ceiling 직전 마지막 Row의 번호+1.)
		int getHeight() const;

		// 현재 Board의 상태 지정 (현재 게임의 상태이기도 하다.)
		void setBoardState(BoardState state);

		// 현재 Board의 상태 반환 (현재 게임의 상태이기도 하다.)
		BoardState getBoardState() const;

		/*
		// 이 함수로 알 수 있는 것.
		// 반환값 :  현재 남은 Marble 이 존재하는 첫번 째 줄.
		// 0반환 : 게임 오버.										// gameOver() 가 효율이 나음.
		// getHeight() 반환 :게임이 클리어 된 상태.					// gameClear() 가 효율이 나음.
		// 10초과일 경우 화면에 보이는 것이 없으므로 내려줘야함.	// 다른 함수에서.
		// 탐색할 필요가 없게 하는 것이 좋음.
		*/
		int getFloor() const;

		scalar getCeilingPosition() const;

		// 마지막 줄에 Marble이 하나라도 있으면 true.
		bool gameOver();

		// Marble이 Board에 남아 있지 않으면 true.
		bool gameClear();

		// ( 타이머가 있을 경우 일정 턴 수 마다 )
		// 한 줄 내리는 처리를 하며 동반되는 작용들을 함께 처리한다.
		// 이 작업으로 인해 갱신된 현재 상태 BoardState를 반환한다.
		bool dragDownOneLine();

		// Marble들이 파괴되어 화면상에 보이는 Marble이 더이상 없을 경우 일정칸을 내린다.
		// return 값은 이 함수가 drag를 일으켰는지를 반환한다.
		// ( 이전에 처리되지 않은 drag 가 있을 경우, _dragged와 리턴값이 동일하지 않을 수 있다.)
		bool dragDownHiddenLines();

		// 조건에 맞춰 dragDownOneLine()과 dragDownHiddenLines를 모두 실행한다.
		//BoardState dragDown();

		//void loadBoard(File* file);
		//void buildBoard();

		// 임의의 Board Map을 생성한다. 
		// (Level 기능 추가 후에 한 Level로 치며, negative 값으로 센다.)
		void makeRandomBoard();

		// 모든 Marble들이 자신이 가지고 있는 Dequeue 에서의 번호를 기준으로,
		// GridPosition 과 Position을 갱신한다. (Marble들이 정렬됨)
		void updateMarblePositions();

		// 자신의 중심점의 x좌표를 파라미터로 주고 Column 번호를 얻는다.
		// rowType이 argument로 필요하다. getRowType(y)로 알 수 있다.
		// example : 0 <= x < 50 -> 10
		int positionToColumnIndex(scalar x, RowType rowType) const;
		// 자신의 중심점의 y 좌표를 파라미터로 주고 Row 번호를 얻는다.
		int positionToRowIndex(scalar y) const;
		// 자신의 중심점의 좌표를 파라미터로 MarbleBoard에서의 Index 번호를 얻는다.
		IntPosition positionToIndex(scalar x, scalar y) const;
		// 자신의 중심점의 좌표를 파라미터로 MarbleBoard에서의 Index 번호를 얻는다.
		IntPosition positionToIndex(Position position) const;
		
		Position indexToPosition(IntPosition index) const;

		// 자신의 중심점의 y 좌표를 통해 Even Row 인지 Odd Row인지 알 수 있다.
		RowType getRowType(scalar y) const;
		// 자신의 Row 번호를 통해, RowType이 Even인지 Odd인지 알 수 있다. 
		RowType getRowType(int row) const;

		// 오류를 일으킬 index 값인지 검사한다.
		bool isInvalidIndex(IntPosition index) const;

		//2016. 3. 2 추가.
		int getMarbleDisappearFrame() const;
		int getLineDragFrame() const;
		void marbleDisappearAnimation(int elapsedFrame);
		void lineDragAnimation(int elapsedFrame);
		
		//pure virtual functions
		virtual void render();
		virtual void update(float frameTime);

	};

}

#endif