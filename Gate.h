/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#ifndef _GATE_H
#define _GATE_H

class Gate {

  public:

    Gate();
    void random_wait();
    void ready();
    void arm();
    void drop();
    void abort();
    bool is_sequence_running();
    bool is_aborted();
    bool is_abortable();

    void set_sequence_running(bool running);
    void set_abortale(bool abortable);
};

#endif
