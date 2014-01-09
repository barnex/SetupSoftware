#ifndef _CONTROLLER_H
#define _CONTROLLER_H

int abort(int fd);

int setStart(int fd, int *start);
int setIInc(int fd, int *i_inc);
int setJInc(int fd, int *j_inc);
int setTSettle(int fd, int t_settle);
int setPixels(int fd, int pixels);

int getPosition(int fd, int *position);
int getChannels(int fd, int *values);

int gotoPosition(int fd, int *position);
int 1DScan(int fd, uint16_t *pixelList, int wait_time);
int 2DScan(int fd, uint16_t *pixelList, const char *filename);

#endif
