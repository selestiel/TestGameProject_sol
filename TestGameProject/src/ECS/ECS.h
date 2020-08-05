#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <type_traits>

struct Component;
class Entity;
class Manager;


using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;

}
template <typename T> 
inline  ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID{ getNewComponentTypeID() };
	return typeID;
}
constexpr std::size_t maxComponents{ 32 };
constexpr std::size_t maxGroups{ 32 };

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

struct Component 
{
	Entity* entity;
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};
	virtual ~Component() {};

};
class Entity
{
private:

	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:
	Entity(Manager& mManager) : manager(mManager){}

	void update() 
	{
		for (auto& c : components)
		{
			c->update();
		}
	}
	void draw()
	{
		for (auto& c : components)
		{
			c->draw();
		}

	}
	bool isActive() const
	{ 
		return active;
	}
	void destroy()
	{
		active = false;
	}
	template <typename T> 
	bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}
	bool hasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}
	void addGroup(Group aGroup);
	void delGroup(Group dGroup)
	{
		groupBitSet[dGroup] = false;
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* create(new T(std::forward<TArgs>(mArgs)...));
		create->entity = this;

		std::unique_ptr<Component> uPtr{create};
		
		components.emplace_back(std::move(uPtr));
		
		componentArray[getComponentTypeID<T>()] = create;
		componentBitSet[getComponentTypeID<T>()] = true;

		create->init();

		return *create;
	}
	template <typename T> 
	T& getComponent() const 
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
	void update()
	{
		for (auto& ent : entities)
		{
			ent->update();
		}
	}
	void draw()
	{
		for (auto& ent : entities)
		{
			ent->draw();
		}
	}
	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
				{
					return !mEntity->isActive() || !mEntity->hasGroup(i);
				}
			),
				std::end(v));

		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}
	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}
	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		Entity* entity{ new Entity(*this) };
		std::unique_ptr<Entity> uPtr{ entity };
		entities.emplace_back(std::move(uPtr));
		return *entity;
	}

};