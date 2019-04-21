#include <iostream>
#include <Core/Core.h>

int main(int argc, char* argv[])
{
	int s = CECore::InitEngineCore();
	if (s != 0) return s;


	return 0;
}