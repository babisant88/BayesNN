/*
 * output.cpp
 *
 *  Created on: Mar 24, 2022
 *      Author: babis
 */

#include <iostream>

#include "../hpp/out_Layer.hpp"
#include "../hpp/utils.hpp"

using namespace std;



out_Layer::out_Layer( int size, _act_fn_ act_fn, _layer_type_ the_layer_type ) : Layer( the_layer_type )
{
	this->size = size;
	this->act_fn = act_fn;

//	this->nn_out = VectorXd::Zero(size, 1);
	//this->layer_type_in_pipe = type_of_layer_in_pipe;
	this->nn_out = new double[size]();
}



_act_fn_ out_Layer::get_act_fn()
{
	return act_fn;
}



//VectorXd & out_Layer::get_nn_out()
//{
//	return nn_out;
//}



double *out_Layer::get_nn_out()
{
	return nn_out;
}



int out_Layer::get_size()
{
	return size;
}



void out_Layer::eval( double *in, double *w_mean, double *w_std, double *b, int w_rows, int w_cols )
{
//	this->nn_out = W * in + b;

	gemv( in, w_mean, w_std, b, this->nn_out, w_rows, w_cols );

	/* softmax act. function must be applied only for the output layer */
	if ( act_fn == none )
	{
		/*No action */
	}
	else if( act_fn == softmax )
	{
		double sum = 0;

		/* sum of all output exponentials */
		for( int i=0; i < this->size; ++i )
			sum += exp( this->nn_out[i] );

		for( int i=0; i < this->size; ++i )
			this->nn_out[i] = this->nn_out[i]/sum;
	}
	else
	{
		cout << "No other than softmax activation function is defined for the output layer" << endl;
		exit(-1);
	}
}
