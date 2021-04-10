#include "DEBUG.h"
#include <iostream>

#include "HasMoved.h"

HasMoved::HasMoved()
	: m_HasMoved(false)
{
	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

void HasMoved::CheckFirstMove()
{
	if (!GetHasMoved())
	{
		SetHasMoved(true);
	}
}