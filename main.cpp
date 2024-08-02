#include "helper/scene.h"
#include "helper/scenerunner.h"

//#include "IslandScene.h"
#include "scenebasic_uniform.h"


int main(int argc, char* argv[])
{
	SceneRunner runner("Island");

	std::unique_ptr<SceneBasic_Uniform> scene;

	scene = std::unique_ptr<SceneBasic_Uniform>(new SceneBasic_Uniform());


	return runner.run(*scene);
}