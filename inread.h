#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>

// custom functions
void read_csv();
void read_data();
void add_data();
void update_data();

struct pop_entry {
  int year;
  int population;
  char boro[15];
};
