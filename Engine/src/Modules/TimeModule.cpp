#include "Modules/TimeModule.h"

#include <SFML/System/Time.hpp>

void TimeModule::Awake()
{
	Module::Awake();

	deltaClock.restart();
	clock.restart();
}

void TimeModule::Update()
{
	Module::Update();

	const sf::Time delta = deltaClock.restart();
	deltaTime = delta.asSeconds();
}

float TimeModule::GetDeltaTime() const
{
	return deltaTime;
}

float TimeModule::GetTimeSinceBeginning() const
{
	return clock.getElapsedTime().asSeconds();
}

sf::Clock TimeModule::GetDeltaClock() const
{
	return deltaClock;
}

sf::Clock TimeModule::GetClockSinceBeginning() const
{
	return clock;
}
