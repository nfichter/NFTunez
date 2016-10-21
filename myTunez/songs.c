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
}

void print_list(song_node *list) {
  printf("%s - %s\n",list->artist,list->name);
  if (list->next != NULL) {
    print_list(list->next);
  }
}

song_node * first_song_by_name(song_node *front, char nameGiven[]) {
  song_node * current = front;
  
  char nameLower[256];
  strncpy(nameLower,nameGiven,256);
  lower_string(nameLower);

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

  srand(time(NULL));
  int chosen = rand() % length;

  current = front;
  while (chosen) {
    current = current->next;    
    chosen--;
  }

  return current;
}


void remove_node(song_node *front, song_node *remove) {
  song_node *current = front;

  while (current != NULL) {
    if (current->next == remove) {
      current->next = remove->next;
    }
  }
  free(remove);
}

void free_all(song_node *front) {
  while (front != NULL) {
    free(front);
    front = front->next;
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
song_node * add_song(song_node *lib, char nameGiven[], char artistGiven[]) {
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
    return lib;
  }
  
  if (strcmp(lib->artist,artistGiven) < 0) {
    return insert_front_node(lib,newNode);
  }

  int added = 0;
  song_node *current = lib;
  while (current->next != NULL && added == 0) {
    if (strcmp(current->next->artist,artistGiven) < 0) {
      return insert_node(current,newNode);
      added = 1;
    }
    current = current->next;
  }
}

int main() {
  song_node *lib = (song_node*)malloc(sizeof(song_node));
  lib = 0;
  lib = add_song(lib,"eee","eee");
  print_list(lib);
  lib = add_song(lib,"ddd","ddd");
  print_list(lib);
  lib = add_song(lib,"fff","fff");
  print_list(lib);

  return 0;
}
