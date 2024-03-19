#include "helper/scene.h"
#include "helper/scenerunner.h"

#include "IslandScene.h"
//#include "scenebasic_uniform.h"


int main(int argc, char* argv[])
{
	SceneRunner runner("Island");

	std::unique_ptr<Scene> scene;

	scene = std::unique_ptr<Scene>(new IslandScene());


	return runner.run(*scene);
}