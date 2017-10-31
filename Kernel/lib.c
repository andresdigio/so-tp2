#include <stdint.h>

uint64_t toHex(const char * s) {
	uint64_t result = 0;
	int c ;
	if ('0' == *s && 'x' == *(s+1)) { s+=2;
	  while (*s) {
		   result = result << 4;
		   if (c=(*s-'0'),(c>=0 && c <=9)) result|=c;
		   else if (c=(*s-'A'),(c>=0 && c <=5)) result|=(c+10);
		   else if (c=(*s-'a'),(c>=0 && c <=5)) result|=(c+10);
		   else break;
		   ++s;
	  }
	}
	return result;
}


void * memset(void * destination, int32_t c, uint64_t length){
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length){
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0){
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}
	return destination;
}
