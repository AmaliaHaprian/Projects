#pragma once
#include <string>
#include <Repository.h>

using namespace std;
class Action
{
public:
	Action();
	virtual ~Action() {};
	virtual void undo() = 0;
	virtual void redo() = 0;
};

class AddAction :public Action {
private:
	Repository& repo;
	Dog addedDog;
public:
	AddAction(Repository& repo, Dog d);
	~AddAction();
	void undo() override;
	void redo() override;
};

class RemoveAction :public Action {
private:
	Repository& repo;
	Dog removedDog;
public:
	RemoveAction(Repository& repo, Dog d);
	~RemoveAction();
	void undo() override;
	void redo() override;
};

class UpdateAction :public Action {
private:
	Repository& repo;
	Dog oldDog;
	Dog newDog;
public:
	UpdateAction(Repository& repo, Dog oldDog, Dog newDog);
	~UpdateAction();
	void undo() override;
	void redo() override;
};