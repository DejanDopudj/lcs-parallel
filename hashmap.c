#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
    char* key;
    int value;
    int isOccupied;  
} KeyValuePair;

typedef struct {
    int size;
    KeyValuePair* table;
} HashMap;

KeyValuePair createKeyValuePair(const char* key, int value) {
    KeyValuePair pair;
    pair.key = strdup(key);
    pair.value = value;
    pair.isOccupied = 1;
    return pair;
}

HashMap* createHashMap(int size) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->size = size;
    map->table = (KeyValuePair*)calloc(size, sizeof(KeyValuePair));
    for (int i = 0; i < size; i++){
        map->table[i].isOccupied = 0;
        map->table[i].key = "-1";
        map->table[i].value = -1;
    }
    return map;
}

int hashFunction(const char* key, int size) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31 + key[i]) % size;
    }
    return hash;
}

KeyValuePair* get_for_insert(HashMap* map,const char* key){
    int index = hashFunction(key, map->size);
    KeyValuePair* kvp = &(map->table[index]);
    int probes = 0;
    while (probes < map->size - 1 && kvp->key != key && kvp->isOccupied == 1){
        probes += 1;
        index += 1;
        kvp = &(map->table[index]);
    }
    if (probes > map->size - 1){
        return NULL;
    }
    return kvp;
}


void insert(HashMap* map, const char* key, int value) {
    int index = hashFunction(key, map->size);

    while (1) {
        KeyValuePair* kvp = get_for_insert(map,key);
        if (kvp == NULL){
            return;
        }
        if ( __sync_val_compare_and_swap(&kvp->key, "-1", key)){
            map->table[index] = createKeyValuePair(key, value);
            return;
        }

        if (index >= map->size - 1){
            break;
        }
        index = (index + 1) % map->size;
    }
}

int get(HashMap* map, const char* key) {
    int index = hashFunction(key, map->size);

    while (map->table[index].isOccupied) {
        if (strcmp(map->table[index].key, key) == 0) {
            return map->table[index].value;
        }
        if (index >= map->size - 1){
            break;
        }
        index = (index + 1) % map->size;
    }

    return -1;
}

void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->size; i++) {
        free(map->table[i].key);
    }
    free(map->table);
    free(map);
}

void printHashMap(HashMap* map) {
    printf("HashMap Contents:\n");

    for (int i = 0; i < map->size; i++) {
        if (map->table[i].isOccupied) {
            printf("Index %d: Key='%s', Value=%d\n", i, map->table[i].key, map->table[i].value);
        } 
    }

    printf("\n");
}

// int main() {
//     HashMap* map = createHashMap(TABLE_SIZE);

//     // Add key-value pairs
//     add(map, "one", 1);
//     add(map, "two", 2);
//     add(map, "three", 3);

//     // Get values using keys
//     printf("Value for key 'one': %d\n", get(map, "one"));
//     printf("Value for key 'two': %d\n", get(map, "two"));
//     printf("Value for key 'three': %d\n", get(map, "three"));
//     printf("Value for key 'four': %d\n", get(map, "four")); // Key not found, will print default value

//     // Free the memory used by the hash map
//     freeHashMap(map);

//     return 0;
// }
