#ifndef SYNCHRO_H
#define SYNCHRO_H

#include "ensitheora.h"
#include <stdbool.h>

extern bool fini;
/* Les extern des variables pour la synchro ici */
extern pthread_cond_t cond_tex;
extern pthread_cond_t cond_fen; 
extern pthread_mutex_t m_fen ; 
extern pthread_mutex_t m_tex ;
extern pthread_cond_t cond_wri ; 
extern pthread_cond_t cond_aff ;


/* Fonctions de synchro à implanter */

void envoiTailleFenetre(th_ycbcr_buffer buffer);
void attendreTailleFenetre();

void attendreFenetreTexture();
void signalerFenetreEtTexturePrete();

void debutConsommerTexture();
void finConsommerTexture();

void debutDeposerTexture();
void finDeposerTexture();

#endif
