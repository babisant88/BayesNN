/*
 * types.hpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */

#ifndef HPP_TYPES_HPP_
#define HPP_TYPES_HPP_

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/SparseCholesky>

using namespace Eigen;

enum _act_fn_ {none = -1, relu = 0, sigmoid = 1, softmax = 2};

// enum _layer_type_in_pipe_ {input = 0, hidden = 1, output = 2};

enum _layer_type_ {UNDEFINED = 0, INPUT = 1, FC = 2, CONV = 3, POOL = 4, OUTPUT = 5};

typedef Matrix<double, Dynamic, Dynamic> MatrixXd;
typedef Matrix<double, Dynamic, 1> VectorXd;

#endif /* HPP_TYPES_HPP_ */
