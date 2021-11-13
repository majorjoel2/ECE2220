/**
 * Joel Tanner
 * 11-12-2021
 *
 * The goal of this project is read the headers and pixel files of bmp image
 * files and perform edge detection on files.
 */

//Libraries used in this program
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//Struct for the Header
struct tsHeader
{  unsigned short int Type;     /* Magic identifier       */
   unsigned int Size;           /* File size in bytes     */
   unsigned short int Reserved1, Reserved2;
   unsigned int Offset;         /* Offset to data (in B)  */
};

//Struct for the info header
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

//Struct for the Pixels
struct tsPixel{
  unsigned char red, green, blue;
};

//Union for converting short to bytes
union t_uint_16 {
  short int number;
  char bytes[2];
};

//Union for converting int to bytes
union t_uint_32 {
  int number;
  char bytes[4];
};

/**
 * This function will read a short int from the passed in file
 *
 * @param *fileToRead active bmp filepointer
 * @return short int which the function has read
 */
short int readShort(FILE *fileToRead);
/**
 * This function will read an int from the passed in file
 *
 * @param *fileToRead active bmp filepointer
 * @return int which the function has read
 */
int readInt(FILE *fileToRead);
/**
 * This function will reads the header values
 *
 * @param *inFile active bmp filepointer
 * @return struct tsHeader header values read
 */
struct tsHeader readHeader(FILE *inFile);
/**
 * This function will reads the info header values
 *
 * @param *inFile active bmp filepointer
 * @return struct tsInfoHeader info header values read
 */
struct tsInfoHeader readInfoHeader(FILE *inFile);

/**
 * This function will print the current pixel to the output file
 *
 * @note The row and col are just for the print. Function reads next 3 bytes
 * from colorFile
 *
 * @param *colorFile active bmp filepointer
 * @param *printFile active txt filepointer
 * @param row to print to printFile
 * @param col to print to printFile
 * @return 1 on success
 */
int readRGB(FILE *colorFile, FILE *printFile, int row, int col);
/**
 * This function will print the current pixel and return as tsPixel
 *
 * @param *colorFile active bmp filepointer
 * @return tsPixel pixel data in struct form
 */
struct tsPixel structReadRGB(FILE *colorFile);

/**
 * This function will check to see if passed in row and col values are on the
 * edge of the file
 *
 * @param inHead File info header to get Height and Width info
 * @param row to compare if on edge
 * @param col to compare if on edge
 * @return true if edge pixel
 */
int isEdge(struct tsInfoHeader inHead, int row, int col);
/**
 * This function will perform edge detect calculation for one int
 *
 * @param north pixel row + 1
 * @param east pixel col + 1
 * @param south pixel row - 1
 * @param west pixel col - 1
 * @param center current pixel
 * @return edgedetected value
 */
int edgeDetect(int north, int east, int south, int west, int center);

int main(int argc, char *argv[]){
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
      printf("ERROR: Failed to create Output-edge File\n");
      return 1;
    }
  }
  //create and fill header and info header data
  struct tsHeader inputHeader;
  struct tsInfoHeader inputInfoHeader;

  inputHeader = readHeader(inputFile);

  inputInfoHeader = readInfoHeader(inputFile);

  if(strcmp(argv[1], "read") == 0){
    //Print header data to output file
    fprintf(outputFile, "\"%s\"\n", argv[3]);
    union t_uint_16 headerSplit;
    headerSplit.number = inputHeader.Type;
    fprintf(outputFile, "Header.Type = %c\nHeader.Type = %c\n", headerSplit.bytes[0], headerSplit.bytes[1]);
    fprintf(outputFile, "Header.Size = %i\n", inputHeader.Size);
    fprintf(outputFile, "Header.Offset = %i\n", inputHeader.Offset);

    //Print info header data to output file
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

    //Calculate padding and add to output file
    int padding = inputInfoHeader.Width % 4;

    fprintf(outputFile, "Padding = %i\n", padding);

    //rewind input file because header data read makes inputFile not at the start
    rewind(inputFile);
    int i, row, col;
    //add all the individual bytes from the header and infoheader
    for(i = 0; i < inputHeader.Offset; i++){
      fprintf(outputFile, "Byte[%02i] = %03i\n", i, getc(inputFile));
    }

    //Read pixel data and account for padding
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
    //if doing edge detection
    int row, col, i;
    //calculate padding
    int padding = inputInfoHeader.Width % 4;
    struct tsPixel *picture, *outputPicture;
    //allocate memory for 2d pixel arry for input picture and output picture
    picture = (struct tsPixel *)malloc(inputInfoHeader.Height * inputInfoHeader.Width * sizeof(struct tsPixel));
    if(picture == NULL) printf("Failed to allocate memory for pixels\n");
    outputPicture = (struct tsPixel *)malloc(inputInfoHeader.Height * inputInfoHeader.Width * sizeof(struct tsPixel));
    if(outputPicture == NULL) printf("Failed to allocate memory for output picture\n");
    //read the data into the picture 2d array
    for(row = 0; row < inputInfoHeader.Height; row ++){
      for(col = 0; col < inputInfoHeader.Width; col++){
        *(picture + row*inputInfoHeader.Width + col) = structReadRGB(inputFile);
      }
      for(i = 0; i < padding; i++){
        //clear out padding
        getc(inputFile);
      }
    }
    //do Edge Detect
    struct tsPixel tempPixel_N, tempPixel_S, tempPixel_E, tempPixel_W, tempPixel_C, outPixel;
    for(row = 0; row < inputInfoHeader.Height; row ++){
      for(col = 0; col < inputInfoHeader.Width; col++){
        tempPixel_C = *(picture + row*inputInfoHeader.Width + col);
        if(isEdge(inputInfoHeader, row, col)){
          //don't do edge detection if pixel is on the edge
          outPixel = tempPixel_C;
        } else {
          //do edge detection on red, green, and blue parts of the pixel.
          tempPixel_N = *(picture + (row+1)*inputInfoHeader.Width + (col));
          tempPixel_E = *(picture + (row)*inputInfoHeader.Width + (col+1));
          tempPixel_S = *(picture + (row-1)*inputInfoHeader.Width + (col));
          tempPixel_W = *(picture + (row)*inputInfoHeader.Width + (col-1));
          outPixel.red = edgeDetect(tempPixel_N.red, tempPixel_E.red, tempPixel_S.red, tempPixel_W.red, tempPixel_C.red);
          outPixel.green = edgeDetect(tempPixel_N.green, tempPixel_E.green, tempPixel_S.green, tempPixel_W.green, tempPixel_C.green);
          outPixel.blue = edgeDetect(tempPixel_N.blue, tempPixel_E.blue, tempPixel_S.blue, tempPixel_W.blue, tempPixel_C.blue);
        }
        //store in outpicture memory block
        *(outputPicture + row*inputInfoHeader.Width + col) = outPixel;
      }
    }
    //Save to file
    //header
    fwrite(&inputHeader.Type, sizeof(inputHeader.Type), 1, outputFile);
    fwrite(&inputHeader.Size, sizeof(inputHeader.Size), 1, outputFile);
    fwrite(&inputHeader.Reserved1, sizeof(inputHeader.Reserved1), 1, outputFile);
    fwrite(&inputHeader.Reserved2, sizeof(inputHeader.Reserved2), 1, outputFile);
    fwrite(&inputHeader.Offset, sizeof(inputHeader.Offset), 1, outputFile);

    //info header
    fwrite(&inputInfoHeader.Size, sizeof(inputInfoHeader.Size), 1, outputFile);
    fwrite(&inputInfoHeader.Width, sizeof(inputInfoHeader.Width), 1, outputFile);
    fwrite(&inputInfoHeader.Height, sizeof(inputInfoHeader.Height), 1, outputFile);
    fwrite(&inputInfoHeader.Planes, sizeof(inputInfoHeader.Planes), 1, outputFile);
    fwrite(&inputInfoHeader.Bits, sizeof(inputInfoHeader.Bits), 1, outputFile);
    fwrite(&inputInfoHeader.Compression, sizeof(inputInfoHeader.Compression), 1, outputFile);
    fwrite(&inputInfoHeader.ImageSize, sizeof(inputInfoHeader.ImageSize), 1, outputFile);
    fwrite(&inputInfoHeader.xResolution, sizeof(inputInfoHeader.xResolution), 1, outputFile);
    fwrite(&inputInfoHeader.yResolution, sizeof(inputInfoHeader.yResolution), 1, outputFile);
    fwrite(&inputInfoHeader.Colors, sizeof(inputInfoHeader.Colors), 1, outputFile);
    fwrite(&inputInfoHeader.ImportantColors, sizeof(inputInfoHeader.ImportantColors), 1, outputFile);

    //pixel data
    for(row = 0; row < inputInfoHeader.Height; row ++){
      for(col = 0; col < inputInfoHeader.Width; col++){
        outPixel = *(outputPicture + row*inputInfoHeader.Width + col);
        fwrite(&outPixel.blue, sizeof(unsigned char), 1, outputFile);
        fwrite(&outPixel.green, sizeof(unsigned char), 1, outputFile);
        fwrite(&outPixel.red, sizeof(unsigned char), 1, outputFile);
      }
      for(i = 0; i < padding; i++){
        //add in padding
        unsigned char temp = 0;
        fwrite(&temp, sizeof(unsigned char), 1, outputFile);
      }
    }

  } else {
    //if not doing edge or file read report bad command call
    //The function will exit if an input or output file can't be created and
    //will also exit of argv[1] isn't read or edge
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

struct tsPixel structReadRGB(FILE *colorFile){
  struct tsPixel output;
  unsigned int red, green, blue;
  blue = getc(colorFile);
  green = getc(colorFile);
  red = getc(colorFile);
  output.red = (unsigned int)red;
  output.green = (unsigned int)green;
  output.blue = (unsigned int)blue;
  return output;
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

int isEdge(struct tsInfoHeader inHead, int row, int col){
  //check if row or col are at minimum or maximum
  return (row == 0) || (col == 0) || (row+1 == inHead.Height) || (col+1 == inHead.Width);
}

int edgeDetect(int north, int east, int south, int west, int center){
  return (4 * center) + (-1 * north) + (-1 * east) + (-1 * south) + (-1 * west);
}
