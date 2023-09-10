#include "systems/audio/audioSystem.hpp"
#include "core/ecs/components.hpp"

namespace siofraEngine::systems
{
	AudioSystem::AudioSystem(IEventSystem* const eventSystem) :
		eventSystem{ eventSystem }
	{

	}

	void AudioSystem::update(core::Scene* scene)
	{
		auto const entities = scene->getEntities<core::AudioSource>();
		for (auto const& entity : entities)
		{
			auto const audioSourceComponent = scene->getComponent<core::AudioSource>(entity);

			if (!audioSourceComponent->play)
			{
				continue;
			}

			audioSourceComponent->play = false;
		}
	}
}