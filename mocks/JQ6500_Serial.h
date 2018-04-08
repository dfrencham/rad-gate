#pragma once
#ifndef JQ6500Serial_h
#define JQ6500Serial_h

#include <Arduino.h>
#include <SoftwareSerial.h>

#define MP3_EQ_NORMAL     0
#define MP3_EQ_POP        1
#define MP3_EQ_ROCK       2
#define MP3_EQ_JAZZ       3
#define MP3_EQ_CLASSIC    4
#define MP3_EQ_BASS       5
#define MP3_SRC_SDCARD    1
#define MP3_SRC_BUILTIN   4
#define MP3_LOOP_ALL      0
#define MP3_LOOP_FOLDER   1
#define MP3_LOOP_ONE      2
#define MP3_LOOP_RAM      3
#define MP3_LOOP_ONE_STOP 4
#define MP3_LOOP_NONE     4 
#define MP3_STATUS_STOPPED 0
#define MP3_STATUS_PLAYING 1
#define MP3_STATUS_PAUSED  2
#define MP3_STATUS_CHECKS_IN_AGREEMENT 4
#define MP3_DEBUG 0

class JQ6500_Serial : public SoftwareSerial
{
  
  public: 
    
    JQ6500_Serial(short rxPin, short txPin) : SoftwareSerial(rxPin,txPin) { };
    // void play(); 
    // void restart();
    // void pause();    
    // void next();  
    // void prev();
    // void nextFolder();
    // void prevFolder();
    void playFileByIndexNumber(unsigned int fileNumber);        
    // void playFileNumberInFolderNumber(unsigned int folderNumber, unsigned int fileNumber);
    // void volumeUp(); 
    // void volumeDn();    
    // void setVolume(byte volumeFrom0To30);
    // void setEqualizer(byte equalizerMode); // EQ_NORMAL to EQ_BASS
    // void setLoopMode(byte loopMode);
    // void setSource(byte source);        // SRC_BUILTIN or SRC_SDCARD       
    // void sleep();    
    // void reset();    
    byte getStatus();    
    // byte getVolume(); 
    // byte getEqualizer();
    // byte getLoopMode();
    // unsigned int   countFiles(byte source);    
    // unsigned int   countFolders(byte source);        
    // unsigned int   currentFileIndexNumber(byte source);
    // unsigned int   currentFilePositionInSeconds();
    // unsigned int   currentFileLengthInSeconds();
    // void           currentFileName(char *buffer, unsigned int bufferLength);    
        
  protected:
    
    // void sendCommand(byte command, byte arg1, byte arg2, char *responseBuffer, unsigned int bufferLength);
    // void sendCommand(byte command);    
    // void sendCommand(byte command, byte arg1);    
    // void sendCommand(byte command, byte arg1, byte arg2);    
    // unsigned int sendCommandWithUnsignedIntResponse(byte command);
    // unsigned int getVersion();
    
    // size_t readBytesUntilAndIncluding(char terminator, char *buffer, size_t length, byte maxOneLineOnly = 0);
    
    // int    waitUntilAvailable(unsigned long maxWaitTime = 1000);
    
};

#endif