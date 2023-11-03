#pragma once

// �O���錾
class Stage;

namespace {
	struct Block {
		int x_;
		int z_;
		Block(int x, int z) {
			x_ = x;
			z_ = z;
		}
	};
}

class CommandBase {
protected:
	Block selectBlock_;	//�I�����ꂽ�u���b�N
	int brushSize_;		//�u���V�̑傫��
public:
	CommandBase(int x, int z, int size);
	~CommandBase();

	virtual void UndoCommand(Stage* p) = 0;	//Undo
	virtual void RedoCommand(Stage* p) = 0;	//Redo
};