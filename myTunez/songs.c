#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song_node {
  char name[256];
  char artist[256];
  song_node next;
} song_node;

song_node * insert_front(song_node *front, char nameGiven[], char artistGiven[]) {
  song_node *newFront = (song_node*)malloc(sizeof(song_node));
  
  strncpy(song_node->name,nameGiven,256);
  strncpy(song_node->artist,artistGiven,256);
  newFront->next = front;

  return newFront;
}

void insert_song(song_node *front, char nameGiven[], char artistGiven[]) {
  song_node *current = front;

  if (current->next == NULL) {
    song_node *newNode = (song_node*)malloc(sizeof(song_node));
    strncpy(newNode->name,nameGiven,256);
    strncpy(newNode->artist,artistGiven,256);
  } else {
    while (current->next->next != NULL && strcmp(current->next->artist,artistGiven) > 0) {
      current = current->next;
    }
    current = insert_front(current->next,nameGiven,artistGiven);
  }
}

void print_list(song_node *list) {
  printf("%s - %s/n",list->artist,list->name);
  if (list->next != NULL) {
    print_list(list->next);
  }
}

void main() {
  song_node *list;
  list = (song_node*)malloc(sizeof(song_node));
  list->name="Facts";
  list->artist="Kanye West";

  insert_song(list,"Hello","Hello");
  insert_song(list,"ASDF","ASDF");

  print_list(list);
}
