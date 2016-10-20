#ifndef songs_h

#define songs_h

typedef struct song_node {
  char name[256];
  char artist[256];
  struct song_node *next;
} song_node;

void lower_string(char s[]);
song_node * insert_front(song_node *front, char nameGiven[], char artistGiven[]);
song_node * insert_song(song_node *front, char nameGiven[], char artistGiven[]);
void print_list(song_node *list);
song_node * first_song_by_name(song_node *front, char nameGiven[]);
song_node * first_song_by_artist(song_node *front, char artistGiven[]);
song_node * random_song(song_node *front);

#endif
