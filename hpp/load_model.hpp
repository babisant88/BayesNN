/*
 * load_model.hpp
 *
 *  Created on: Mar 21, 2022
 *      Author: babis
 */

#ifndef HPP_LOAD_MODEL_HPP_
#define HPP_LOAD_MODEL_HPP_

#include "../hpp/nnArch.hpp"

nnArch *load_model( char* argv[] );

void load_arch( char*, char*, nnArch* );

// void load_wghts( char *filename, nnArch* );

#endif /* HPP_LOAD_MODEL_HPP_ */
