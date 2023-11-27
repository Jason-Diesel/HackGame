#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::init()
{
}

SceneUpdate Scene::Update(float dt)
{
	return SceneUpdate::Continue;
}

void Scene::Render()
{
}

void Scene::setResourceManager(ResourceManager* rm)
{
	this->rm = rm;
}

