#include <stdio.h>
#include "inread.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Please call with make --> read_csv, read_data, add_data, update_data\nFor example: make read_csv or make add_data\n");
    return -1;
  }
  else if (strcmp(argv[1], "-read_csv") == 0) {
    read_csv();
  }
  else if (strcmp(argv[1], "-read_data") == 0) {
    read_data();
  }
  else if (strcmp(argv[1], "-add_data") == 0) {
    add_data();
  }
  else if (strcmp(argv[1], "-update_data") == 0) {
    update_data();
  }
  else {
    printf("Invalid request.\n Please choose a function --> -read_csv, -read_data, -add_data, -update_data\n");
    return -1;
  }
}
