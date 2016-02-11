#ifndef __STREAMRIPPER_H__
#define __STREAMRIPPER_H__

#include <libstreamripper.h>

int stop_streamripper();
int start_streamripper();
int status_streamripper();
int streamripper_exists();
void setstream_streamripper(const char*);
void setpath_streamuri(char*);
void init_streamripper();

void streamripper_set_url(char*);
void streamripper_set_url_dest(char*);
int poll_streamripper(char* newfilename);

#endif
