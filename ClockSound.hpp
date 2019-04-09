#ifndef __CLOCK_SOUND_HPP__
#define __CLOCK_SOUND_HPP__

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>


class ClockSound {
  public:
    void begin(int tx, int rx);
    void update_player();
    
    void playLargeFolder(uint8_t folderNumber, uint16_t fileNumber);
    void volume(int volume);
    
    int readFileCountsInFolder(int folder);
    void waitUntilFinished();
    void stop();

  private:
    void printDetail(uint8_t type, int value);

    SoftwareSerial *mySoftwareSerial;
    DFRobotDFPlayerMini mp3player;
};


#endif
