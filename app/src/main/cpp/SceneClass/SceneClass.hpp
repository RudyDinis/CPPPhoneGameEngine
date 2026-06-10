/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneClass.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:06:40 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/10 15:08:33 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENECLASS_HPP
#define SCENECLASS_HPP

#include <map>
#include <vector>
#include "../ObjectClass/ObjectClass.hpp"
#include "../TextClass/TextClass.hpp"
#include "../ScreenClass/ScreenClass.hpp"

typedef struct s_text_value
{
	const char *font;
    float x, y;
    float r, g, b, a;
} t_text_value;



class Scene
{
private:
	std::vector<Object *> Objects;
	Text * text;
	std::map<std::string, s_text_value> TextData;
	Screen *screen;
	bool canMoove = false;
public:
	Scene(Screen *screen);
	void addObject(Object *);
	std::vector<Object *> getObject();

	Text *getText();
	void addText(std::string, s_text_value);

	bool getCanMoove();
	void setCanMoove(bool);
	
	void render();
	~Scene();
};


#endif