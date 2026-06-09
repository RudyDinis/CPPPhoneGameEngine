/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScreenClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:38:10 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/09 15:00:55 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_CLASS_HPP
#define SCREEN_CLASS_HPP

#include <iostream>
#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

class Screen
{
private:
	EGLDisplay _display;
	android_app *_app;
	EGLConfig _config;
	EGLint _numConfigs;
	EGLContext _context;
public:
	Screen(android_app *app);
	int width();
	int height();
	EGLDisplay getDisplay();
	EGLConfig getConfig();
	EGLContext getContext();
	~Screen();
};

#endif