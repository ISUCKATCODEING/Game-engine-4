#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() :window(nullptr), isRunning(false), fps(30), gameInterface(nullptr), currentSceneNum(0) {

}


CoreEngine::~CoreEngine() {

}

CoreEngine* CoreEngine::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_) {
	LogM::OnCreate();
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		LogM::Info("FATAL ERROR", "CoreEngine.cpp", __LINE__);
		OnDestroy();
		return isRunning = false;
	}

	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("simpleShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			LogM::Info("ERROR", "CoreEngine.cpp", __LINE__);
			return isRunning = false;
		}
	}
	
	LogM::Info("Everything worked", "CoreEngine.cpp", __LINE__);
	timer.Start();
	return isRunning = true;
}

void CoreEngine::Run() {
	while (isRunning) {
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
		OnDestroy();
	
}

void CoreEngine::Exit() {
	isRunning = false;
}

bool CoreEngine::GetIsRunning() const{
	return isRunning;
}

int CoreEngine::GetCurrentScene() const {
	return currentSceneNum;
}

float CoreEngine::GetScreenWidth() const {
	return static_cast<float>(window->GetWidth());
}

float CoreEngine::GetScreenHight() const {
	return static_cast<float>(window->GetHeight());
}

Camera* CoreEngine::GetCamera()const {
	return camera;
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}

void CoreEngine::SetCurrentScene(int sceneNum_) {
	currentSceneNum = sceneNum_;
}

void CoreEngine::SetCamera(Camera* camera_) {
	camera = camera_;
}

void CoreEngine::Update(const float deltaTime_) {
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
	
}

void CoreEngine::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gameInterface) {
		gameInterface->Render();
	}
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy() {
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	
	delete gameInterface;
	delete camera;
	gameInterface = nullptr;
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}

