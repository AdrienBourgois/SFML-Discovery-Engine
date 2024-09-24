#pragma once
#include <SFML/System/Clock.hpp>
#include "Module.h"

/**
 * \class TimeModule
 * \brief A module for handling time-related functionality.
 * 
 * This class provides methods to track the time elapsed since the beginning
 * of the application and the time between frames (delta time).
 */
class TimeModule final : public Module
{
public:
	/**
	 * \brief Default constructor.
	 */
	TimeModule() = default;

	/**
	 * \brief Default destructor.
	 */
	~TimeModule() = default;

	/**
	 * \brief Called when the module is initialized.
	 */
	void Awake() override;

	/**
	 * \brief Called once per frame to update the module.
	 */
	void Update() override;

	/**
	 * \brief Gets the time elapsed between the current and the previous frame.
	 * \return The delta time in seconds.
	 */
	float GetDeltaTime() const;

	/**
	 * \brief Gets the time elapsed since the beginning of the application.
	 * \return The time since the beginning in seconds.
	 */
	float GetTimeSinceBeginning() const;

	/**
	 * \brief Gets the clock used to measure delta time.
	 * \return The delta time clock.
	 */
	sf::Clock GetDeltaClock() const;

	/**
	 * \brief Gets the clock used to measure the time since the beginning.
	 * \return The clock since the beginning.
	 */
	sf::Clock GetClockSinceBeginning() const;

private:
	/// Clock to measure delta time.
	sf::Clock deltaClock;

	/// Clock to measure time since the beginning.
	sf::Clock clock;

	/// Time elapsed between the current and the previous frame.
	float deltaTime = 0.0f;
};
