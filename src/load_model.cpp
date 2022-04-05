/*
 * load_model.cpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */


#include <iostream>
#include <fstream>
#include <cstring>

#include "../hpp/load_model.hpp"

using namespace std;



nnArch* load_model( char* argv[] )
{
	nnArch *arch = new nnArch();

	load_arch( argv[1], argv[2], arch );

	return arch;
}



void load_arch( char* arch_def_filename, char* arch_param_filename, nnArch* arch )
{
	string line, line2;
	ifstream arch_def_file( arch_def_filename );

	ifstream arch_param_file( arch_param_filename );

	int l_i = 0;

	if( arch_def_file.is_open() )
	{
		while( getline( arch_def_file, line ) )
		{
			char * pch;
			pch = strtok( (char *)line.c_str(), " " );

			if( pch != NULL )
			{
				if( !strcmp(pch, "input") )
				{
					pch = strtok (NULL, " ");

					int size = atoi(pch);

					in_Layer *curr_layer = new in_Layer( size, INPUT );

					arch->add_next_layer( curr_layer );
				}
				else if( !strcmp(pch, "output") )
				{
					pch = strtok (NULL, " ");

					int size = atoi(pch);

					pch = strtok (NULL, " ");

					_act_fn_ act_fn = none;

					if( !strcmp(pch, "softmax") )
						act_fn = softmax;

					out_Layer *curr_layer = new out_Layer( size, act_fn, OUTPUT );

					arch->add_next_layer( curr_layer );

					int row_i = 0;
					char * pch2;

					vector<double*> w_mean = arch->get_weights_mean();

					int w_rows = size;
					int w_cols;

					std::vector<Layer*>::iterator it_prev;
					it_prev = arch->get_pipeline().end() - 2;

					if( (*it_prev)->get_type() != FC )
					{
						cout << "The layer before the output must be FC" << endl;
						exit(-1);
					}
					else
					{
						fc *prv_fc_layer = ( fc* )( (*it_prev) );
						w_cols = prv_fc_layer->get_size();
					}

					while( row_i < w_rows )
					{
						getline( arch_param_file, line2 );

						pch2 = strtok( (char *)line2.c_str(), " " );

						int col_i;
						for( col_i=0; col_i < w_cols; ++col_i )
						{
							w_mean[l_i][row_i*w_cols + col_i] = atof( pch2 );
							pch2 = strtok (NULL, " ");
						}
						row_i++;
					}

					vector<double*> w_std = arch->get_weights_std();

					row_i = 0;
					while( row_i < w_rows )
					{
						getline( arch_param_file, line2 );

						pch2 = strtok( (char *)line2.c_str(), " " );

						int col_i;
						for( col_i=0; col_i < w_cols; ++col_i )
						{
							w_std[l_i][row_i*w_cols + col_i] = atof( pch2 );
							pch2 = strtok (NULL, " ");
						}
						row_i++;
					}

					getline( arch_param_file, line2 );

					pch2 = strtok( (char *)line2.c_str(), " " );

//					vector<VectorXd>& bias = arch->get_bias();

					vector<double*> bias = arch->get_bias();

					int b_i;
					for( b_i=0; b_i < curr_layer->get_size(); ++b_i )
					{
						bias[l_i][b_i] = atof(pch2);
						pch2 = strtok (NULL, " ");
					}

					l_i++;
				}
				else if( !strcmp(pch, "fc") )
				{
					pch = strtok (NULL, " ");

					int size = atoi(pch);

					pch = strtok (NULL, " ");

					_act_fn_ act_fn = none;

					if( !strcmp(pch, "relu") )
						act_fn = relu;
					else if( !strcmp(pch, "sgm") )
						act_fn = sigmoid;
					else // Sanity check
					{
						cout << "Not registered activation function" << endl;
						exit(-1);
					}

					pch = strtok (NULL, " ");

					bool batch_norm = false;

					if ( pch != NULL )
						if ( !strcmp(pch, "BN") )
							batch_norm = true;

					fc *curr_layer = new fc(size, act_fn, FC, batch_norm);

					arch->add_next_layer( curr_layer );

					int row_i = 0;
					char * pch2;

//					vector<MatrixXd>& weights = arch->get_weights();

					vector<double*> w_mean = arch->get_weights_mean();

					int w_rows = size;
					int w_cols;

					std::vector<Layer*>::iterator it_prev;
					it_prev = arch->get_pipeline().end() - 2;

					if( (*it_prev)->get_type() != INPUT )
					{
						in_Layer *the_in_layer = ( in_Layer* )( (*it_prev) );
						w_cols = the_in_layer->get_size();
					}
					else
					{
						fc *prv_fc_layer = ( fc* )( (*it_prev) );
						w_cols = prv_fc_layer->get_size();
					}

					while( row_i < w_rows )
					{
						getline( arch_param_file, line2 );

						pch2 = strtok( (char *)line2.c_str(), " " );

						int col_i;
						for( col_i=0; col_i < w_cols; ++col_i )
						{
							w_mean[l_i][row_i*w_cols + col_i] = atof( pch2 );
							pch2 = strtok (NULL, " ");
						}
						row_i++;
					}

					vector<double*> w_std = arch->get_weights_std();

					row_i = 0;
					while( row_i < w_rows )
					{
						getline( arch_param_file, line2 );

						pch2 = strtok( (char *)line2.c_str(), " " );

						int col_i;
						for( col_i=0; col_i < w_cols; ++col_i )
						{
							w_std[l_i][row_i*w_cols + col_i] = atof( pch2 );
							pch2 = strtok (NULL, " ");
						}
						row_i++;
					}

					getline( arch_param_file, line2 );

					pch2 = strtok( (char *)line2.c_str(), " " );

					//vector<VectorXd>& bias = arch->get_bias();

					vector<double*> bias = arch->get_bias();

					int b_i;
					for( b_i=0; b_i < curr_layer->get_size(); ++b_i )
					{
						bias[l_i][b_i] = atof( pch2 );
						pch2 = strtok( NULL, " " );
					}

					/* batch_norm_params[0] -> batch_gamma
					 * batch_norm_params[1] -> batch_beta
					 * batch_norm_params[2] -> batch_mean
					 * batch_norm_params[3] -> batch_var
					 * */

					double** batch_norm_params = curr_layer->get_batch_norm();

					if( batch_norm )
					{
						for( uint prm_i = 0; prm_i < 4; ++prm_i )
						{
							getline( arch_param_file, line2 );

							pch2 = strtok( (char *)line2.c_str(), " " );

							for( int prm_ii=0; prm_ii < curr_layer->get_size(); ++prm_ii )
							{
								batch_norm_params[prm_i][prm_ii] = atof( pch2 );
								pch2 = strtok( NULL, " " );
							}
						}
					}

					l_i++;

					cout << l_i << endl;
				}
			}
		}
	}

	arch_def_file.close();

	arch_param_file.close();
}
