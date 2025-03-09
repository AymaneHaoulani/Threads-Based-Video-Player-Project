#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "ensitheora.h"
#include "synchro.h"
#include "oggstream.h"
#include "stream_common.h"

int main(int argc, char *argv[]) {
  int res;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s FILE", argv[0]);
    exit(EXIT_FAILURE);
  }
  assert(argc == 2);

  // Initialisation de la SDL
  res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
  atexit(SDL_Quit);
  assert(res == 0);

  // Your code HERE
  pthread_t vid_thread;
  pthread_t aud_thread;
  
  // start the two stream readers (theoraStreamReader and vorbisStreamReader)
  // each in a thread
  pthread_create(&vid_thread,NULL, theoraStreamReader,(void*)argv[1]);
  pthread_create(&aud_thread,NULL,vorbisStreamReader,(void*)argv[1]);
  
  

  // wait for vorbis thread
  pthread_join(aud_thread,NULL);

  // 1 seconde of sound in advance, thus wait 1 seconde
  // before leaving
  sleep(1);

  pthread_cancel(aud_thread);
  pthread_cancel(vid_thread);
  // Wait for theora and theora2sdl threads
  pthread_join(vid_thread,NULL);
  // TODO
  /* liberer des choses ? */
  pthread_mutex_destroy(&m_hash);
  pthread_mutex_destroy(&m);
  pthread_mutex_destroy(&m_fen);
  pthread_mutex_destroy(&m_tex);

  pthread_cond_destroy(&cond_aff);
  pthread_cond_destroy(&cond_wri);
  pthread_cond_destroy(&cond_fen);
  pthread_cond_destroy(&cond_tex);
  
  
  exit(EXIT_SUCCESS);
}
