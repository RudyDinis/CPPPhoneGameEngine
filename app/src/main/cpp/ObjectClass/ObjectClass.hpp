/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:59:14 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/09 18:45:45 by rdinis           ###   ########.fr       */
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
public:
	Object(std::string, int, int, int, int, AAssetManager*, Screen *,const char*);
	void Show();
	int isTouched(float x, float y);
	std::string getName();
	bool getVisibility();
	void setVisible(bool);
	~Object();
};

#endif