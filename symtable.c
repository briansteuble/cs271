#include "symtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return (int)(hash % SYMBOL_TABLE_SIZE);
}

void symtable_insert(char *key, hack_addr addr) {
    struct Symbol *item = (struct Symbol *)malloc(sizeof(struct Symbol));
    item->name = strdup(key);
    item->addr = addr;

    int index = hash(key);
    while (hashArray[index] != NULL) {
        index = (index + 1) % SYMBOL_TABLE_SIZE;
    }
    hashArray[index] = item;
}


Symbol *symtable_find(char *name) {
   int hashIndex = hash(name);

   while(hashArray[hashIndex] != NULL) {

      if(strcmp(hashArray[hashIndex]->name, name) ==0)
         return hashArray[hashIndex];

      ++hashIndex;

      hashIndex %= SYMBOL_TABLE_SIZE;
   }

   return NULL;
}


void symtable_display_table() {
   int i = 0;

   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {

      if(hashArray[i] != NULL)
         printf(" (%s,%d)",hashArray[i]->name,hashArray[i]->address);
      else
         printf(" ~~ ");
   }

   printf("\n");
}

void symtable_print_labels() {
   int i = 0;
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->address);

        }

   }
}
