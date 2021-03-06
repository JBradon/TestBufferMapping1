// TestBufferMapping1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"   /this seems to need to be first
#include "windows.h"
#include "stdio.h"
#include "iostream"  //for cout,cin
using namespace std; //for cout,cin
#include <chrono>
#include <thread>
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

const DWORD dwChunkSize = 32;
const DWORD maxWord = 2 ^ 16;

// PCMdata does not use pointers
union PCMdata {
	BYTE DataBytes[dwChunkSize];
    WORD DataInt[dwChunkSize/2]; // Word is 16 bit windows format
};

// PCMPtrData does use pointers
union PCMPtrData {
	BYTE * pDataBytes = new BYTE[dwChunkSize];
	WORD DataIntP[dwChunkSize / 2]; // Word is 16 bit windows format
};


int main() {

	//basics
	BYTE TestByte {15};
	cout << "Byte Value raw: " << TestByte << "\n";
	printf("Byte Value as number: %u \n" , TestByte );
	printf("Byte Value as hex   : %x \n", TestByte); // X hexadecimal with capitals

	//--------- First without pointers
	PCMdata pcm;

	int j;
	for (j = 0; j < dwChunkSize / 2; j++) {
		pcm.DataInt[j] = j * j;//% maxWord; //% is modulus
	}
	
	cout << "DataInt: ";
	for (j = 0; j < dwChunkSize / 2; j++) {
		cout << ", " << pcm.DataInt[j];
	}
	cout << "\n";

	printf ( "Bytes: ");
	for (j = 0; j < dwChunkSize ; j++) {
		printf (", %u" , pcm.DataBytes[j]); //&pcm.pDataBuffer[0]// (unsigned __int8) &pcm.pDataBuffer[j])
	}
	cout << "\n";


	BYTE * pDataBuffer = &pcm.DataBytes[0]; //was 	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	printf("Bytes via ptr: ");
	for (j = 0; j < dwChunkSize; j++) {
		printf(", %u", pcm.DataBytes[j]); //&pcm.pDataBuffer[0]// (unsigned __int8) &pcm.pDataBuffer[j])
	}
	for (BYTE * p = pDataBuffer; p < pDataBuffer + dwChunkSize; p++) {
		printf(", %u", *p);
	}

	printf("Pointer Value as hex    : %x \n", pDataBuffer); // X hexadecimal with capitals
	printf("Pointer Value+ 1 as hex: %x \n", pDataBuffer+1); // X hexadecimal with capitals
//	printf("Value at Pointer Value[0]    : %u \n", *pDataBuffer); // X hexadecimal with capitals
//	printf("Value at Pointer Value[1]    : %u \n", *(pDataBuffer + 1)); // X hexadecimal with capitals
//	printf("Value at Pointer Value[2]    : %u \n", *(pDataBuffer + 2)); // X hexadecimal with capitals




//-------------Second with pointers

	PCMPtrData pcmPtr;
 //was 	BYTE * pDataBuffer = new BYTE[dwChunkSize];

	for (j = 0; j < dwChunkSize / 2; j++) {
		pcmPtr.DataIntP[j] = j * j;//% maxWord; //% is modulus
	}

	cout << "DataIntP: ";
	for (j = 0; j < dwChunkSize / 2; j++) {
		cout << ", " << pcmPtr.DataIntP[j];
	}
	cout << "\n";
	cout << "BYTES via pointer: ";
	for (BYTE * p = pcmPtr.pDataBytes; p < pcmPtr.pDataBytes + dwChunkSize; p++) {
		printf(", %u", *p);
	}
	cout << "\n";

	printf("Pointer Value as hex    : %x \n", pcmPtr.pDataBytes); // X hexadecimal with capitals
	printf("Pointer Value+ 1 as hex: %x \n", pcmPtr.pDataBytes + 1); // X hexadecimal with capitals
	printf("Value at Pointer Value[0]    : %u \n", *pcmPtr.pDataBytes); // X hexadecimal with capitals
	printf("Value at Pointer Value[1]    : %u \n", *(pcmPtr.pDataBytes + 1)); // X hexadecimal with capitals
	printf("Value at Pointer Value[2]    : %u \n", *(pcmPtr.pDataBytes + 2)); // X hexadecimal with capitals

	cout << "\n";
	cout << "\n";


	cout << "Address, Content: " << pcmPtr.pDataBytes << "," << *pcmPtr.pDataBytes << "\n";
	printf ( "pf Address, Content: " , pcmPtr.pDataBytes , "," , *pcmPtr.pDataBytes );
	cout << "\n";
	printf("Ptr Bytes: ");
	for (BYTE* p = pcmPtr.pDataBytes; p < pcmPtr.pDataBytes + dwChunkSize;p++){
		printf(", %u", *p); 
	}
	cout << "\n";



//----------- modify just one byte array
	BYTE * pDataBuffer2 = new BYTE[dwChunkSize];
	*pDataBuffer2 = 5;

	int i;
//	cout << "Please enter an integer value: ";
//	cin >> i;
//	cout << "The value you entered is " << i;




	sleep_for(10ns);



	sleep_until(system_clock::now() + 1s);



    return 0;
}

