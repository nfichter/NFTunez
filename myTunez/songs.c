#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "songs.h"

void lower_string(char s[]) {
   int c = 0;
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}

song_node * insert_front(song_node *front, char nameGiven[], char artistGiven[]) {
  song_node *newFront = (song_node*)malloc(sizeof(song_node));
  
  char nameLower[256];
  char artistLower[256];
  strncpy(nameLower,nameGiven,256);
  strncpy(artistLower,artistGiven,256);
  lower_string(nameLower);
  lower_string(artistLower);

  strncpy(newFront->name,nameLower,256);
  strncpy(newFront->artist,artistLower,256);
  newFront->next = front;

  return newFront;
}

song_node * insert_song(song_node *front, char nameGiven[], char artistGiven[]) {
  song_node *current = front;

  char nameLower[256];
  char artistLower[256];
  strncpy(nameLower,nameGiven,256);
  strncpy(artistLower,artistGiven,256);
  lower_string(nameLower);
  lower_string(artistLower);

  //IF LIST ONLY HAS ONE ELEMENT
  if (current->next == NULL) {
    song_node *newNode = (song_node*)malloc(sizeof(song_node));
    
    strncpy(newNode->name,nameLower,256);
    strncpy(newNode->artist,artistLower,256);

    if (strcmp(current->artist,newNode->artist) < 0) {
      current->next = newNode;
    } else {
      current = insert_front(current,newNode->name,newNode->artist);
    }
  }
  else {
    if (strcmp(current->next->artist,artistLower) < 0) {
      current = insert_song(current->next,nameLower,artistLower);
    }
    else {
      current = insert_front(current,nameLower,artistLower);
    }
  }

  return current;
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

song_node * random_song(song_node *front) {
  int length = 0;
  song_node * current = front;

  while (current != NULL) {
    length++;
    current = current->next;
  }
}

int main() {
  song_node *list;
  list = (song_node*)malloc(sizeof(song_node));
  strcpy(list->name,"fdsa");
  strcpy(list->artist,"fdsa");

  list = insert_song(list,"ello","ello");
  print_list(list);
  
  printf("\n");

  list = insert_song(list,"ASDF","ASDF");
  print_list(list);

  song_node *find_ello = first_song_by_name(list,"ello");
  printf("find_ello name: %s\n",find_ello->name);

  song_node *find_fdsa = first_song_by_artist(list,"fdsa");
  printf("find_fdsa artist: %s\n",find_fdsa->artist);

  return 0;
}
