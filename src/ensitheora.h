#ifndef THEORA_H
#define THEORA_H

#include "ensivideo.h"
#include <SDL2/SDL.h>
#include <ogg/ogg.h>

#define NBTEX 30

struct TextureDate {
  unsigned char *plane[3]; // copy of plane are contiguous, thus
                           // stride is width
  double timems;           // expiration date of the frame, in ms
};

extern struct streamstate *theorastrstate;

void *draw2SDL(void *arg);
void theora2SDL(struct streamstate *s);

extern int windowsx;
extern int windowsy;

extern int tex_iaff;
extern int tex_iwri;
extern struct TextureDate texturedate[NBTEX];
extern pthread_mutex_t m_hash ;

#endif
