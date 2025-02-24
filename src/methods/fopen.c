#include "../headers/hello.h"

#define err stderr
#define out stdout
#define in stdin
void openFiles(struct openFile *of) {
  of->file = fopen(of->filename, "a+");
  if (of->file == NULL) {
    printf("Error: Could not open file %s\n", of->filename);
  } else {
    printf("File %s opened successfully\n", of->filename);
  }
}
void inputFile(struct openFile *of) {
  int result = fputc(98, of->file);
  if (result == EOF) {
    printf("Error: Could not write to file\n");
  } else {
    printf("File written to successfully\n");
  }
}

void closeFile(struct openFile *of) {
  int result = fclose(of->file);
  if (result == EOF) {
    printf("Error: Could not close file\n");
  } else {
    printf("File %s closed successfully\n", of->filename);
  }
}

void inputFileS(struct openFile *of) {
  int result = fputs("Hello, Word! \n", of->file);
  if (result == EOF) {
    printf("Error: Could not write to file\n");
  } else {
    printf("File %s written to successfully\n", of->filename);
  }
}

void inputLongContent(struct openFile *of) {
  char *name = "Lawrence Cheng";
  int result = fprintf(
      of->file, "This is for testing fprintf function what can it work by %s",
      name);
  if (result == EOF) {
    printf("Error: Could not write to file\n");
  } else {
    printf("File %d written to successfully \n", result);
  }
}

void getFileContentC(struct openFile *of) {
  int result = fgetc(of->file);
  while (result != EOF) {
    printf("%c", result);
    result = fgetc(of->file);
  }
  printf("\n");
}

void getFileContentS(struct openFile *of) {
  char buffer[255];
  while (fgets(buffer, sizeof(buffer), of->file)) {
    printf("%s", buffer);
  }
}

void fscanfFile(struct openFile *of) {
  char buffer[255];
  int age;
  char wife[255];

  while (fscanf(of->file, "%s %d %s", buffer, &age, wife) != EOF) {
    printf("Name: %s, Age: %d, Wife: %s\n", buffer, age, wife);
  }
}

void stdinOutErr(struct openFile *of) {
  char *ch = malloc(100);
  fgets(ch, 100, in);
  printf("You entered: %s\n", ch);
  fputs(ch, out);
  printf("\n");
}
