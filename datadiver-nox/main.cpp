#include "datadiver.h"

int main(void){
	DataDiver test;
	test = DataDiver_CreateContext();
	DataDiver_OpenFile(test, "/home/bcurtis/Downloads/debian-7.4.0-amd64-netinst.iso");
	DataDiver_DestroyContext(test);
	return (0);
}
