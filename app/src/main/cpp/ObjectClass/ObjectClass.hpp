/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:59:14 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/16 18:13:45 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTCLASS_HPP
#define OBJECTCLASS_HPP

#include "../SquareClass/SquareClass.hpp"
#include "../ResourceManagerClass/ResourceManager.hpp"

#include <string>
#include <android/log.h>

class Object
{
private:
	Square *square = nullptr;
	int x1;
	int x2;
	int y1;
	int y2;
	
	int x1f;
	int x2f;
	int y1f;
	int y2f;
	bool visible;
	std::string name;
	Screen *screen;
	bool mobile;
public:
	Object(std::string, float, float, float, float, AAssetManager*, Screen *,const char*, const char*, bool mobile, ResourceManager *resourceManager, float uRepeatX = 1.0f, float uRepeatY = 1.0f);
	void Show(float, float, float, float, float);
	int isTouched(float x, float y);
	std::string getName();
	bool getVisibility();
	void setVisible(bool);
	~Object();
};

#endif