#define __COMPILING_NS_TASK_CPP__
#include "Task.h"
#undef __COMPILING_NS_TASK_CPP__
 
#include "../Assert/Assert.h"

using namespace Ns;


Task::Task()
{
}

Task::~Task()
{
}

void Task::destroy()
{
	this->onDestroy();
}

bool Task::execute()
{
	return this->onExecute();
}

Ns::IString Task::toString() const
{
	return this->onToString();
}

void Task::onDestroy()
{
	delete this;
}

Ns::IString Task::onToString() const
{
	return Ns::IString();
}
