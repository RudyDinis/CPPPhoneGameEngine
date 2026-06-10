/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:07:12 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/10 17:40:19 by rdinis           ###   ########.fr       */
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

int clicked = 0;
Scene *selected_scene = nullptr;
HomeScene *homeScene = nullptr;
HomeScene *test = nullptr;

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

static int32_t handle_input(struct android_app *app, AInputEvent *event)
{
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{

		static float last_x = 0.0f;
		static float last_y = 0.0f;
		static float dist_min = 10.0f;
		static bool hasMoved = false;
		int32_t action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;

		if (action == AMOTION_EVENT_ACTION_DOWN)
		{
			float x = AMotionEvent_getX(event, 0);
			float y = AMotionEvent_getY(event, 0);
			last_x = x;
			last_y = y;
			hasMoved = false;
		}

		if (action == AMOTION_EVENT_ACTION_MOVE)
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
				__android_log_print(ANDROID_LOG_INFO, "DEBUG", "SLIDEEEEEEEEEEEEEEEEEEEE");
			}
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
						selected_scene = test;
					}
				}
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

				homeScene = new HomeScene("HomeScene", mgr, &screen);
				test = new HomeScene("testScene", mgr, &screen);

				selected_scene = homeScene;

				surfaceReady = true;
			}
			if (app->destroyRequested)
				running = false;
		}

		if (surfaceReady)
		{
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			selected_scene->render();

			eglSwapBuffers(screen.getDisplay(), surface);
		}
	}
}