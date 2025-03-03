#pragma once

#include "Particle.h"

namespace KwurkEngine::Physics
{
	struct ParticleSystemInfo
	{
		Graphics::TextureId textrueId = 0;
		int maxParticles = 100;
		Math::RangeInt particlesPerEmit = { 0,0 };
		float delay;
		float lifeTime = 0.0f;
		Math::Range<float> timeBetweenEmit = { 0.0f, 0.0f };
		Math::Range<float> spawnAngle = { 0.0f, 0.0f };
		Math::Range<float> spawnSpeed = { 0.0f, 0.0f };
		Math::Range<float> spawnLifeTime = { 0.0f, 0.0f };
		Math::Vector3 spawnDirection = Math::Vector3::YAxis;
		Math::Vector3 spawnPosition = Math::Vector3::Zero;
		Math::Range<Math::Vector3> startScale = { Math::Vector3::One, Math::Vector3::One };
		Math::Range<Math::Vector3> endScale = { Math::Vector3::One, Math::Vector3::One };
		Math::Range<Color> startColor = { Colors::White, Colors::White };
		Math::Range<Color> endColor = { Colors::White, Colors::White };
	};

	class ParticleSystem
	{
	public:
		void Initialize(const ParticleSystemInfo& info);
		void Terminate();
		void Update(float deltaTime);

		bool IsActive();
		void DebugUI();

		void SetPosition(const Math::Vector3& position);

		void SpawnParticles();
		void Render(Graphics::ParticleSystemEffect& effect);

	private:
		void InitializeParticles(uint32_t count);
		void SpawnSingleParticle();

		using Particles = std::vector<std::unique_ptr<Particle>>;
		Particles mParticles;

		Graphics::ParticleSystemEffect mParticleEffect;
		ParticleSystemInfo mInfo;
		int mNextAvailableParticleIndex;
		float mNextSpawnTime = 0.0f;
		float mLifeTime = 0.0f;
	};

}