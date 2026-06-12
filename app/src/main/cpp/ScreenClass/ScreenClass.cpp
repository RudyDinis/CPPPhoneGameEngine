/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScreenClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:47:38 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/12 12:10:19 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScreenClass.hpp"

Screen::Screen(android_app *App)
{
	
	this->_app = App;
	
	ANativeActivity_setWindowFlags(
    	this->_app->activity,
    	0x00000400,
    	0
	);
	this->_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(this->_display, nullptr, nullptr);

	EGLint attribs[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_NONE};

	eglChooseConfig(this->_display, attribs, &this->_config, 1, &this->_numConfigs);

	EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
	this->_context = eglCreateContext(this->_display, this->_config, nullptr, contextAttribs);
}

EGLDisplay Screen::getDisplay()
{
	return (this->_display);
}

EGLConfig Screen::getConfig()
{
	return (this->_config);
}

EGLContext Screen::getContext()
{
	return (this->_context);
}

int Screen::width()
{
	return (ANativeWindow_getWidth(_app->window));
}

int Screen::height()
{
	return (ANativeWindow_getHeight(_app->window));
}

Screen::~Screen()
{
}