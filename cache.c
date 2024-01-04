#include <stdio.h>
#include <string.h>

// THE CACHE
struct LINE{
    char valid;
    int tag;
    char data[32];
};

struct SET{
    struct LINE line[1];
};

struct CACHE {
    struct SET set[8];
} cache;

// GLOBALDATA
// increment these in your function
unsigned hit_count  = 0;
unsigned miss_count = 0;
unsigned read_data_count = 0;

// SYSTEM BUS 
// call Read_Data_From_Ram to update this
char system_bus[32];



// READ DATA FROM RAM
// this function copies 32 character from the text file to
// the system_bus array aligned with the system bus
// (we will not test this with input larger than the text file)
void Read_Data_From_Ram(unsigned address) {
    address >>= 5; address <<= 5; // get align the data
    read_data_count++;
    FILE *file;
    file = fopen("alice_in_wonderland.txt", "r");
    fseek(file, address, SEEK_SET);
    for (int i = 0; i<32; i++) system_bus[i] = fgetc(file);
    return;
}


// COMPLETE THE FOLLOWING FUNCTION 
//
// this code should check to see if the data in the cache is valid and the tag matches
// if so it should return the char matching the address and increment the hit count
//
// if not it should read the data from the system bus copy it into the cache and 
// increment the miss count and return the char matching the address
// 
char Read_Data_From_Cache(unsigned address){
	int tag = (address & ~(address & 255)) >> 8;
	int set = (address >> 5) & 7;
	int bitOffset = address & 31;
	//printf("tag = %d || set = %d || b = %d\t", tag, set, bitOffset);
	
	if (cache.set[set].line[0].valid != 0 && cache.set[set].line[0].tag == tag) {
		hit_count++;
	} else {
		miss_count++;
		Read_Data_From_Ram(address);
		cache.set[set].line[0].valid = 1;//cache.set[set].line[0].data[0];
		cache.set[set].line[0].tag = tag;
		//printf("%s\n", system_bus);
		strncpy(cache.set[set].line[0].data, system_bus, 32);
		//strcpy(cache.set[set].line[0].data, system_bus);
	}

 	return cache.set[set].line[0].data[bitOffset];
}

/* Method used to look inside cache for testing
void printCache() {
	for (int i = 0; i < 8; i++) {
		printf("%d || valid = %c, tag = %d, data = %s ||\n", i, cache.set[i].line[0].valid, cache.set[i].line[0].tag, cache.set[i].line[0].data);
	}
	return;
}
*/

int main() {
    // INITIALIZE CACHE
    for (int i = 0; i<8; i++) cache.set[i].line[0].valid = 0;
    
    // READ SOME DATA
    char c;
    c = Read_Data_From_Cache(0); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(1); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(2); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(3); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(4); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n\n", c, hit_count, miss_count,read_data_count );

    // WRITE A LOT MORE TESTS
	//printCache();
	c = Read_Data_From_Cache(288); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
	c = Read_Data_From_Cache(320); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
	c = Read_Data_From_Cache(352); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
	c = Read_Data_From_Cache(384); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
	c = Read_Data_From_Cache(416); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n\n", c, hit_count, miss_count,read_data_count );
	//printCache();
    	c = Read_Data_From_Cache(256); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
       	c = Read_Data_From_Cache(0); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    	c = Read_Data_From_Cache(256); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    	c = Read_Data_From_Cache(0); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n\n", c, hit_count, miss_count,read_data_count );
    	//printCache();
	c = Read_Data_From_Cache(8000); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    	c = Read_Data_From_Cache(8001); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
	//printCache();

    return 0;
}

