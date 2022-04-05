/*
 * output.hpp
 *
 *  Created on: Mar 24, 2022
 *      Author: babis
 */

#ifndef HPP_OUT_LAYER_HPP_
#define HPP_OUT_LAYER_HPP_

#include "Layer.hpp"

class out_Layer: public Layer
{
	public:
			out_Layer( int, _act_fn_, _layer_type_ );
			//~out_Layer();

			int get_size();
			_act_fn_ get_act_fn();

//			void eval( VectorXd &, MatrixXd &, VectorXd & );
			void eval( double *, double *, double *, double *, int, int );

//			VectorXd & get_nn_out();
			double *get_nn_out();

	private:

			// int dim;
			// int * dim_size;

			int size;
			_act_fn_ act_fn;

//			VectorXd nn_out;
			double *nn_out;
};

#endif /* HPP_OUT_LAYER_HPP_ */
