// Line numbers for each section -- When the AI learns new words, it will need to offset this by the number of words learnt. When the AI shuts down, it will need to open the text file and update these numbers.
#pragma once

#include <map>

std::map <char, int> letterMap;

void initMap()
{
	letterMap['a'] = 0;
	letterMap['b'] = 5955;
	letterMap['c'] = 11362;
	letterMap['d'] = 21531;
	letterMap['e'] = 27426;
	letterMap['f'] = 31161;
	letterMap['g'] = 36159;
	letterMap['h'] = 39777;
	letterMap['i'] = 46314;
	letterMap['j'] = 50235;
	letterMap['k'] = 51255;
	letterMap['l'] = 52236;
	letterMap['m'] = 56067;
	letterMap['n'] = 62061;
	letterMap['o'] = 64278;
	letterMap['p'] = 66996;
	letterMap['q'] = 75693;
	letterMap['r'] = 76254;
	letterMap['s'] = 81723;
	letterMap['t'] = 94198;
	letterMap['u'] = 100119;
	letterMap['v'] = 103542;
	letterMap['w'] = 105126;
	letterMap['x'] = 108477;
	letterMap['y'] = 108519;
	letterMap['z'] = 108939;
	letterMap['z' + 1] = 109132;
}