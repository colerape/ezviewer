/**************************************************************************
  exif.h  -- A simple ISO C++ library to parse basic EXIF 
             information from a JPEG file.

  Based on the description of the EXIF file format at:
  -- http://park2.wakwak.com/~tsuruzoh/Computer/Digicams/exif-e.html
  -- http://www.media.mit.edu/pia/Research/deepview/exif.html
  -- http://www.exif.org/Exif2-2.PDF

  Copyright (c) 2010-2013 Mayank Lahiri
  mlahiri@gmail.com
  All rights reserved.

  VERSION HISTORY:
  2.0: Released February 2013
  1.0: Released 2010
  
  Redistribution and use in source and binary forms, with or without 
  modification, are permitted provided that the following conditions are met:

  -- Redistributions of source code must retain the above copyright notice, 
     this list of conditions and the following disclaimer.
  -- Redistributions in binary form must reproduce the above copyright notice, 
     this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY EXPRESS 
   OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN 
   NO EVENT SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
   OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __EXIF_H
#define __EXIF_H

#include <string>

// 
// Class responsible for storing and parsing EXIF information from a JPEG blob
//
class EXIFInfo {
 public:
  // RETURN:  0 on succes with 'result' filled out
  //          error code otherwise, as defined by the PARSE_EXIF_ERROR_* macros
  int parseFrom(const unsigned char *data, unsigned length);
  int parseFrom(const std::string &data);
  void clear();

  // Data fields filled out by parseFrom()
  char ByteAlign;                   // 0 = Motorola byte alignment, 1 = Intel 
  std::string ImageDescription;     // Image description
  std::string Make;                 // Camera manufacturer's name
  std::string Model;                // Camera model
  unsigned short Orientation;       // Image orientation, start of data corresponds to
                                    // 0: unspecified in EXIF data
                                    // 1: upper left of image
                                    // 3: lower right of image
                                    // 6: upper right of image
                                    // 8: lower left of image
                                    // 9: undefined
  unsigned short BitsPerSample;     // Number of bits per component
  std::string Software;             // Software used
  std::string DateTime;             // File change date and time
  std::string DateTimeOriginal;     // Original file date and time (may not exist)
  std::string DateTimeDigitized;    // Digitization date and time (may not exist)
  std::string SubSecTimeOriginal;   // Sub-second time that original picture was taken
  std::string Copyright;            // File copyright information
  double ExposureTime;              // Exposure time in seconds
  double FNumber;                   // F/stop
  unsigned short ISOSpeedRatings;   // ISO speed
  double ShutterSpeedValue;         // Shutter speed (reciprocal of exposure time)
  double ExposureBiasValue;         // Exposure bias value in EV
  unsigned short ExposureProgram;   // Exposure program
  unsigned short Whitebalance;      // White balance
  double SubjectDistance;           // Distance to focus point in meters
  double FocalLength;               // Focal length of lens in millimeters
  unsigned short FocalLengthIn35mm; // Focal length in 35mm film
//  char Flash;                       // 0 = no flash, 1 = flash used
  unsigned short Flash;             // 0 = no flash, others = flash used
  unsigned short MeteringMode;      // Metering mode
                                    // 1: average
                                    // 2: center weighted average
                                    // 3: spot
                                    // 4: multi-spot
                                    // 5: multi-segment
                                    // 6: partial
                                    // 255: other
  unsigned short LightSource;       // Light source
  unsigned ImageWidth;              // Image width reported in EXIF data
  unsigned ImageHeight;             // Image height reported in EXIF data
  struct Geolocation_t {            // GPS information embedded in file
    double Latitude;                  // Image latitude expressed as decimal
    double Longitude;                 // Image longitude expressed as decimal
    struct Coord_t {
      double degrees;               
      double minutes;
      double seconds;
      char direction;
    } LatComponents, LonComponents;   // Latitude, Longitude expressed in deg/min/sec 
    double Altitude;                  // Altitude in meters, relative to sea level
    char AltitudeRef;                 // 0 = above sea level, -1 = below sea level
  } GeoLocation;

  EXIFInfo() {
    clear();
  }
};

// No EXIF header found in JPEG file.
#define PARSE_EXIF_ERROR_NO_EXIF              1983
// Byte alignment specified in EXIF file was unknown (not Motorola or Intel).
#define PARSE_EXIF_ERROR_UNKNOWN_BYTEALIGN    1984
// EXIF header was found, but data was corrupted.
#define PARSE_EXIF_ERROR_CORRUPT              1985

#endif
