#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	mEntity = new MapEntity();
}

ObjectManager::~ObjectManager() {
	delete mEntity;
}

void ObjectManager::Initialize(stage global) {

	mEntity->Initialize(global);

}

void ObjectManager::Process() {

}

void ObjectManager::Render() {

	mEntity->Render();

}
