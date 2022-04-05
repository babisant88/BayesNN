/*
 * Layer.hpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */

#ifndef HPP_LAYER_HPP_
#define HPP_LAYER_HPP_

#include "../hpp/types.hpp"

class Layer
{
	public:
			Layer();
			Layer( _layer_type_ );

			_layer_type_ get_type();
			void set_type( _layer_type_ );

	private:
			_layer_type_ type;
};

#endif /* HPP_LAYER_HPP_ */
