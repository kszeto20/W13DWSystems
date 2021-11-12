#include "inread.h"

void read_csv() {
  // data from input
  printf("Reading 'nyc_pop.csv'... \n");
  int in = open("./nyc_pop.csv", O_RDONLY);
  if (errno != 0) {
    printf("An error has occured \n%s", strerror(errno));
    return;
  }

  // file to output
  int out = open("./nyc_pop.data", O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if (errno != 0) {
    printf("An error has occured \n%s", strerror(errno));
    return;
  }

  // getting data metadata
  struct stat fileD;
  // stat gets info about nyc_pop and writes into where fileD points to
  stat("./nyc_pop.csv", &fileD);
  if (errno != 0) {
    printf("An error has occured \n%s", strerror(errno));
    return;
  }
  int fileSize = fileD.st_size;

  // make char of the size
  char *all = malloc(fileSize);
  // all is to manipulate
  read(in, all, fileSize);
  if (errno != 0) {
    printf("An error has occured \n%s", strerror(errno));
    return;
  }

  int lines = 0;
  int i;
  for (i = 0; i < fileSize; i++) {
    if (all[i] == '\n') {
      lines++;
    }
  }

  // mem for all: x years, 5 boroughs per lines, 1 struct per borough
  long totalMem = (lines - 1) * 5 * sizeof(struct pop_entry);

  struct pop_entry *bunch = malloc(totalMem);
  char *noFirst = strchr(all + 1, '\n');

  int bCount = 0;
  for (i = 0; i < lines - 1; i++) {
    // assign pops
    int year;
    sscanf(noFirst + 1, "%d,%d,%d,%d,%d,%d\n", &year,
          &(bunch[bCount].population), &(bunch[bCount + 1].population),
          &(bunch[bCount + 2].population), &(bunch[bCount + 3].population),
          &(bunch[bCount + 4].population));
    // assign boroughs
    strcpy(bunch[bCount].boro, "Manhattan");
    strcpy(bunch[bCount + 1].boro, "Brooklyn");
    strcpy(bunch[bCount + 2].boro, "Queens");
    strcpy(bunch[bCount + 3].boro, "Bronx");
    strcpy(bunch[bCount + 4].boro, "Staten Island");
    // all years the same for the group of five
    for (int y = 0; y < 5; y++) {
      bunch[bCount + y].year = year;
    }

    bCount += 5;
    noFirst = strchr(noFirst + 1, '\n');
  }

  int written = write(out, bunch, totalMem);
  printf("Wrote %d bytes into nyc_pop.data\n", written);
}

void read_data() {
    int data = open("./nyc_pop.data", O_RDONLY);
    if (errno != 0) {
      printf("An error has occured \n%s", strerror(errno));
      return;
    }

    struct stat fileD;
    stat("./nyc_pop.data", &fileD);
    if (errno != 0) {
      printf("An error has occured \n%s", strerror(errno));
      return;
    }
    int fileSize = fileD.st_size;

    struct pop_entry *all = malloc(fileSize);

    read(data, all, fileSize);
    if (errno != 0) {
      printf("An error has occured \n%s", strerror(errno));
      return;
    }

    int i;
    for (i = 0; i * sizeof(struct pop_entry) < fileSize; i++) {
        printf("%d: Year: %d\tBorough: %s\tPopulation: %d\n", i, all[i].year, all[i].boro, all[i].population);
    }
}

void add_data () {

  char *info;
  printf("Format for adding data --> Year,Population,Borough\nPlease enter data to add: \n");

  // grab the file name
  scanf("%ms", &info);

  struct pop_entry toAdd;
  sscanf(info, "%d,%d,%s\n", &toAdd.year, &toAdd.population, toAdd.boro);

  int writing = open("./nyc_pop.data", O_WRONLY | O_APPEND);
  if (errno != 0) {
    printf("An error has occured \n%s", strerror(errno));
    return;
  }
  write(writing, &toAdd, sizeof(struct pop_entry));
  if (errno != 0) {
    printf("An error has occured \n%s", strerror(errno));
    return;
  }
  printf("Appended data to file: Year: %d \t Boro: %s \t Population: %d\n", toAdd.year, toAdd.boro, toAdd.population);
}

void update_data() {
  read_data();

  //rdwr allow writing on an existing file
  int file = open("./nyc_pop.data", O_RDWR);
  if (errno != 0) {
    printf("An error has occured \n%s", strerror(errno));
    return;
  }

  struct stat fileD;
  stat("./nyc_pop.data", &fileD);
  if (errno != 0) {
    printf("An error has occured \n%s", strerror(errno));
    return;
  }

  char *info;
  printf("Entry to update: \n");
  // grab the num
  scanf("%ms", &info);
  if (errno != 0) {
    printf("An error has occured \n%s", strerror(errno));
    return;
  }

  int num = atoi(info);

  printf("Format for adding data --> Year,Population,Borough\nPlease enter data to add: \n");

  // grab the file name
  scanf("%ms", &info);

  struct pop_entry toAdd;
  sscanf(info, "%d,%d,%s\n", &toAdd.year, &toAdd.population, toAdd.boro);

  lseek(file, num * sizeof(struct pop_entry), SEEK_SET);
  write(file, &toAdd, sizeof(struct pop_entry));
  if (errno != 0) {
      printf("Error: %s\n", strerror(errno));
      return;
  }
  printf("File updated.\n");
}
