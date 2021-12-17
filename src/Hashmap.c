#include "Hashmap.h"

//the max percentage that the hashmap can be
#define MAX_LOAD_CAPACITY 0.75

void initMap(Hashmap* map) {
    map->count = 0;
    map->capacity = 0;
    map->entries = NULL;
}

void freeMap(Hashmap* map) {

}

static uint32_t hash(const char* key) {

}

static Entry* findEntry(Entry* entries, const char* key) {

}

void setEntry(Hashmap* map, Entry* entry) {
    
}

int getEntry(Hashmap* map, const char* key) {

}
