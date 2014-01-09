#ifndef _CONTROLLER_H
#define _CONTROLLER_H

int abort();

int setStart(int *start);
int setIInc(int *i_inc);
int setJInc(int *j_inc);
int setTSettle(int t_settle);
int setPixels(int pixels);

int gotoPosition(int *position);
int getPosition(int *position);
int getChannels(int *values);

int 1DScan(uint16_t *pixelList, int wait_time);
int 2DScan(uint16_t *pixelList, const char *filename);

#endif
