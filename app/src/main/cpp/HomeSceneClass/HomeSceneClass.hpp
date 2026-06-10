/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HomeSceneClass.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:07:03 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/10 11:14:50 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOMESCENECLASS_HPP
#define HOMESCENECLASS_HPP

#include "../SceneClass/SceneClass.hpp"
#include "../ObjectClass/ObjectClass.hpp"

class HomeScene : public Scene
{
private:
	std::string name;
	AAssetManager *mgr;
	Screen *screen;
public:
	HomeScene(std::string, AAssetManager*, Screen *);
	~HomeScene();
};

#endif