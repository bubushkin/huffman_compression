//============================================================================
// Name        : boburchik.cpp
// Author      : Iskandar Askarov
// Version     :
// Copyright   : Use it all you want!!!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <vector>

#include "udef.h"

using std::cout;
using std::endl;
using std::cerr;
using std::fstream;
using std::size_t;
using std::vector;
using std::ios_base;
using std::ios;

clock_t timekeeper;

typedef struct _file{

	fstream fp;
	unsigned int length;

} ifile;

ifile* init_file(char *pfile);
byte *load_file(char *pfile, unsigned int length);
void generate_frequency_table(vector<int> &rfreqs, unsigned int len, byte *buffer);

int main(int argc, char **argv) {

	if(argc != 4){
		HELP()
		return EXIT_FAILURE;
	}
	byte *buffer;
	timekeeper = clock_t();
	vector<int> symbolFrequency(UCHAR_MAX, 0);
	ifile *infile = init_file(CMD_INPUT_FILE);
	ifile *outfile;

	if(!infile){
		cerr << "Unable to open input file." << endl;
		return EXIT_FAILURE;
	}

	buffer = load_file(CMD_INPUT_FILE, infile->length);
	if(!buffer){
		cerr << "Unable to read input file." << endl;
		return EXIT_FAILURE;
	}

	generate_frequency_table(symbolFrequency, infile->length, buffer);

	outfile = new ifile;
	outfile->fp.open(CMD_OUTPUT_FILE, ios::out | ios::binary | ios::trunc);
	if(!outfile->fp.is_open()){
		cerr << "Unable to open file for writing.. exiting.." << endl;
		delete [] buffer;
		delete infile;
		delete outfile;
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}


ifile* init_file(char *pfile){
	ifile *ipfile = new ifile;

	FILE *fp = fopen(pfile, "rb");
	if( !fp ){
		cout << "Invalid input file. No file was opened. Please try again." << endl;
		return nullptr;
	}

	fseek(fp, 0, SEEK_END);
	ipfile->length = ftell(fp);
	fclose(fp);

	return ipfile;
}

byte *load_file(char *pfile, unsigned int length){

	size_t read_count = 0;
	byte *buffer = new byte[length];
	FILE *fp = fopen(pfile, "rb");

	if( !fp ){
		return nullptr;
	}

	read_count = fread(buffer, sizeof(byte), length, fp);

	if(read_count != length){
		return nullptr;
	}

	fclose(fp);

	return buffer;
}

void generate_frequency_table(vector<int> &rfreqs, unsigned int len, byte *buffer){
	for( unsigned int i = 0; i < len; i++ ){
		rfreqs[(int) buffer[i]]++;
	}
}

