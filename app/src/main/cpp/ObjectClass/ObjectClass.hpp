/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:59:14 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/10 16:55:03 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTCLASS_HPP
#define OBJECTCLASS_HPP

#include "../SquareClass/SquareClass.hpp"
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
	bool visible;
	std::string name;
	bool mobile;
public:
	Object(std::string, float, float, float, float, AAssetManager*, Screen *,const char*, bool mobile);
	void Show(float, float);
	int isTouched(float x, float y);
	std::string getName();
	bool getVisibility();
	void setVisible(bool);
	~Object();
};

#endif