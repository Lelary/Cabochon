// 2016. 3. 10.

#ifndef _BOARD_LINK_CHEKCER_H
#define _BOARD_LINK_CHECKER_H

#include <vector>
#include <deque>
#include "vector2.h"
#include "marble_board.h"
namespace controls
{
	using mathematics::IntPosition;
	using controls::MarbleBoard;

	enum class LinkState{ NotChecked = -1, NotLinked = 0, Linked = 1 };
	class BoardLinkChecker
	{
	private:	
		static const int two = 2;
		const MarbleBoard& _board;
		std::deque<std::vector<bool>> _data;
		std::deque<std::vector<LinkState>> _result;

		void linkAll(IntPosition me);
		void linkUpper(IntPosition me);
		void linkSide(IntPosition me);
		void linkLower(IntPosition me);

		void check(std::array<IntPosition, two> testSet);

		void makeData();
		void makeLinkedResult();
	public:
		BoardLinkChecker(const MarbleBoard& marbleBoard);
		BoardLinkChecker(const BoardLinkChecker& rhs) = delete;
		~BoardLinkChecker();
		BoardLinkChecker& operator=(const BoardLinkChecker& rhs) = delete;
		
		const std::deque<std::vector<LinkState>>& getLinkedResult();
	};
}
#endif