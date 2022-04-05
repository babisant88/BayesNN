/*
 * Layer.cpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */


#include "../hpp/Layer.hpp"


Layer::Layer(){
	this->type = UNDEFINED;
}



Layer::Layer( _layer_type_ the_type ){
	this->type = the_type;
}



_layer_type_ Layer::get_type(){
	return type;
}



void Layer::set_type( _layer_type_ the_type ){
	this->type = the_type;
}
