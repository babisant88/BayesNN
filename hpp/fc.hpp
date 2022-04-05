/*
 * ff.hpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */

#ifndef HPP_FC_HPP_
#define HPP_FC_HPP_

#include "../hpp/types.hpp"
#include "../hpp/Layer.hpp"



class fc: public Layer
{
	public:

			fc();
			fc( int );
			fc( int, _act_fn_, _layer_type_, bool );
			//~fc();

			int get_size();

			_act_fn_ get_act_fn();

			void eval( double*, double*, double*, double*, int, int );
//			void eval( VectorXd &, MatrixXd &, VectorXd & );
//			VectorXd& get_state();

			double *get_state_d();

			double**& get_batch_norm();

	private:

			// int dim;
			// int * dim_size;

			int size;
			_act_fn_ act_fn;

//			VectorXd state;

			double **batch_norm;

			double *state_d;
};

#endif /* HPP_FC_HPP_ */
