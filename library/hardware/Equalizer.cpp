/*
 * Equalizer.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: k6u0b
 */

#include "Equalizer.h"

#include "Assert.h"

Equalizer* equalizer_instance = 0;

Equalizer* Equalizer::getInstance() {
	M_Stack();
	if(equalizer_instance == 0) {
			equalizer_instance = new Equalizer;
		}
	M_Unstack();
	return equalizer_instance;
}

int Equalizer::getTreble() {
	return treble;
}

int Equalizer::getBass() {
	return bass;
}

void updateTreble(int treble) {
	M_Stack();
	if(treble > 5) {
		treble = 5;
	} else if(treble < 0) {
		treble = 0;
	}

	Treble_Out = treble;
	M_Unstack();
}

void updateBass(int bass) {
	M_Stack();
	if(bass > 5) {
		bass = 5;
	} else if(bass < 0) {
		bass = 0;
	}

	Bass_Out = bass;
	M_Unstack();
}




