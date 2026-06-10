/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:22:27 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/10 16:27:05 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERACLASS_HPP
#define CAMERACLASS_HPP

class Camera
{
private:
	float offset_y = 0.0f;
	float offset_x = 0.0f;
public:
	Camera(/* args */);
	float *getOffset_y();
	float *getOffset_x();
	~Camera();
};


#endif