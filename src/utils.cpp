/*
 * aux.cpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */

#include <cmath>
#include <random>
#include "../hpp/utils.hpp"

using namespace std;

double act_fn_eval( double x, _act_fn_ act_fn )
{
	double res;

	if( act_fn == relu )
	{
		if ( x < 0 )
			res = 0;
		else
			res = x;
	}
	else if ( act_fn == sigmoid )
		res = 1/(1+exp(-x));

	return res;
}



string what_is_the_layer_type( _layer_type_ what_layer_type )
{
	string type;

	if( what_layer_type == 0 )
		type = "UNDEFINED";
	else if( what_layer_type == 1 )
		type = "INPUT";
	else if ( what_layer_type == 2 )
		type = "FC";
	else if ( what_layer_type == 3 )
		type = "CONV";
	else if ( what_layer_type == 4 )
		type = "POOL";
	else if ( what_layer_type == 5 )
		type = "OUTPUT";

	return type;
}



void gemv( double *in, double *w_mean, double *w_std, double *b, double *res, int w_rows, int w_cols )
{
	std::default_random_engine generator;

	for( uint row_i=0; row_i < w_rows; ++ row_i )
	{
		res[row_i] = 0;
		for( uint col_i=0; col_i < w_cols; ++col_i )
		{
			std::normal_distribution<double> gaussian_d( w_mean[row_i*w_cols + col_i], w_std[row_i*w_cols + col_i] );
			res[row_i] += gaussian_d(generator) * in[col_i];
		}

		res[row_i] += b[row_i];
	}
}
