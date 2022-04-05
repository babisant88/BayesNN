/*
 * in_Layer.hpp
 *
 *  Created on: Mar 28, 2022
 *      Author: babis
 */

#ifndef HPP_IN_LAYER_HPP_
#define HPP_IN_LAYER_HPP_

#include "Layer.hpp"


class in_Layer: public Layer
{
	public:
			in_Layer( int, _layer_type_ );
			//~in_Layer();

			int get_size();

//			VectorXd & get_nn_in();

	private:

			int size;

//			VectorXd nn_in;
};


#endif /* HPP_IN_LAYER_HPP_ */
