/*
 * in_Layer.cpp
 *
 *  Created on: Mar 28, 2022
 *      Author: babis
 */

#include "../hpp/in_Layer.hpp"



in_Layer::in_Layer( int size, _layer_type_ the_layer_type ) : Layer( the_layer_type )
{
	this->size = size;
}


int in_Layer::get_size()
{
	return size;
}
