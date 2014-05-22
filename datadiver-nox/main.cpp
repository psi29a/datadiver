#include "datadiver.h"

int main(void){
	DataDiver test;
	test = DataDiver_CreateContext();
	DataDiver_DestroyContext(test);
	return (0);
}
