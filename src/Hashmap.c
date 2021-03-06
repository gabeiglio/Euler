#include "Hashmap.h"

//the max percentage that the hashmap can be
#define MAX_LOAD_CAPACITY 0.75

void initMap(Hashmap* map) {
    map->count = 0;
    map->capacity = 8;
    
    Entry* tmp = malloc(sizeof(Entry) * map->capacity);
    
    if (!tmp) {
        fprintf(stderr, "[ERROR] Could not initialize map: memory\n");
        exit(1);
    }

    map->entries = tmp;
}

void freeMap(Hashmap* map) {
    map->count = 0;
    map->capacity = 0;
    free(map->entries);
}

//FNV-1a hash algorithm
static uint32_t hash(const char* key) {
    uint32_t hash = 2166136261u;

    for (int i = 0; i < strlen(key); i++) {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }

    return hash;
}

static Entry* findEntry(Hashmap* map, const char* key) {
    uint32_t index = hash(key) % map->capacity;
    
    for (;;) {
        Entry* entry = &map->entries[index];
       
        if (entry->key == NULL) return entry;
        if (strcmp(entry->key, key) == 0) return entry;

        index = (index + 1) % map->capacity;
    }
}

void setEntry(Hashmap* map, const char* key, double value) {
    if (map->count + 1 > map->capacity * MAX_LOAD_CAPACITY) {
        map->capacity *= 2; 
        Entry* tmp = realloc(map->entries, sizeof(Entry) * map->capacity);
        
        if (!tmp) {
            fprintf(stderr, "[ERROR] Could not allocate more memory for map");
            exit(1);
        }
    
        map->entries = tmp;
    }

    Entry* entry = findEntry(map, key);
    bool isNewKey = entry->key == NULL;

    if (isNewKey) map->count++;
    
    entry->key = key;
    entry->value = value;
}

double getEntry(Hashmap* map, const char* key) {
    
    if (map->count == 0) return -1;

    Entry* result = findEntry(map, key);
    if (result->key != NULL) return result->value;
    
    return -1;
}

