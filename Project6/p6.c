
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

int main(int argc, char *argv[]){
  //
  //open file
  FILE *inputFile = fopen(argv[2], "r");
  if(inputFile == NULL) {
    printf("ERROR: Failed to load Input File\n");
    return 1;
  }
  //create file
  FILE *outputFile = fopen(argv[3], "w");
  if(outputFile == NULL) {
    printf("ERROR: Failed to create Output File\n");
    return 1;
  }
  struct tsHeader inputHeader;
  struct tsInfoHeader inputInfoHeader;

  inputHeader.Type = readShort(inputFile);
  inputHeader.Size = readInt(inputFile);
  inputHeader.Reserved1 = readShort(inputFile);
  inputHeader.Reserved2 = readShort(inputFile);
  inputHeader.Offset = readInt(inputFile);

  inputInfoHeader.Size = readInt(inputFile);
  inputInfoHeader.Width = readInt(inputFile);
  inputInfoHeader.Height = readInt(inputFile);
  inputInfoHeader.Planes = readShort(inputFile);
  inputInfoHeader.Bits = readShort(inputFile);
  inputInfoHeader.Compression = readInt(inputFile);
  inputInfoHeader.ImageSize = readInt(inputFile);
  inputInfoHeader.xResolution = readInt(inputFile);
  inputInfoHeader.yResolution = readInt(inputFile);
  inputInfoHeader.Colors = readInt(inputFile);
  inputInfoHeader.ImportantColors = readInt(inputFile);

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
