#include "Precompiled.h"
#include "AudioSystem.h"

using namespace DirectX;
using namespace KwurkEngine;
using namespace KwurkEngine::Audio;

namespace
{
	std::unique_ptr<AudioSystem> sAudioSystem;
}

void AudioSystem::StaticInitialize()
{
	ASSERT(sAudioSystem == nullptr, "AudioSystme: Is already initialized");
	sAudioSystem = std::make_unique<AudioSystem>();
	sAudioSystem->Initialize();
}

void AudioSystem::StaticTerminate()
{
	if (sAudioSystem != nullptr)
	{
		sAudioSystem->Terminate();
		sAudioSystem.reset();
	}
}

AudioSystem* AudioSystem::Get()
{
	ASSERT(sAudioSystem != nullptr, "AudioSysytem: is not initialized");
	return sAudioSystem.get();
}

AudioSystem::AudioSystem()
{
}

AudioSystem::~AudioSystem()
{
	ASSERT(mAudioEngine == nullptr, "AudioSysytem: is not terminated");
}

void AudioSystem::Initialize()
{
	AUDIO_ENGINE_FLAGS flags = AudioEngine_Default;
#if defined(_DEBUG)
	flags |= AudioEngine_Debug;
#endif
	mAudioEngine = new AudioEngine(flags);
}

void AudioSystem::Terminate()
{
	if (mAudioEngine != nullptr)
	{
		Suspend();
		delete  mAudioEngine;
		mAudioEngine = nullptr;
	}
}

void AudioSystem::Update()
{
	if (mAudioEngine != nullptr && mAudioEngine->Update())
	{
		if (mAudioEngine->IsCriticalError())
		{
			LOG("AudioSystem: criticla erropr, shutting down");
			Terminate();
		}
	}
}

void AudioSystem::Suspend()
{
	ASSERT(mAudioEngine != nullptr, "AudioSystem: audio engine is not available");
	mAudioEngine->Suspend();
}
