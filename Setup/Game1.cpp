#include "Game1.h"

Game1::Game1() : GameInterface(), currentSceneNum(0), currentScene(nullptr) {

}

Game1::~Game1() {
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate() {
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	LogM::Info("WARNING", "Game1.cpp", __LINE__);
	return false;
}
void Game1::Update(const float deltaTime_) {
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render() {
	currentScene->Render();
}

void Game1::BuildScene() {
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene()) {
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		LogM::Info("ERROR", "Game1.cpp", __LINE__);
		CoreEngine::GetInstance()->Exit();
	}
}