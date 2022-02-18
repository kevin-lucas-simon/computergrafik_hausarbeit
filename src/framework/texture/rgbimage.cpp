#include "rgbimage.h"
#include "color.h"
#include "assert.h"
#include <fstream>
#include <stdio.h>
#include <math.h>

//  Erzeugt bei der Konstruktion einen 2D-Bildspeicher mit der Auflösung Width*Height Pixeln
RGBImage::RGBImage( unsigned int Width, unsigned int Height)
{
    m_Width = Width;
    m_Height = Height;
    m_Image = new Color[m_Width * m_Height];
}

// Freigabe des Bildspeichers
RGBImage::~RGBImage()
{
    delete [] m_Image;
}

// Setzen einer Pixelfarbe an der Stelle x, y
void RGBImage::setPixelColor( unsigned int x, unsigned int y, const Color& c)
{
    if(x < width() && y < height())
        m_Image[x + m_Width*y] = c;
}

// Lesen einer Pixelfarbe an der Stelle x, y
const Color& RGBImage::getPixelColor( unsigned int x, unsigned int y) const
{
    if(x < width() && y < height())
        return m_Image[x + m_Width*y];
}

// Gibt die Breite des 2d-Speichers aus
unsigned int RGBImage::width() const
{
    return m_Width;
}

// Gibt die Höhe des 2d-Speichers aus
unsigned int RGBImage::height() const
{
    return m_Height;
}

// Konvertiert einen Float-Farbkanal (R, G oder B) in einen Byte-Wert
unsigned char RGBImage::convertColorChannel( float v)
{
    if(v < 0.0)
        return 0;
    else if(v > 1.0)
        return 255;
    else
        return 255*v;
}

// Kantenerkennung auf Bildern
RGBImage& RGBImage::SobelFilter(RGBImage &destination, const RGBImage &source, float factor) {
    // Durch alle Pixel iterieren
    for (int x = 1; x < source.width()-1; ++x) {
        for (int y = 1; y < source.height()-1; ++y) {
            // Kante auf x-Achse berechnen
            float xEdge =
                    source.getPixelColor(x-1, y-1).monochrome() + 2*source.getPixelColor(x-1,y).monochrome()
                    + source.getPixelColor(x-1,y+1).monochrome() - source.getPixelColor(x+1,y-1).monochrome()
                    - 2*source.getPixelColor(x+1,y).monochrome() - source.getPixelColor(x+1,y+1).monochrome();
            // Kante auf y-Achse berechnen
            float yEdge =
                    source.getPixelColor(x-1, y-1).monochrome() + 2*source.getPixelColor(x,y-1).monochrome()
                    + source.getPixelColor(x+1,y-1).monochrome() - source.getPixelColor(x-1,y+1).monochrome()
                    - 2*source.getPixelColor(x,y+1).monochrome() - source.getPixelColor(x+1,y+1).monochrome();
            // Ergebnis durch Überblendung der Kanten
            float edge = sqrt(pow(xEdge,2)+ pow(yEdge,2)) * factor;
            destination.setPixelColor(x,y, Color(edge, edge, edge));
        }
    }
    return destination;
}

// Speichert das Bild als 24Bit-RGB-Bitmap-Datei (BMP)
// Quelle: https://stackoverflow.com/Questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
bool RGBImage::saveToDisk( const char* Filename)
{
    // Header und Data Definition
    unsigned int headers[13];
    FILE* pBitmap;
    int extrabytes = (4-((m_Width*3)%4))%4;
    int paddedsize = ((m_Width*3)+extrabytes)*m_Height;

    headers[0]  = paddedsize + 54;
    headers[1]  = 0;
    headers[2]  = 54;
    headers[3]  = 40;
    headers[4]  = m_Width;
    headers[5]  = m_Height;
    headers[7]  = 0;
    headers[8]  = paddedsize;
    headers[9]  = 0;
    headers[10] = 0;
    headers[11] = 0;
    headers[12] = 0;

    // In neue BMP-Datei schreiben
    pBitmap = fopen(Filename,"wb");
    if(pBitmap!= NULL){
        fputs("BM", pBitmap);
        for (int n = 0; n <= 5; n++)
        {
            fprintf(pBitmap, "%c", headers[n] & 0x000000FF);
            fprintf(pBitmap, "%c", (headers[n] & 0x0000FF00) >> 8);
            fprintf(pBitmap, "%c", (headers[n] & 0x00FF0000) >> 16);
            fprintf(pBitmap, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
        }
        fprintf(pBitmap, "%c", 1);
        fprintf(pBitmap, "%c", 0);
        fprintf(pBitmap, "%c", 24);
        fprintf(pBitmap, "%c", 0);
        for (int n = 7; n <= 12; n++)
        {
            fprintf(pBitmap, "%c", headers[n] & 0x000000FF);
            fprintf(pBitmap, "%c", (headers[n] & 0x0000FF00) >> 8);
            fprintf(pBitmap, "%c", (headers[n] & 0x00FF0000) >> 16);
            fprintf(pBitmap, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
        }

        // Bildinformationen in RGB-Farbwerten
        for (int y = m_Height - 1; y >= 0; y--){
            for (int x = 0; x <= m_Width - 1; x++){
                Color temp = getPixelColor(x, y);
                fprintf(pBitmap, "%c", convertColorChannel(temp.B));
                fprintf(pBitmap, "%c", convertColorChannel(temp.G));
                fprintf(pBitmap, "%c", convertColorChannel(temp.R));
            }
            if (extrabytes)
            {
                for (int n = 1; n <= extrabytes; n++)
                {
                    fprintf(pBitmap, "%c", 0);
                }
            }
        }

        fclose(pBitmap);
        return true;
    }
    return false;
}