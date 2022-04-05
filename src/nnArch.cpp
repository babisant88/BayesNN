/*
 * Arch.cpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */


#include <iostream>

#include "../hpp/nnArch.hpp"
#include "../hpp/utils.hpp"

nnArch::nnArch(){}


void nnArch::add_next_layer( Layer *curr_layer )
{
	if ( curr_layer->get_type() == FC )
	{
		fc *curr_fc_layer = ( fc* )( curr_layer );

		pipeline.push_back( curr_fc_layer );

		std::vector<Layer*>::iterator it_prev;
		it_prev = pipeline.end() - 2;

		int W_rows, W_cols;

		if( (*it_prev)->get_type() == INPUT )
		{
			in_Layer *the_in_layer = (in_Layer*)( (*it_prev) );
			W_cols = the_in_layer->get_size();
		}
		else
		{
			fc *prv_fc_layer = ( fc* )( (*it_prev) );
			W_cols = prv_fc_layer->get_size();
		}

		W_rows = curr_fc_layer->get_size();

		double *w_mean = new double[W_rows*W_cols];

		double *w_std = new double[W_rows*W_cols];
//		MatrixXd W( W_rows, W_cols );

		double *b = new double[curr_fc_layer->get_size()];
//		VectorXd b( curr_fc_layer->get_size() );

		this->w_mean.push_back( w_mean );
		this->w_std.push_back( w_std );
		bias.push_back( b );
	}
	else if( curr_layer->get_type() == INPUT )
	{
		in_Layer *the_in_layer = (in_Layer*)( curr_layer );
		pipeline.push_back( the_in_layer );
	}
	else if( curr_layer->get_type() == OUTPUT )
	{
		int W_rows, W_cols;

		out_Layer *the_out_layer = (out_Layer*)( curr_layer );
		pipeline.push_back( the_out_layer );

		std::vector<Layer*>::iterator it_prev;
		it_prev = pipeline.end() - 2;

		if( (*it_prev)->get_type() != FC )
		{
			cout << "The layer before the output must be FC" << endl;
			exit(-1);
		}
		else
		{
			fc *prv_fc_layer = ( fc* )( (*it_prev) );
			W_cols = prv_fc_layer->get_size();
		}

		W_rows = the_out_layer->get_size();

		double *w_mean = new double[W_rows*W_cols];

		double *w_std = new double[W_rows*W_cols];
//		MatrixXd W( W_rows, W_cols );

		double *b = new double[the_out_layer->get_size()];
//		VectorXd b( the_out_layer->get_size() );

		this->w_mean.push_back( w_mean );
		this->w_std.push_back( w_std );
		bias.push_back( b );
	}
}



void nnArch::print_all_layers_info()
{
	for( uint l_i=0; l_i < pipeline.size(); ++l_i )
	{
		cout << "The type of Layer " << l_i  << " is " << what_is_the_layer_type( pipeline[l_i]->get_type() ) << endl;

		if( pipeline[l_i]->get_type() == INPUT )
		{
			in_Layer *the_in_layer = ( in_Layer* )( pipeline[l_i] );

			cout << "number of neurons of the input layer: " << the_in_layer->get_size() << endl;
		}
		else if( pipeline[l_i]->get_type() == OUTPUT )
		{
			out_Layer *the_out_layer = ( out_Layer* )( pipeline[l_i] );

			cout << "number of neurons of the output layer: " << the_out_layer->get_size() << endl;
		}
		else if( pipeline[l_i]->get_type() == FC )
		{
			fc *fc_layer = ( fc* )( pipeline[l_i] );

			cout << "number of neurons of the output layer: " << fc_layer->get_size() << endl;
		}
	}
}



double* nnArch::predict( double *x )
{
	fc *prv_fc_layer = NULL;

	// Start from layer after the input layer
	uint l_i;
	for( l_i=1; l_i < pipeline.size(); ++l_i )
	{
		if( pipeline[l_i]->get_type() == FC )
		{
			fc *fc_layer = ( fc* )( pipeline[l_i] );

			if ( l_i == 1 ) // the layer just after the input layer
				fc_layer->eval( x, this->w_mean[l_i-1], this->w_std[l_i-1], this->bias[l_i-1], fc_layer->get_size(), 784 );
			else
				//fc *prv_fc_layer = dynamic_cast<fc*>( pipeline[i-1] );
				fc_layer->eval( prv_fc_layer->get_state_d(), this->w_mean[l_i-1], this->w_std[l_i-1], this->bias[l_i-1], fc_layer->get_size(), prv_fc_layer->get_size() );

			prv_fc_layer = fc_layer;
		}

		if( pipeline[l_i]->get_type() == OUTPUT )
			break;
	}

	out_Layer *the_out_Layer = ( out_Layer * )( pipeline[l_i] );

	if ( prv_fc_layer != NULL )
		the_out_Layer->eval( prv_fc_layer->get_state_d(), this->w_mean[l_i-1], this->w_std[l_i-1], this->bias[l_i-1], the_out_Layer->get_size(), prv_fc_layer->get_size() );

	return the_out_Layer->get_nn_out();
}



//vector<MatrixXd>& nnArch::get_weights()
//{
//	return weights;
//}



vector<double*>& nnArch::get_weights_mean()
{
	return w_mean;
}



vector<double*>& nnArch::get_weights_std()
{
	return w_std;
}



vector<Layer*>& nnArch::get_pipeline()
{
	return pipeline;
}



//vector<VectorXd>& nnArch::get_bias()
//{
//	return bias;
//}



vector<double*>& nnArch::get_bias()
{
	return bias;
}
