/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:07:12 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/17 18:21:57 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <android/log.h>
#include <vector>

#include "EBOClass/EBOClass.hpp"
#include "Shader/ShaderClass.hpp"
#include "VAOClass/VAOClass.hpp"
#include "VBOClass/VBOClass.hpp"
#include "ScreenClass/ScreenClass.hpp"
#include "ObjectClass/ObjectClass.hpp"
#include "HomeSceneClass/HomeSceneClass.hpp"
#include "GameSceneClass/GameSceneClass.hpp"
#include "ResourceManagerClass/ResourceManager.hpp"

int clicked = 0;
Scene *selected_scene = nullptr;
HomeScene *homeScene = nullptr;
GameScene *gameScene = nullptr;
ResourceManager *resourceManager = new ResourceManager();

static void handle_app_cmd(struct android_app *app, int32_t cmd)
{
	switch (cmd)
	{
	case APP_CMD_INIT_WINDOW:
		// surface init ici, pas dans le poll
		break;
	case APP_CMD_GAINED_FOCUS:
		__android_log_print(ANDROID_LOG_INFO, "DEBUG", "Focus gained");
		break;
	}
}

float getPinchDistance(AInputEvent *event)
{
	float x0 = AMotionEvent_getX(event, 0);
	float y0 = AMotionEvent_getY(event, 0);
	float x1 = AMotionEvent_getX(event, 1);
	float y1 = AMotionEvent_getY(event, 1);
	float dx = x1 - x0;
	float dy = y1 - y0;
	return sqrt(dx * dx + dy * dy);
}

static int32_t handle_input(struct android_app *app, AInputEvent *event)
{
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{

		static float last_x = 0.0f;
		static float last_y = 0.0f;
		static float dist_min = 10.0f;
		static bool hasMoved = false;
		static float lastPinchDist = 0.0f;
		static bool isPinching = false;

		int32_t action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
		int32_t pointerCount = AMotionEvent_getPointerCount(event);

		if (action == AMOTION_EVENT_ACTION_DOWN)
		{
			float x = AMotionEvent_getX(event, 0);
			float y = AMotionEvent_getY(event, 0);
			last_x = x;
			last_y = y;
			hasMoved = false;
		}

		if (action == AMOTION_EVENT_ACTION_POINTER_DOWN && pointerCount == 2)
		{
			lastPinchDist = getPinchDistance(event);
			isPinching = true;
		}

		if (action == AMOTION_EVENT_ACTION_POINTER_UP)
		{
			lastPinchDist = 0.0f;
			hasMoved = true;
			last_x = AMotionEvent_getX(event, 0);
			last_y = AMotionEvent_getY(event, 0);
		}

		if (action == AMOTION_EVENT_ACTION_UP)
		{
			if (!hasMoved)
			{
				float x = AMotionEvent_getX(event, 0);
				float y = AMotionEvent_getY(event, 0);

				for (auto &object : selected_scene->getObject())
				{
					if (object->isTouched(x, y))
					{
						if (object->getName() == "idk")
						{
							selected_scene = gameScene;
							gameScene->load();
						}
						else
							selected_scene = homeScene;
					}
				}
			}

			hasMoved = false;
			isPinching = false;
		}

		if (action == AMOTION_EVENT_ACTION_MOVE)
		{
			if (pointerCount == 1 && !isPinching)
			{
				float x = AMotionEvent_getX(event, 0);
				float y = AMotionEvent_getY(event, 0);

				float dx = x - last_x;
				float dy = y - last_y;

				if (!hasMoved && (dx * dx + dy * dy) > dist_min * dist_min)
				{
					hasMoved = true;
				}

				if (hasMoved)
				{
					*selected_scene->getCamera()->getOffset_x() += dx;
					*selected_scene->getCamera()->getOffset_y() -= dy;
					last_x = x;
					last_y = y;
				}
			}
			else if (pointerCount == 2)
			{
				float newDist = getPinchDistance(event);
				if (lastPinchDist > 0.0f)
				{
					float scale = newDist / lastPinchDist;
					if (*selected_scene->getCamera()->getZoom() * scale <= 0.5)
						*selected_scene->getCamera()->getZoom() = 0.5;
					else if (*selected_scene->getCamera()->getZoom() * scale >= 2.5)
						*selected_scene->getCamera()->getZoom() = 2.5;
					else
						*selected_scene->getCamera()->getZoom() *= scale;
				}
				lastPinchDist = newDist;
			}
		}
		return 1; // consommé
	}
	return 0;
}

void android_main(struct android_app *app)
{
	AAssetManager *mgr = app->activity->assetManager;
	Screen screen(app);

	float aspect = 0.0;

	bool running = true;
	bool surfaceReady = false;
	EGLSurface surface = EGL_NO_SURFACE;

	app->onAppCmd = handle_app_cmd;
	app->onInputEvent = handle_input;
	while (running)
	{
		int events;
		struct android_poll_source *source;

		while (ALooper_pollAll(0, nullptr, &events, (void **)&source) >= 0)
		{
			if (source)
				source->process(app, source);
			if (app->window && !surfaceReady)
			{
				surface = eglCreateWindowSurface(screen.getDisplay(), screen.getConfig(), app->window, nullptr);
				eglMakeCurrent(screen.getDisplay(), surface, surface, screen.getContext());

				glViewport(0, 0, screen.width(), screen.height());

				resourceManager->loadShader(mgr, "default", "shaders/default.vert", "shaders/default.frag");
				resourceManager->loadShader(mgr, "tileMap", "shaders/tileMap.vert", "shaders/tileMap.frag");

				resourceManager->loadTextures(mgr, "groundAtlas", "textures/ground/groundAtlas.png");

				
				homeScene = new HomeScene("HomeScene", mgr, &screen, resourceManager);
				gameScene = new GameScene("gameScene", mgr, &screen, resourceManager);

				selected_scene = homeScene;

				surfaceReady = true;
			}
			if (app->destroyRequested)
				running = false;
		}

		if (surfaceReady)
		{
			GLboolean blendEnabled;
			glGetBooleanv(GL_BLEND, &blendEnabled);
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			selected_scene->render();
			static int fps = 0;
			static auto last = std::chrono::steady_clock::now();

			fps++;

			auto now = std::chrono::steady_clock::now();

			if (std::chrono::duration_cast<std::chrono::seconds>(now - last).count() >= 1)
			{
				__android_log_print(ANDROID_LOG_INFO, "DEBUG FPS", "%d", fps);
				fps = 0;
				last = now;
			}

			eglSwapBuffers(screen.getDisplay(), surface);
		}
	}
}