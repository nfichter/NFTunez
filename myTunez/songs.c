#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song_node {
  char name[256];
  char artist[256];
  struct song_node *next;
} song_node;

char * lower_string(char s[]) {
   int c = 0;
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
   return s;
}

song_node * insert_front(song_node *front, char nameGiven[], char artistGiven[]) {
  song_node *newFront = (song_node*)malloc(sizeof(song_node));
  
  nameGiven = lower_string(nameGiven);
  artistGiven = lower_string(artistGiven);

  strncpy(newFront->name,nameGiven,256);
  strncpy(newFront->artist,artistGiven,256);
  newFront->next = front;

  return newFront;
}

song_node * insert_song(song_node *front, char nameGiven[], char artistGiven[]) {
  song_node *current = front;

  char nameLower[256];
  strncpy(nameLower,lower_string(nameGiven),256);
  char artistLower[256];
  strncpy(artistLower,lower_string(artistGiven),256);

  song_node *newNode = (song_node*)malloc(sizeof(song_node));
  strncpy(newNode->name,nameLower,256);
  strncpy(newNode->artist,artistLower,256);

  //IF LIST ONLY HAS ONE ELEMENT
  if (current->next == NULL) {
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
      current = insert_front(current->next,nameLower,artistLower);
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

void main() {
  song_node *list;
  list = (song_node*)malloc(sizeof(song_node));
  strcpy(list->name,"fdsa");
  strcpy(list->artist,"fdsa");

  list = insert_song(list,"ello","ello");
  print_list(list);

  list = insert_song(list,"ASDF","ASDF");
  print_list(list);
}
