#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>

class Component;

class GameObject {
private:
	std::list<Component *> _components;
public:

};

#endif // !GAMEOBJECT_H
