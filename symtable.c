#include "symtable.h"

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    hash %= SYMBOL_TABLE_SIZE;
    return hash;
}

void symtable_insert(char *key, hack_addr addr) {

   Symbol *item =  malloc(sizeof(Symbol));
   item->address = addr;
   item->name = strdup(key);


   int hashIndex = hash(key);

   while((hashArray[hashIndex] != NULL) && (hashArray[hashIndex]->name != NULL)) {
      ++hashIndex;

      hashIndex %= SYMBOL_TABLE_SIZE;
   }

   hashArray[hashIndex] = item;
}


Symbol *symtable_find(char *name) {
   int hashIndex = hash(name);

   while(hashArray[hashIndex] != NULL) {

      if(hashArray[hashIndex]->name == name)
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
