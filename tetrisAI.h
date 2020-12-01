#ifndef TETRIS_AI_H
#define TETRIS_AI_H

#include<vector>

namespace TetrisAI {
	class AI {
	public:
		void inputData(int d1, int d2);
		std::vector<std::vector<int>> getData();
	private:
		std::vector<int> data;
		std::vector<std::vector<int>> dataCollection;
	};
	void AI::inputData(int d1, int d2) {
		data.push_back(d1);
		data.push_back(d2);
		dataCollection.push_back(data);
	}
	std::vector<std::vector<int>> AI::getData() {
		return this->dataCollection;
	}
}








#endif// TETRIS_AI_H