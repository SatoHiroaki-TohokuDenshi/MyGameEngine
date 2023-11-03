#include "CommandManager.h"
#include "CommandBase.h"

CommandManager::CommandManager() {
}

CommandManager::~CommandManager() {
}

void CommandManager::RecordCommand(CommandBase* command) {
	// Undo���Ă���Ȃ�
	if (!commandListRedo_.empty()) {
		commandListRedo_.clear();
	}

	commandListUndo_.push_back(command);
}

void CommandManager::ClearCommand() {
	commandListUndo_.clear();
	commandListRedo_.clear();
}

void CommandManager::Undo(Stage* p) {
	// Undo���X�g���󂶂�Ȃ��Ȃ�
	if (!commandListUndo_.empty()) {
		commandListUndo_.back()->UndoCommand(p);
		// Redo�ɃR�s�[
		commandListRedo_.push_back(commandListUndo_.back());
		commandListUndo_.pop_back();
	}
}

void CommandManager::Redo(Stage* p) {
	// Redo���X�g���󂶂�Ȃ��Ȃ�
	if (!commandListRedo_.empty()) {
		commandListRedo_.back()->RedoCommand(p);
		// Undo�ɃR�s�[
		commandListUndo_.push_back(commandListRedo_.back());
		commandListRedo_.pop_back();
	}
}