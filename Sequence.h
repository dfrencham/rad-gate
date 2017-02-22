/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include "Gate.h"
#include "LightTree.h"
#include "AudioFX.h"

#ifndef _SEQUENCE_H
#define _SEQUENCE_H

class Sequence {

  public:
    Sequence(Gate* gateOb, AudioFX* audioOb, LightTree* lighttreeOb);
    void begin_sequence();
    void abort_seq();
    void set_ready();

  private:
    Gate *gate;
    AudioFX *audio;
    LightTree *lighttree;
};

#endif
