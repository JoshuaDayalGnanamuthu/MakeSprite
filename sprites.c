#include <stdio.h>

typedef enum ERROR_CODES {
  INVALID_FILE_NAME = 1,
  FAILURE_OPENING_FILE
} ERROR_CODES;

int main(int argc, char * argv[]) {

  if (argc != 2) {
    return INVALID_FILE_NAME;
  }
  char * filename = argv[1];

  FILE * fptr = fopen(filename, "rb"); // read-binary, image files usually tend to be binary
  if (fptr == NULL) {
    return FAILURE_OPENING_FILE;
  }


  
  return 0;
}
