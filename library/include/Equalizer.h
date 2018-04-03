/*
 * Equalizer.h
 *
 *  Created on: Mar 31, 2018
 *      Author: k6u0b
 */

#ifndef EQUALIZER_H_
#define EQUALIZER_H_

#define Treble_Out (*(volatile signed char*) (0x0000030))
#define Bass_Out (*(volatile signed char*) (0x0000040))

class Equalizer {
	int treble;
	int bass;
public:
	static Equalizer* getInstance();
	int getTreble();
	int getBass();
	void updateTreble(int treble);
	void updateBass(int bass);
};

#endif /* EQUALIZER_H_ */
