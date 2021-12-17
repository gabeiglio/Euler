#ifndef hashmap_c
#define hashmap_c

typedef struct {
    const char* key;
    int value;
} Entry;

typedef struct {
    int count;
    int capacity;
    Entry* entries;
} Hashmap;

void initMap(Hashmap* map);
void freeMap(Hashmap* map);

void setEntry(Hashmap* map, Entry* entry);
int getEntry(Hashmap* map, const char* key);

#endif
