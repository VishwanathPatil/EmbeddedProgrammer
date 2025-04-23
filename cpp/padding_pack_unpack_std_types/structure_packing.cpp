#include <stdio.h>
#include <stdint.h>

class CheckSizeAndNonPack {
	bool a;
	// padding happens
	uint32_t b;
	uint8_t c;
	// no padding happens when standard types are used like,
	// uint8_t, uint16_t, uint32_t are used
	uint16_t d;
};

class CheckSizeAndPack {
	bool a;
	uint32_t b;
	uint8_t c;
	uint16_t d;
}__attribute__((packed));

int main() {
	printf("packed size:%lu , unpacked structure :%lu", sizeof(CheckSizeAndPack), 
			sizeof(CheckSizeAndNonPack));
}
