#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "list.h"

//ALL LIST FUNCTIONS//
song_node * insert_front_node(song_node *front, song_node *insert) {
  insert->next = front;
  return insert;
}

song_node * insert_node(song_node *prev, song_node *new) {
  song_node *temp = prev->next;
  prev->next = new;
  new->next = temp;
  return prev;
}

void print_list(song_node *list) {
  if (list != NULL && list->artist != NULL && list-> name != NULL) {
    printf("%s - %s\n",list->artist,list->name);
    if (list->next != NULL) {
      print_list(list->next);
    }
  }
}

song_node * first_song_by_name(song_node *front, char nameGiven[]) {
  song_node * current = front;
  
  char nameLower[256];
  strncpy(nameLower,nameGiven,256);
  lower_string(nameLower);

  if (current == NULL) {
    return NULL;
  }
  
  while (current->next != NULL && strcmp(current->name,nameLower) != 0) {
    current = current->next;
  }
  if (strcmp(current->name,nameLower) == 0) {
    return current;
  }
  else {
    return NULL;
  }
}

song_node * first_song_by_artist(song_node *front, char artistGiven[]) {
  song_node * current = front;

  char artistLower[256];
  strncpy(artistLower,artistGiven,256);
  lower_string(artistLower);

  while (current->next != NULL && strcmp(current->artist,artistLower) != 0) {
    current = current->next;
  }
  if (strcmp(current->artist,artistLower) == 0) {
    return current;
  }
  else {
    return NULL;
  }
}

song_node * random_node(song_node *front) {
  int length = 0;
  song_node * current = front;

  while (current != NULL) {
    length++;
    current = current->next;
  }
  
  if (length == 0) {
    return NULL;
  }
  
  srand(time(NULL));
  int chosen = rand() % length;

  current = front;
  while (chosen) {
    current = current->next;    
    chosen--;
  }

  return current;
}


song_node * remove_node(song_node *front, song_node *remove) {
  song_node *current = front;

  if (current == remove) {
    front = front->next;
    return front;
  }
  
  while (current != NULL) {
    if (current->next == remove) {
      current->next = remove->next;
    }
    current = current->next;
  }
  free(remove);
  return front;
}

void free_all(song_node *front) {
  song_node *temp;
  song_node *current = front;
  while (current != NULL) {
    temp = current->next;
    free(current);
    current = 0;
    current = temp;
  }
}

void lower_string(char s[]) {
   int c = 0;
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}

//ALL SONG FUNCTIONS//
song_node * add_song_to_list(song_node *lib, char nameGiven[], char artistGiven[]) {
  char nameLower[256];
  char artistLower[256];
  strncpy(nameLower,nameGiven,256);
  strncpy(artistLower,artistGiven,256);
  lower_string(nameLower);
  lower_string(artistLower);

  song_node *newNode = (song_node*)malloc(sizeof(song_node));
  strncpy(newNode->name,nameLower,256);
  strncpy(newNode->artist,artistLower,256);

  if (lib == NULL) {
    return newNode;
  }
  
  if (strcmp(lib->artist,artistLower) > 0) {
    return insert_front_node(lib,newNode);
  }

  int added = 0;
  song_node *current = lib;
  while (current->next != NULL && added == 0) {
    if (strcmp(current->next->artist,artistLower) > 0) {
      insert_node(current,newNode);
      added = 1;
    }
    current = current->next;
  }
  if (!added) {
    current->next = newNode;
  }
  return lib;
}

void add_song(song_node *table[], char nameGiven[], char artistGiven[]) {
  char nameLower[256];
  char artistLower[256];
  strncpy(nameLower,nameGiven,256);
  strncpy(artistLower,artistGiven,256);
  lower_string(nameLower);
  lower_string(artistLower);

  printf("Adding song %s - %s...\n",artistLower,nameLower);
  
  table[artistLower[0]-97] = add_song_to_list(table[artistLower[0]-97],nameLower,artistLower);
}

song_node * search_for_name(song_node *table[], char nameGiven[]) {
  int i;
  for (i = 0; i < 26; i++) {
    if (first_song_by_name(table[i],nameGiven) != NULL) {
      return first_song_by_name(table[i],nameGiven);
    }
  }
  return NULL;
}

song_node * search_for_artist(song_node *table[], char artistGiven[]) {
  char artistLower[256];
  strncpy(artistLower,artistGiven,256);
  lower_string(artistLower);
  
  return first_song_by_artist(table[artistLower[0]-97],artistLower);
}

void print_all_under_letter(song_node *table[], char letterGiven) {
  int c = letterGiven;
  if (c >= 'A' && c <= 'Z') {
    c += 32;
  }
  printf("Artists starting with %c\n",c);
  if (table[c-97] != NULL) {
    print_list(table[c-97]);
  }
}

void print_all_under_artist(song_node *table[], char artistGiven[]) {
  char artistLower[256];
  strncpy(artistLower,artistGiven,256);
  lower_string(artistLower);

  printf("Songs by %s\n",artistLower);
  
  song_node *current = table[artistLower[0]-97];
  if (current != NULL) {
    while (current->next != NULL) {
      if (strcmp(current->artist,artistLower) == 0) {
	printf("%s - %s\n",current->artist,current->name);
      }
      current = current->next;
    }
    if (strcmp(current->artist,artistLower) == 0) {
      printf("%s - %s\n",current->artist,current->name);
    }
  }
}

void print_library(song_node *table[]) {
  int i;
  for (i = 0; i < 26; i++) {
    print_all_under_letter(table,i+97);
  }
}

void shuffle(song_node *table[]) {
  printf("Shuffling...\n");
  int i;
  for (i = 0; i < 5; i++) {
    srand(time(NULL)*i);
    int chosen = 26;
    while (table[chosen] == NULL || chosen == 26) {
      chosen = rand() % 26;
    }
    song_node *chosenNode = NULL;
    while (chosenNode == NULL) {
      chosenNode = random_node(table[chosen]);
    }
    printf("%s - %s\n",chosenNode->artist,chosenNode->name);
  }
}

void remove_song(song_node *table[], char nameGiven[], char artistGiven[]) {
  char nameLower[256];
  char artistLower[256];
  strncpy(nameLower,nameGiven,256);
  strncpy(artistLower,artistGiven,256);
  lower_string(nameLower);
  lower_string(artistLower);

  printf("Removing %s - %s\n",artistLower,nameLower);
  
  song_node *current = table[artistLower[0]-97];
  while (current != NULL) {
    if (strcmp(current->name,nameLower) == 0 && strcmp(current->artist,artistLower) == 0) {
      current = remove_node(table[artistLower[0]-97],current);
    }
    current = current->next;
  }
}

void delete_all(song_node *table[]) {
  printf("Deleting all songs...\n");
  int i;
  for (int i = 0; i < 26; i++) {
    free_all(table[i]);
    table[i] = 0;
  }
}

int main() {
  //SETUP//
  song_node *table[26];
  int i;
  for (i = 0; i < 26; i++) {
    table[i] = (song_node*)malloc(sizeof(song_node));
    table[i] = 0;
  }

  printf("\n===TESTING add_song===\n");
  add_song(table,"eee","eee");
  add_song(table,"fff","eee");
  add_song(table,"ddd","eee");
  add_song(table,"test","abc");
  add_song(table,"test1","xyz");
  add_song(table,"test2","ebutnoteee");

  printf("\n===TESTING search_for_name===\n");
  printf("Pointer to test2: %p\n",search_for_name(table,"test2"));
  printf("Pointer to ayo: %p\n",search_for_name(table,"ayo"));

  printf("\n===TESTING search_for_artist===\n");
  printf("Pointer to eee: %p\n",search_for_artist(table,"eee"));
  printf("Pointer to ayo: %p\n",search_for_artist(table,"ayo"));

  printf("\n===TESTING print_library===\n");
  print_library(table);

  printf("\n===TESTING print_all_under_artist===\n");
  print_all_under_artist(table,"ccc");
  print_all_under_artist(table,"eee");

  printf("\n===TESTING print_all_under_letter===\n");
  print_all_under_letter(table,'c');
  print_all_under_letter(table,'e');

  printf("\n===TESTING shuffle===\n");
  shuffle(table);

  printf("\n===TESTING remove_song===\n");
  remove_song(table,"eee","eee");
  print_all_under_letter(table,'e');

  printf("\n===TESTING delete_all===\n");
  delete_all(table);
  print_library(table);
  return 0;
}
