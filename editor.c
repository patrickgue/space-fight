#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "editor.h"


void save(int *image, int width, int height) {
  char *header="char **image ={";
  FILE* save_file;
  size_t string_size = sizeof(header)
    + (sizeof(char) * width * height * 4) /* max 3 numbers and comma */
    + (sizeof(char) * height * 3) /* brackets and newline */
    + (sizeof(char) * 2) /* ending bracket and \0 character */;
  char *string = (char*)malloc(string_size);
  int x_index, y_index;
  char *filename = (char*)malloc(64 * sizeof(char)); /* 64 bytes quite random. TODO: change if memory gets sparse */
  printf("initialised (%ib)\n", string_size);
  
  strcpy(string, header);
  for(y_index = 0; y_index < height; y_index++) {
    strcat(string, "{");
    for(x_index = 0; x_index < width; x_index++) {
      sprintf(string, "%s%i", string,
	      *((image+x_index*height) + y_index ) );
      if(x_index < width -1) {
	strcat(string,",");
      }
    }
    strcat(string, "}\n");
    printf("line %i composed\n", y_index);
  }

  printf("image created\nFilename: ");
  scanf("%s", filename);

  save_file = fopen(filename, "w");
  fwrite(string, 1, strlen(string), save_file);
  fclose(save_file);

  free(string);
  free(filename);

}
