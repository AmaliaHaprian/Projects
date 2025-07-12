#include "Action.h"

Action::Action()
{
}

AddAction::AddAction(Repository& repo, Dog d) : repo(repo), addedDog(d)
{
}

AddAction::~AddAction()
{
}

void AddAction::undo()
{
	this->repo.removeRepo(this->addedDog.getName());
}

void AddAction::redo()
{
	this->repo.addRepo(this->addedDog);
}

RemoveAction::RemoveAction(Repository& repo, Dog d) : repo(repo), removedDog(d)
{
}

RemoveAction::~RemoveAction()
{
}

void RemoveAction::undo()
{
	this->repo.addRepo(this->removedDog);
}

void RemoveAction::redo()
{
	this->repo.removeRepo(this->removedDog.getName());
}

UpdateAction::UpdateAction(Repository& repo, Dog oldDog, Dog newDog) : repo(repo), oldDog(oldDog), newDog(newDog)
{
}

UpdateAction::~UpdateAction()
{
}

void UpdateAction::undo()
{
	this->repo.updateRepo(this->newDog, this->oldDog);
}

void UpdateAction::redo()
{
	this->repo.updateRepo(this->oldDog, this->newDog);
}
