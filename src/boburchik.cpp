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
#include "bitstreamer.h"
#include "huffman.h"

using std::cout;
using std::endl;
using std::cerr;
using std::ofstream;
using std::ifstream;
using std::size_t;
using std::vector;
using std::ios_base;
using std::ios;

byte *buffer = nullptr;
clock_t timekeeper;

typedef struct _file{

	ifstream ifp;
	ofstream ofp;

	unsigned int ilength;
	unsigned int olength;


} ifile;

ifile* init_file(string option, char *pinfile, char *poutfile);
byte *load_file(char *pfile, unsigned int length);
void generate_frequency_table(vector<int> &rfreqs, unsigned int len, byte *buffer);

int main(int argc, char **argv) {

	if(argc != 4){
		HELP()
		return EXIT_FAILURE;
	} else{
		timekeeper = clock();
		std::string option = argv[0x1];
		ifile *infile;
		huffman huff;

		if(option == "-c"){
			vector<int> frequencies(UCHAR_MAX, 0);

			infile = init_file(option, CMD_INPUT_FILE, CMD_OUTPUT_FILE);
			if(!infile){
				cerr << "Unable to open input file." << endl;
				return EXIT_FAILURE;
			}

			generate_frequency_table(frequencies, infile->ilength, buffer);

			bitstreamer bitout(infile->ifp, infile->ofp);

			huff.buildTreeComp(frequencies, infile->ilength, bitout);

			while(1) {
				byte sym = infile->ifp.get();
			    if(infile->ifp.eof())
			    	break;
			   huff.encode(sym, bitout);
			}

			bitout.padding();
			infile->olength = infile->ofp.tellp();
		}else if(option == "-d"){
			infile = init_file(option, CMD_INPUT_FILE, CMD_OUTPUT_FILE);
			bitstreamer bitout(infile->ifp, infile->ofp);
			unsigned int chCnt = huff.buildTreeUncomp(bitout);
			int sym;
			unsigned int counter = 0;
			while( counter != chCnt ) {

			    sym = huff.decode( bitout );

			    if( sym == -1 )
			      break;

			    infile->ofp.put((byte)sym);
			    counter++;
			  }
			  infile->ofp.seekp( 0, infile->ofp.end);
			  infile->olength = infile->ofp.tellp();

		} else {
			HELP()
			return EXIT_FAILURE;
		}
		if(buffer)
			delete [] buffer;
		if(infile){
			infile->ifp.close();
			infile->ofp.close();
			delete infile;
		}
	}

	timekeeper = clock() - timekeeper;

	return EXIT_SUCCESS;
}


ifile* init_file(string option, char *pinfile, char *poutfile){
	ifile *ipfile = new ifile;

	FILE *fp = fopen(pinfile, "rb");
	if( !fp ){
		cout << "Invalid input file. No file was opened. Please try again." << endl;
		return nullptr;
	}

	fseek(fp, 0, SEEK_END);
	ipfile->ilength = ftell(fp);
	fclose(fp);

	if(option == "-c"){
		::buffer = load_file(pinfile, ipfile->ilength);
		if(!buffer){
			cerr << "Unable to read input file." << endl;
			delete ipfile;
			delete [] buffer;
			return nullptr;
		}

		ipfile->ofp.open(poutfile, ios::out | ios::binary | ios::trunc);
		if(!ipfile->ofp.is_open()){
			cerr << "Unable to open file for writing.. exiting.." << endl;
			delete [] buffer;
			delete ipfile;
			return nullptr;
		}

	} else{
		ipfile->ofp.open(poutfile, ios::out | ios::binary);
		if(!ipfile->ofp.is_open()){
			cerr << "Unable to open file for writing.. exiting.." << endl;
			delete ipfile;
			return nullptr;
		}
	}

	ipfile->ifp.open(pinfile, ios::binary);

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

