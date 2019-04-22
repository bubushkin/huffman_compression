/*
 * udef.h
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#ifndef UDEF_H_
#define UDEF_H_

typedef unsigned char byte;

#define HELP()  cout << "HELP USAGE: "<< endl; \
                cout << argv[0x0] << " OPTIONS INPUT_FILE OUTPUT_FILE"<< endl; \
                cout << "OPTIONS:" << endl; \
                cout << "\t-c\t:compress" << endl; \
                cout << "\t-d\t:decompress" << endl; \


#define CMD_INPUT_FILE argv[2]
#define CMD_OUTPUT_FILE argv[3]

#endif /* UDEF_H_ */
