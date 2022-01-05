#ifndef hashmap_c
#define hashmap_c

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* key;
    double value;
} Entry;

typedef struct {
    int count;
    int capacity;
    Entry* entries;
} Hashmap;

void initMap(Hashmap* map);
void freeMap(Hashmap* map);

void setEntry(Hashmap* map, const char* key, double value);
double getEntry(Hashmap* map, const char* key);

#endif
