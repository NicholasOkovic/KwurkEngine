#pragma once

#include <KwurkEngine/Inc/KwurkEngine.h>



class GameState : public KwurkEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	std::filesystem::path mLevelFile;	
	KwurkEngine::GameWorld mGameWorld;
};






