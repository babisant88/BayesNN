/*
 * fc.cpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */

#include <iostream>
#include <cmath>


#include "../hpp/fc.hpp"
#include "../hpp/utils.hpp"

using namespace std;

fc::fc( int size, _act_fn_ the_act_fn, _layer_type_ the_layer_type, bool batch_norm_enable ) : Layer( the_layer_type )
{
	this->size = size;
	this->act_fn = the_act_fn;
//	this->state = VectorXd::Zero(size, 1);

	this->state_d = new double[size];

	if( batch_norm_enable )
	{
		this->batch_norm = new double*[4];

		for( uint batch_par_i = 0; batch_par_i<4; batch_par_i++ )
			this->batch_norm[batch_par_i] = new double[size]();
	}
	else
		this->batch_norm  = NULL;
}



_act_fn_ fc::get_act_fn()
{
	return act_fn;
}



int fc::get_size()
{
	return size;
}



double *fc::get_state_d()
{
	return state_d;
}



double**& fc::get_batch_norm()
{
	return batch_norm;
}


//VectorXd& fc::get_state()
//{
//	return state;
//}



//double *fc::get_state_d()
//{
//	return state_d;
//}



//void fc::eval( VectorXd& in, MatrixXd& W, VectorXd& b )
//{
//	this->state = W * in + b;

//	if( act_fn == relu )
//	{
//		for( uint i=0; i < this->state.size(); ++i )
//		{
//			if ( this->state(i) < 0.0 )
//				this->state(i) = 0;
//		}
//	}
//	else if( act_fn == sigmoid )
//		for( uint i=0; i < this->state.size(); ++i )
//		{
//			this->state(i) = 1 / (1 + exp(-this->state(i)));
//		}
//	else
//	{
//		cout << "No other than relu or sigmoid activation functions is registered for a fc layer at that moment" << endl;
//		exit(-1);
//	}
//}



void fc::eval( double* in, double* w_mean, double* w_std, double* b, int w_rows, int w_cols )
{
	gemv( in, w_mean, w_std, b, this->state_d, w_rows, w_cols );

	if ( this->get_batch_norm() != NULL )
	{
		for( int x_i=0; x_i < size; x_i++ )
			this->state_d[x_i] = this->batch_norm[0][x_i] *
									((this->state_d[x_i] - this->batch_norm[2][x_i]) / sqrt(this->batch_norm[3][x_i] + 0.001))
										+ this->batch_norm[1][x_i];
	}

	if( act_fn == relu )
	{
		for( int i=0; i < this->size; ++i )
		{
			if ( this->state_d[i] < 0.0 )
				this->state_d[i] = 0;
		}
	}
	else if( act_fn == sigmoid )
		for( int i=0; i < this->size; ++i )
		{
			this->state_d[i] = 1 / (1 + exp(-this->state_d[i]));
		}
	else
	{
		cout << "No other than relu or sigmoid activation functions is registered for a fc layer at that moment" << endl;
		exit(-1);
	}
}
