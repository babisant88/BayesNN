/*
 * utils.hpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */

#ifndef HPP_UTILS_HPP_
#define HPP_UTILS_HPP_

#include <string>

#include "types.hpp"

double act_fn_eval( double x, _act_fn_ );

std::string what_is_the_layer_type( _layer_type_ what_layer_type );

void gemv( double*, double*, double*, double*, double*, int, int );

#endif /* HPP_UTILS_HPP_ */
