// Copyright Informatikonline.net 2016
// This file is part of csvtotex.
//
//	csvtotex is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.

//	csvtotex is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License
//	along with csvtotex.  If not, see <http://www.gnu.org/licenses/>.

#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdio.h>

// Do the build on a windows system?
#ifndef _WIN32
#include <errno.h>
#endif

// Do we use cmake to build the program?
#ifdef CMAKE_BUILD
#include <csvtotex_config.h>
#endif

// If not, define "default" version
#ifndef VERSION
#define VERSION 1.01
#endif

// Helper functions for preprocessor defines
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

int calculate_buffer_size(char* inbuf, int length) {
	int o_size = 0;
	for(int i= 0; i < length; i++) {
		switch(inbuf[i]) {
			case ';': // ' & '
			o_size+=3;
			break;
			case '\n':  // '\\\n\hline\n'
			o_size+=10;
			break;
			case '\r':
			break;
			default:
			o_size++;
			break;
		}
	}
	return o_size;
}

void print_usage(char* name) {
	fprintf(stderr, "Usage:\t %s [tex-file] or\n\t %s [tex file] > output_file", name,name);
}
int main(int argc, char** argv) {
	setlocale(LC_ALL,"");
	char* filepath = NULL;
	FILE* openfile;

	// Wurde eine Datei übergeben?
	if(argc < 2) {
		print_usage(argv[0]);
		exit(-1);
	}
	if(!strcmp(argv[1], "-v"))  {
		printf("Copyright 2016 - Sebastian Tilders\n");
		printf("Program Version %s\n", TOSTRING(VERSION)); 
		exit(0);
	}
	filepath = argv[1];
	openfile = fopen(filepath, "rb");

	// Wurde die richtige Datei angegeben?
	if(!openfile) {
		fprintf(stderr, "Die Datei \"%s\" konnte nicht geöffnet werden: %s\n", filepath,strerror(errno));
		print_usage(argv[0]);
		exit(errno);
	}

	// Ermittel Dateigröße
	fseek(openfile, 0,SEEK_END);
	int input_size = ftell(openfile);
	fseek(openfile,0,SEEK_SET);

	// Alloziere Speicher für Input-Daten
	char* inputbuffer = NULL;
	if(!(inputbuffer = malloc(input_size+1))) {
		perror("No memory available!");
		exit(errno);
	}

	// Lese die Daten ein
	fread(inputbuffer, 1,input_size,openfile);
	fclose(openfile);
	inputbuffer[input_size] = 0;
	// Berechne die größe des Output-Buffers
	int output_size = calculate_buffer_size(inputbuffer,input_size);
	output_size++;
	if(output_size <= input_size) {
		fprintf(stderr, "Type Overflow!\n");
		exit(-2);
	}

	// Alloziere Output-Buffer
	char* output_buffer = NULL;
	if(!(output_buffer = malloc(output_size+8))) {
		perror("No memory available!");
		exit(errno);
	}

	// Und führe die Konvertierung durch
	int input_idx = 0;
	int output_idx = 0;
	memset(output_buffer, 0,output_size);
	strcpy(output_buffer, "\\hline\n");
	output_idx += 7;
	output_size += 7;
	fprintf(stderr, "Input size: %d Bytes - Output size: %d Bytes\n",input_size, output_size);
	while((input_idx < input_size) && (output_idx < output_size)) {
		switch(inputbuffer[input_idx]) {
			case ';':
			strcpy(output_buffer+output_idx, " & ");
			output_idx+=3;
			input_idx++;
			break;
			case '\n':
			strcpy(output_buffer+output_idx, "\\\\\n\\hline\n");
			output_idx+=10;
			input_idx++;
			break;
			case '\r':
			input_idx++;
			break;
			default:
			output_buffer[output_idx] = inputbuffer[input_idx];
			input_idx++;
			output_idx++;
			break;
		}
	}
	output_buffer[output_size] = 0;
	printf("%s", output_buffer);
	free(inputbuffer);
	free(output_buffer);
	exit(EXIT_SUCCESS);
}