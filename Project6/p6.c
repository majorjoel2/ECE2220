
//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct tsHeader
{  unsigned short int Type;     /* Magic identifier       */
   unsigned int Size;           /* File size in bytes     */
   unsigned short int Reserved1, Reserved2;
   unsigned int Offset;         /* Offset to data (in B)  */
};

struct tsInfoHeader
{  unsigned int Size;           /* Header size in bytes    */
   int Width, Height;           /* Width / Height of image */
   unsigned short int Planes;   /* Number of colour planes */
   unsigned short int Bits;     /* Bits per pixel          */
   unsigned int Compression;    /* Compression type        */
   unsigned int ImageSize;      /* Image size in bytes     */
   int xResolution, yResolution;/* Pixels per meter        */
   unsigned int Colors;         /* Number of colors        */
   unsigned int ImportantColors;/* Important colors        */
};

union t_uint_16 {
  short int number;
  char bytes[2];
};

union t_uint_32 {
  int number;
  char bytes[4];
};

short int readShort(FILE *fileToRead);
int readInt(FILE *fileToRead);
struct tsHeader readHeader(FILE *inFile);
struct tsInfoHeader readInfoHeader(FILE *inFile);

int readRGB(FILE *colorFile, FILE *printFile, int row, int col);

int main(int argc, char *argv[]){
  //
  //open file
  FILE *inputFile = fopen(argv[2], "r");
  if(inputFile == NULL) {
    printf("ERROR: Failed to load Input File\n");
    return 1;
  }
  FILE *outputFile;
  if(strcmp(argv[1], "read") == 0){
    //create file
    outputFile = fopen(argv[3], "w");
    if(outputFile == NULL) {
      printf("ERROR: Failed to create Output File\n");
      return 1;
    }
  }
  if(strcmp(argv[1], "edge") == 0){
    //create file-edge
    char *subString;
    int lenOfFile = strlen(argv[2]);
    subString = (char *)malloc((lenOfFile+5)*sizeof(char));
    memcpy(subString, (argv[2]), (lenOfFile-4));
    strcat(subString, "-edge.bmp");
    outputFile = fopen(subString, "w");
    if(outputFile == NULL) {
      printf("ERROR: Failed to create Output File\n");
      return 1;
    }
  }
  struct tsHeader inputHeader;
  struct tsInfoHeader inputInfoHeader;

  inputHeader = readHeader(inputFile);

  inputInfoHeader = readInfoHeader(inputFile);

  if(strcmp(argv[1], "read") == 0){
    fprintf(outputFile, "\"%s\"\n", argv[3]);
    union t_uint_16 headerSplit;
    headerSplit.number = inputHeader.Type;
    fprintf(outputFile, "Header.Type = %c\nHeader.Type = %c\n", headerSplit.bytes[0], headerSplit.bytes[1]);
    fprintf(outputFile, "Header.Size = %i\n", inputHeader.Size);
    fprintf(outputFile, "Header.Offset = %i\n", inputHeader.Offset);

    fprintf(outputFile, "InfoHeader.Size = %i\n", inputInfoHeader.Size);
    fprintf(outputFile, "InfoHeader.Width = %i\n", inputInfoHeader.Width);
    fprintf(outputFile, "InfoHeader.Height = %i\n", inputInfoHeader.Height);
    fprintf(outputFile, "InfoHeader.Planes = %i\n", inputInfoHeader.Planes);
    fprintf(outputFile, "InfoHeader.Bits = %i\n", inputInfoHeader.Bits);
    fprintf(outputFile, "InfoHeader.Compression = %i\n", inputInfoHeader.Compression);
    fprintf(outputFile, "InfoHeader.ImageSize = %i\n", inputInfoHeader.ImageSize);
    fprintf(outputFile, "InfoHeader.xResolution = %i\n", inputInfoHeader.xResolution);
    fprintf(outputFile, "InfoHeader.yResolution = %i\n", inputInfoHeader.yResolution);
    fprintf(outputFile, "InfoHeader.Colors = %i\n", inputInfoHeader.Colors);
    fprintf(outputFile, "InfoHeader.ImportantColors = %i\n", inputInfoHeader.ImportantColors);

    int padding = inputInfoHeader.Width % 4;

    fprintf(outputFile, "Padding = %i\n", padding);

    rewind(inputFile);
    int i, row, col;
    for(i = 0; i < inputHeader.Offset; i++){
      fprintf(outputFile, "Byte[%02i] = %03i\n", i, getc(inputFile));
    }

    for(row = 0; row < inputInfoHeader.Height; row++){
      for(col = 0; col < inputInfoHeader.Width; col++){
        //rgb
        readRGB(inputFile, outputFile, row, col);
      }
      //padding
      for(i = 0; i < padding; i++){
        fprintf(outputFile, "Padding[%02i] = %03i\n", i, getc(inputFile));
      }
    }
  } else if(strcmp(argv[1], "edge") == 0){
    //printf("edge\n");
  } else {
    printf("Bad command input\nCommand: [exe] [read/edge] [input file] [output file (read)]\n");
    fclose(inputFile);
    fclose(outputFile);
    return 1;
  }

  fclose(inputFile);
  fclose(outputFile);
  return 0;
}

short int readShort(FILE *fileToRead){
  union t_uint_16 output;
  output.bytes[0] = getc(fileToRead);
  output.bytes[1] = getc(fileToRead);
  return output.number;
}

int readInt(FILE *fileToRead){
  union t_uint_32 output;
  output.bytes[0] = getc(fileToRead);
  output.bytes[1] = getc(fileToRead);
  output.bytes[2] = getc(fileToRead);
  output.bytes[3] = getc(fileToRead);
  return output.number;
}

int readRGB(FILE *colorFile, FILE *printFile, int row, int col){
  unsigned int red, green, blue;
  blue = getc(colorFile);
  green = getc(colorFile);
  red = getc(colorFile);
  fprintf(printFile, "RGB[%02i,%02i] = %03u.%03u.%03u\n", row, col, red, green, blue);
  return 1;
}

struct tsHeader readHeader(FILE *inFile){
  struct tsHeader output;
  output.Type = readShort(inFile);
  output.Size = readInt(inFile);
  output.Reserved1 = readShort(inFile);
  output.Reserved2 = readShort(inFile);
  output.Offset = readInt(inFile);
  return output;
}

struct tsInfoHeader readInfoHeader(FILE *inFile){
  struct tsInfoHeader output;
  output.Size = readInt(inFile);
  output.Width = readInt(inFile);
  output.Height = readInt(inFile);
  output.Planes = readShort(inFile);
  output.Bits = readShort(inFile);
  output.Compression = readInt(inFile);
  output.ImageSize = readInt(inFile);
  output.xResolution = readInt(inFile);
  output.yResolution = readInt(inFile);
  output.Colors = readInt(inFile);
  output.ImportantColors = readInt(inFile);
  return output;
}
