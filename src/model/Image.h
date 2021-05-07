//
// Created by otavio on 03/05/2021.
//

#ifndef T3_IMAGE_H
#define T3_IMAGE_H

#include <fstream>

class Image {
public:
    Image(char *ps, int w, int h);

    ~Image();

    static Image *loadImage(const char *filename);

    /* An array of the form (R1, G1, B1, R2, G2, B2, ...) indicating the
		 * color of each pixel in image.  Color components range from 0 to 255.
		 * The array starts the bottom-left pixel, then moves right to the end
		 * of the row, then moves up to the next column, and so on.  This is the
		 * format in which OpenGL likes images.
		 */
    char *pixels;
    int width;
    int height;

private:
    static int toInt(const char *bytes);

    //Converts a two-character array to a short, using little-endian form
    static short toShort(const char *bytes);

    //Reads the next four bytes as an integer, using little-endian form
    static int readInt(std::ifstream &input);

    //Reads the next two bytes as a short, using little-endian form
    static short readShort(std::ifstream &input);
};


#endif //T3_IMAGE_H
