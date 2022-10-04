// person.h
// Copyright 1997, Gregory A. Riccardi

#ifndef ZIPPY_H
#define ZIPPY_H

#include <iostream>
#include "delim.h"

using namespace std;

class Zippy 
{
  public:
	// fields
	char ZipCode [10];
	char PlaceName [11];
	char State [3];
	char County [16];
	char Lat [9];
	char Long [9];
	//operations
	Zippy ();
	void Clear ();
	static int InitBuffer (DelimFieldBuffer &);
	int Unpack (IOBuffer &);
	int Pack (IOBuffer &) const;
	void Print (ostream &) const;
};

Zippy::Zippy (){Clear ();}

void Zippy::Clear ()
{
	// set each field to an empty string
	ZipCode [0] = 0; PlaceName [0] = 0; State [0] = 0;
	County [0] = 0; Lat [0] = 0; Long [0] = 0;
}

int Zippy::Pack (IOBuffer & Buffer) const
{// pack the fields into a FixedFieldBuffer, 
 // return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer . Clear ();
	numBytes = Buffer . Pack (ZipCode);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (PlaceName);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (State);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (County);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (Lat);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (Long);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int Zippy::Unpack (IOBuffer & Buffer)
{
	Clear ();
	int numBytes;
	numBytes = Buffer . Unpack (ZipCode);
	if (numBytes == -1) return FALSE;
	ZipCode[numBytes] = 0;
	numBytes = Buffer . Unpack (PlaceName);
	if (numBytes == -1) return FALSE;
	PlaceName[numBytes] = 0;
	numBytes = Buffer . Unpack (State);
	if (numBytes == -1) return FALSE;
	State[numBytes] = 0;
	numBytes = Buffer . Unpack (County);
	if (numBytes == -1) return FALSE;
	County[numBytes] = 0;
	numBytes = Buffer . Unpack (Lat);
	if (numBytes == -1) return FALSE;
	Lat[numBytes] = 0;
	numBytes = Buffer . Unpack (Long);
	if (numBytes == -1) return FALSE;
	Long[numBytes] = 0;
	return TRUE;
}

int Zippy::InitBuffer (DelimFieldBuffer & Buffer)
// initialize a DelimFieldBuffer to be used for Zippys
{	return TRUE;}

void Zippy::Print (ostream & stream) const
{
	stream << "Address:";
	stream << "\n\t       Zip Code '"<<ZipCode<<"'\n"
		<< "\t     Place Name '"<<PlaceName<<"'\n"
		<< "\t          State '"<<State<<"'\n"
		<< "\t         County '"<<County<<"'\n"
		<< "\t       Latitude '"<<Lat<<"'\n"
		<< "\t      Longitude '"<<Long<<"'\n" <<flush;
}

#endif
