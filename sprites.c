#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum ERROR_CODES {
  INVALID_FILE_NAME = 1,
  FAILURE_OPENING_FILE,
  MEMORY_ALLOCATION_ERROR,
  BUFFER_LOADING_ERROR,
  FAILURE_WRITINGTO_FILE
} ERROR_CODES;



/* Function to create a buffer of secified filesize to store the image */
char * imageBuffer(const FILE * file, const size_t fileSize) {
  char * buffer = (char *)(malloc(fileSize)); // 1 char is usually a byte, so you wouldn't havet o multiply by sizeof(char)
  if (buffer == NULL) {
    fclose(file);
    exit(MEMORY_ALLOCATION_ERROR);
  }
  return buffer; // pointer to buffer memory address
}



/* Function to load image file contents unto the buffer */
bool loadImage(char * buffer, size_t elementSize, size_t fileSize, FILE * file) {
  return fread(buffer, elementSize, fileSize, file) == fileSize;
}



/* Dumps buffer contents into a sprite file */
bool dumpSprite(const char * buffer, size_t elementSize, size_t fileSize, FILE * sprite) {
  return fwrite(buffer, elementSize, fileSize, sprite) == fileSize;
}


int main(int argc, char * argv[]) {

  
  if (argc != 3) {
    return INVALID_FILE_NAME;
  }
  char * filename = argv[1];
  char * spritefile = argv[2];

  
  FILE * file = fopen(filename, "rb"); // read-binary, image files usually tend to be binary
  if (file == NULL) {
    return FAILURE_OPENING_FILE;
  }

  FILE * sprite = fopen(spritefile, "wb"); // write-binary
  if (sprite == NULL) {
    return FAILURE_OPENING_FILE;
  }

  
  fseek(file, 0, SEEK_END); // send's the cursor all the way till the end
  const size_t fileSize = ftell(file); // should now be able to tell us file size, by calculating cursor offset
  rewind(file);

  
  char * buffer = imageBuffer(file, fileSize);
  if (!loadImage(buffer, sizeof(char), fileSize, file)) {
      return BUFFER_LOADING_ERROR;
  }

  if (!dumpSprite(buffer, sizeof(char), fileSize, sprite)) {
      return FAILURE_WRITINGTO_FILE;
  }

  
  free(buffer); // deallocate buffer before program 
  fclose((FILE *)file); // cast to FILE * as "rb" returns a const FILE *
  return 0;
}
