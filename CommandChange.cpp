#include "CommandChange.h"

CommandChange::CommandChange(Stage* p, int x, int z, int size)
	:CommandBase(p, x, z, size)
{
	// �u���b�N���擾
	blockType_.resize(brushSize_ * brushSize_);

	//p->GetBlockType(selectBlock_.x_, selectBlock_.z_);
}

CommandChange::~CommandChange() {
}

void CommandChange::UndoCommand() {
	// �I�񂾃u���b�N��߂�
}

void CommandChange::RedoCommand() {
	// �I�񂾃u���b�N��ς���
}
