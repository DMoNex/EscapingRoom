#include "pch.h"
#include "Entity.h"

#include "EscapingRoomView.h"
Entity::Entity(EntityId id) {
	this->id = id;
	init();
}

EntityId Entity::getEntityType() {
	return id;
}

void Entity::init() {

}