#include "Core.h"
#include <Display/GLWindow.h>
#include <Shape/Cube.h>
#include <Shader/Shader.h>
#include <stdarg.h>   
#include <stdlib.h>
#include <time.h>  

GLWindow CECore::_mainWindow = GLWindow();

static void DoVectorTest();

int CECore::InitEngineCore()
{
#ifdef ENABLE_DEBUG
	CEngineDebug::_DEBUG_LOG_LEVEL = 0;
#endif // DEBUG

	DEBUG_LOG("Initializing CubeEngine core...\n");

	// create main window
	DEBUG_LOG("Creating main window...\n");
	DEBUG_LOG_STEP_IN;
	int status = _mainWindow.Init(540, 540, "CubeEngineMainWindow");
	DEBUG_LOG_STEP_OUT;
	if (status != 0)
	{
		DEBUG_LOG("Failed to create main window\n");
		return status;
	}
	DEBUG_LOG("Successfully created main window\n");

	Shader basicShader("./src/Shader/basicShader");
	Shape * newShape = new Cube(Vector2(0, 0), Vector2(1, 1), 0);
	// start loop
	DEBUG_LOG("Starting engine loop...\n");
	while (!_mainWindow.isClosed())
	{
		_mainWindow.Clear(0.0f, 0.0f, 0.0f, 1.f);
		basicShader.Bind();
		newShape->DoTransform();
		newShape->Draw();

		_mainWindow.Update();
	}

	delete newShape;
	DEBUG_LOG("Engine loop exited");
	return 0;
}

float randFloat() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

void DoVectorTest() {
	srand(time(0));

	Vector3 vectors[10] = {
		Vector3(randFloat(), randFloat(), randFloat()),
		Vector3(randFloat(), randFloat(), randFloat()),
		Vector3(randFloat(), randFloat(), randFloat()),
		Vector3(randFloat(), randFloat(), randFloat()),
		Vector3(randFloat(), randFloat(), randFloat()),
		Vector3(randFloat(), randFloat(), randFloat()),
		Vector3(randFloat(), randFloat(), randFloat()),
		Vector3(randFloat(), randFloat(), randFloat()),
		Vector3(randFloat(), randFloat(), randFloat()),
		Vector3(randFloat(), randFloat(), randFloat())
	};

	Vector3 * result = new Vector3();

	DEBUG_LOG_STEP_IN;
	DEBUG_LOG("\nStarting vector test...\n");
	clock_t begin = clock();

	for (int x = 0; x < 100000; x++)
	{
		for (int i = 0; i < 10; i++)
		{
			*result += vectors[i];
			if (i < 9) *result *= vectors[i].dot(vectors[i + 1]);
		}
		*result /= 5;
	}
	for (int x = 0; x < 100000; x++)
	{
		for (int i = 0; i < 10; i++)
		{
			*result += vectors[i];
			if (i < 9) *result *= vectors[i].cross(vectors[i + 1]);
		}
		*result /= 5;
	}
	

	clock_t end = clock();
	DEBUG_LOG("\nFinished vector speed test... clocks elapsed :");
	DEBUG_LOG("%ld\n", end - begin);

	DEBUG_LOG_STEP_OUT;
}