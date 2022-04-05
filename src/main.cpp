/*
 * main.cpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */

#include <iostream>
#include <fstream>

#include <omp.h>
#include <chrono>

#include "../hpp/types.hpp"
#include "../hpp/load_model.hpp"

using namespace std;

// void load_input( char**, MatrixXd &, VectorXd & );

void load_input( char**, double*, int* );

int main( int argc, char *argv[] )
{
	nnArch *arch = NULL;

//	MatrixXd x( 10000, 784 ); // debug with mnist
	double *x = new double[7840000];

//	double *x_d = new double[10000][784];

//	VectorXd y( 10000 );

	int *y = new int[10000];

//	int *y_d = new int[10000];

	load_input( argv, x, y );

	arch = load_model( argv );

	arch->print_all_layers_info();

	int acc = 0;

	int mc_trials = 10;

	int *distro = new int[10]();

	for( int row_i = 0; row_i < 10000; ++row_i )
	{
		/* reset distro */
		for( int sample_i=0; sample_i < mc_trials; ++sample_i )
			distro[sample_i] = 0;

		int i_max_distro = 0;
		double max_distro_val = distro[0];

		for( int trial=0; trial < 10; ++trial )
		{
			double *curr_y = arch->predict( &x[row_i*784] );

			double max_y = curr_y[0];
			int i_max_y = 0;

			for ( uint i=0; i < 10; ++i )
				if( curr_y[i] > max_y )
				{
					max_y = curr_y[i];
					i_max_y = i;
				}
		//		if(  i_max_y == y[row_i] )

			distro[i_max_y] += 1;

			if( distro[i_max_y] > max_distro_val )
			{
				max_distro_val = distro[i_max_y];
				i_max_distro = i_max_y;
			}
		}

		if ( i_max_distro == y[row_i] )
			acc += 1;
	}

	cout << "acc = " << (double)(acc/10000.0) << endl;
}



void load_input( char* argv[], double* x, int* y )
{
	string line;
	ifstream x_file( argv[3] );

	int row_i, col_i;

	row_i = 0;

	if( x_file.is_open() )
	{
		while( getline( x_file, line ) )
		{
			char * pch;
			pch = strtok( (char *)line.c_str(), " " );

			col_i = 0;

			while ( pch != NULL )
			{
				x[row_i*784 + col_i] = atof( pch );
				col_i++;
				pch = strtok ( NULL, " " );
			}

			row_i++;
		}

		x_file.close();
	}
	else
		cout << "Unable to open file " << argv[3] << endl;


	ifstream y_file( argv[4] );

	row_i = 0;

	if( y_file.is_open() )
	{
		while( getline( y_file, line ) )
		{
			char * pch;
			pch = strtok( (char *)line.c_str(), " " );

			while( pch != NULL )
			{
				y[row_i] = atoi( pch );
				pch = strtok ( NULL, " " );
			}

			row_i++;
		}

		y_file.close();
	}
	else
		cout << "Unable to open file " << argv[4] << endl;
}
