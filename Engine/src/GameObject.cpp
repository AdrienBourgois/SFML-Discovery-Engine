#include "GameObject.h"

GameObject::~GameObject()
{
	for (Component*& component : components)
		delete component;

	components.clear();
}

std::vector<Component*>& GameObject::GetComponents()
{
	return components;
}

void GameObject::AddComponent(Component* _component)
{
	_component->SetOwner(this);
	components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{
	std::erase(components, _component);
}

#pragma region Events

void GameObject::Awake() const
{
	for (Component* const& component : components)
	{
		component->Awake();
	}
}

void GameObject::Start() const
{
	for (Component* const& component : components)
	{
		component->Start();
	}
}

void GameObject::PreRender() const
{
	for (Component* const& component : components)
	{
		component->PreRender();
	}
}

void GameObject::OnGUI() const
{
	for (Component* const& component : components)
	{
		component->OnGUI();
	}
}

void GameObject::PostRender() const
{
	for (Component* const& component : components)
	{
		component->PostRender();
	}
}

void GameObject::OnDebug() const
{
	for (Component* const& component : components)
	{
		component->OnDebug();
	}
}

void GameObject::OnDebugSelected() const
{
	for (Component* const& component : components)
	{
		component->OnDebugSelected();
	}
}

void GameObject::Present() const
{
	for (Component* const& component : components)
	{
		component->Present();
	}
}

void GameObject::OnEnable() const
{
	for (Component* const& component : components)
	{
		component->OnEnable();
	}
}

void GameObject::OnDisable() const
{
	for (Component* const& component : components)
	{
		component->OnDisable();
	}
}

void GameObject::Destroy() const
{
	for (Component* const& component : components)
	{
		component->Destroy();
	}
}

void GameObject::Finalize() const
{
	for (Component* const& component : components)
	{
		component->Finalize();
	}
}

void GameObject::Update(const float _delta_time) const
{
	for (Component* const& component : components)
	{
		component->Update(_delta_time);
	}
}

void GameObject::Render(sf::RenderWindow* _window) const
{
	for (Component* const& component : components)
	{
		component->Render(_window);
	}
}

#pragma endregion
