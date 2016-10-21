typedef struct song_node {
  char name[256];
  char artist[256];
  struct song_node *next;
} song_node;

void lower_string(char s[]);
song_node * insert_front_node(song_node *front, song_node *insert); 
song_node * insert_node(song_node *prev, song_node *new);
void print_list(song_node *list);
song_node * first_song_by_name(song_node *front, char nameGiven[]);
song_node * first_song_by_artist(song_node *front, char artistGiven[]);
song_node * random_node(song_node *front);
void remove_node(song_node *front, song_node *remove);
void free_all(song_node *front);

song_node * add_song_to_list(song_node *lib, char nameGiven[], char artistGiven[]);
void add_song(song_node *table[], char nameGiven[], char artistGiven[]); 
song_node * search_for_name(song_node *table[], char nameGiven[]);
song_node * search_for_artist(song_node *table[], char artistGiven[]);
void print_all_under_letter(song_node *table[], char letterGiven);
void print_all_under_artist(song_node *table[], char artistGiven[]);
void print_library(song_node *table[]);
void shuffle(song_node *table[]);
void remove_song(song_node *lib, char nameGiven[], char artistGiven[]);
void delete_all(song_node *lib);
