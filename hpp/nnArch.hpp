/*
 * Arch.hpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */

#ifndef HPP_NNARCH_HPP_
#define HPP_NNARCH_HPP_

#include <vector>

//#include "../hpp/Layer.hpp"
#include "../hpp/fc.hpp"
#include "../hpp/in_Layer.hpp"
#include "../hpp/fc.hpp"
#include "../hpp/out_Layer.hpp"

using namespace std;

class nnArch
{
	public:
			nnArch();

			void add_next_layer( Layer* );
//			vector<MatrixXd>& get_weights();
//			vector<VectorXd>& get_bias();
			vector<double*>& get_weights_mean();
			vector<double*>& get_weights_std();
			vector<double*>& get_bias();
			vector<Layer*>& get_pipeline();
			void print_all_layers_info();
//			VectorXd &  predict( VectorXd );
			double* predict( double* );

	private:

			vector<Layer*> pipeline;
//			vector<MatrixXd> weights;
//			vector<VectorXd> bias;
			vector<double*> w_mean;
			vector<double*> w_std;
			vector<double*> bias;
};


#endif /* HPP_NNARCH_HPP_ */
