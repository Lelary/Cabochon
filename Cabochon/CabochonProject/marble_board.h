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
	enum class BoardState{Build, Ready, Play, GameOver, GameClear};

	class MarbleBoard
		: public Control
	{
	private:
		/*
		// 2016. 2. 17.
		// TODO.-------------------------------------------------------------
		// level �� Positive �� ��� load �� ��,
		// Zero �ϰ�� ���� ���� ���� ��
		// Negative �� ��� �������� ����. (level ���� abs()�� ���� ����)
		//-------------------------------------------------------------------
		*/
		//const char* levelFile = "data\\level_data.txt";
		//const int maxLevel = 3;

		//int _level;
		BoardState _boardState;
		MarbleRows _marbles;
		Image _ceiling;
		std::array<int, (int)MarbleColor::Num> _colorCount;

		//-------------------------------------
		// 2016. 2. 29.
		// Animation ȿ��. ����� ����.
		// if var==0 return; if var<CONST playAnim()
		const scalar MARBLE_DISAPPEAR_FRAME = 1.0f; // sec
		const scalar LINE_DRAG_FRAME = 0.5f;		// sec

		scalar _marbleDisappearFrame;	// sec
		scalar _lineDragFrame;			//sec

		// ���� ���� marble ���.
		std::vector<IntPosition> _toRemove;
		// ���� ���� �� (�ִϸ��̼��� �ǹ�)
		int _lineToDrag;

		void beginMarbleDisappear(){ _marbleDisappearFrame = MARBLE_DISAPPEAR_FRAME*0.001f; }
		void beginLineDrag(){ _lineDragFrame = LINE_DRAG_FRAME*0.001f; }
		void finishMarbleDisappear(){ _marbleDisappearFrame = 0.0f; }
		void finishLineDrag(){ _lineDragFrame = 0.0f; }
		void progressMarbleDisappear(float elapsedTime){ _marbleDisappearFrame += elapsedTime; }
		void progressLineDrag(float elapsedTime){ _lineDragFrame += elapsedTime; }

	public:
		MarbleBoard();
		MarbleBoard(const MarbleBoard& rhs) = delete;
		~MarbleBoard();
		MarbleBoard& operator=(const MarbleBoard& rhs) = delete;
		// marbleBoard�� �ؽ�ó�� �ϰ������� �ε��Ѵ�.
		void loadTextures(TextureList& textureList);


		// marble_ptr ���� ��ȯ.
		const marble_ptr& getMarble(IntPosition index) const;

		// Marble �� ���� ��� MarbleColor ��ȯ, ���� ��쿣 MarbleColor::None ��ȯ (��ü�� Color�� None���� ǥ���Ͽ� ����ô)
		MarbleColor existMarble(IntPosition index) const;

		// �ش� ������ Marble �߰� (�����δ� ���� �ٲٰ� ī��Ʈ�� �ø�)
		bool addMarble(IntPosition index, MarbleColor color);

		// �ش� ��ġ�� Marble ���� (�����δ� ���� None����, ī��Ʈ�� ����)
		// immediatly�� ��� �������� ���� �⺻���� false, �ִϸ��̼� ����.
		bool removeMarble(IntPosition index, bool immediatly=false);

		// �ش� Color�� ���� Marble Instance ����.
		marble_ptr makeMarble(MarbleColor color);
		marble_ptr makeRandomMarble();
		marble_ptr makeRandomMarble(MarbleColorOn colorRange);

		// �����ִ� marble�� ���� ���ο� ������� 0�� ���� �����Ѵ�.
		// RowZero�� Line �Ʒ��� �ִ� Row. 
		void removeRowZero();

		// �ش� ������ Marble ������ ��ȯ�Ѵ�.
		int getMarbleCount(MarbleColor c) const;

		// �����ִ� Marble ������ ��ȯ�Ѵ�.
		int getMarbleCount() const;

		// ���� ����(Row ��) ��ȯ. (Ceiling ���� ������ Row�� ��ȣ+1.)
		int getHeight() const;

		// ���� Board�� ���� ���� (���� ������ �����̱⵵ �ϴ�.)
		void setBoardState(BoardState state);

		// ���� Board�� ���� ��ȯ (���� ������ �����̱⵵ �ϴ�.)
		BoardState getBoardState() const;

		bool animationFinished();
		/*
		// �� �Լ��� �� �� �ִ� ��.
		// ��ȯ�� :  ���� ���� Marble �� �����ϴ� ù�� ° ��.
		// 0��ȯ : ���� ����.										// gameOver() �� ȿ���� ����.
		// getHeight() ��ȯ :������ Ŭ���� �� ����.					// gameClear() �� ȿ���� ����.
		// 10�ʰ��� ��� ȭ�鿡 ���̴� ���� �����Ƿ� ���������.	// �ٸ� �Լ�����.
		// Ž���� �ʿ䰡 ���� �ϴ� ���� ����.
		*/
		int getFloor() const;

		scalar getCeilingPosition() const;

		// ������ �ٿ� Marble�� �ϳ��� ������ true.
		bool gameOver();

		// Marble�� Board�� ���� ���� ������ true.
		bool gameClear();

		// ( Ÿ�̸Ӱ� ���� ��� ���� �� �� ���� )
		// �� �� ������ ó���� �ϸ� ���ݵǴ� �ۿ���� �Բ� ó���Ѵ�.
		// �� �۾����� ���� ���ŵ� ���� ���� BoardState�� ��ȯ�Ѵ�.
		bool dragDownOneLine();

		// Marble���� �ı��Ǿ� ȭ��� ���̴� Marble�� ���̻� ���� ��� ����ĭ�� ������.
		// return ���� �� �Լ��� drag�� �����״����� ��ȯ�Ѵ�.
		// ( ������ ó������ ���� drag �� ���� ���, _dragged�� ���ϰ��� �������� ���� �� �ִ�.)
		bool dragDownHiddenLines();

		// ���ǿ� ���� dragDownOneLine()�� dragDownHiddenLines�� ��� �����Ѵ�.
		//BoardState dragDown();

		//void loadBoard(File* file);
		//void buildBoard();

		// ������ Board Map�� �����Ѵ�. 
		// (Level ��� �߰� �Ŀ� �� Level�� ġ��, negative ������ ����.)
		void makeRandomBoard();

		//makeRandomBoard()���ο��� �������� ���� marble�߿� link���� ���� marble�� �����Ѵ�.
		void arrangeNotLinkedMarbles(bool immediatly=false);

		// ��� Marble���� �ڽ��� ������ �ִ� Dequeue ������ ��ȣ�� ��������,
		// GridPosition �� Position�� �����Ѵ�. (Marble���� ���ĵ�)
		void updateMarblePositions();

		// �ڽ��� �߽����� x��ǥ�� �Ķ���ͷ� �ְ� Column ��ȣ�� ��´�.
		// rowType�� argument�� �ʿ��ϴ�. getRowType(y)�� �� �� �ִ�.
		// example : 0 <= x < 50 -> 10
		int positionToColumnIndex(scalar x, RowType rowType) const;
		// �ڽ��� �߽����� y ��ǥ�� �Ķ���ͷ� �ְ� Row ��ȣ�� ��´�.
		int positionToRowIndex(scalar y) const;
		// �ڽ��� �߽����� ��ǥ�� �Ķ���ͷ� MarbleBoard������ Index ��ȣ�� ��´�.
		IntPosition positionToIndex(scalar x, scalar y) const;
		// �ڽ��� �߽����� ��ǥ�� �Ķ���ͷ� MarbleBoard������ Index ��ȣ�� ��´�.
		IntPosition positionToIndex(Position position) const;
		
		Position indexToPosition(IntPosition index) const;

		// �ڽ��� �߽����� y ��ǥ�� ���� Even Row ���� Odd Row���� �� �� �ִ�.
		RowType getRowType(scalar y) const;
		// �ڽ��� Row ��ȣ�� ����, RowType�� Even���� Odd���� �� �� �ִ�. 
		RowType getRowType(int row) const;

		// ������ ����ų index ������ �˻��Ѵ�.
		bool isInvalidIndex(IntPosition index) const;

		//2016. 3. 2 �߰�.
		scalar getMarbleDisappearFrame() const;
		scalar getLineDragFrame() const;
		int getNumRemoving() const;
		void marbleDisappearAnimation(scalar elapsedFrame);
		void lineDragAnimation(scalar elapsedFrame);
		void handleAnimation(float frameTime);
		const std::vector<IntPosition>& getToRemove() const{ return _toRemove;}

		//pure virtual functions
		virtual void render();
		virtual void update(float frameTime);

	};

}

#endif