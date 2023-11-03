#pragma once
#include <vector>

// �O���錾
class CommandBase;
class Stage;

class CommandManager {
private:
	std::vector<CommandBase*> commandListUndo_;	// Undo�p���X�g
	std::vector<CommandBase*> commandListRedo_;	// Redo�p���X�g
public:
	CommandManager();
	~CommandManager();

	// �R�}���h���L�^
	void RecordCommand(CommandBase* command);
	void ClearCommand();
	void Undo(Stage* p);
	void Redo(Stage* p);
};