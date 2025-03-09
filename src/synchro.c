#include "ensitheora.h"
#include "synchro.h"
#include <pthread.h>

/* les variables pour la synchro, ici */
pthread_cond_t cond_fen = PTHREAD_COND_INITIALIZER; 
pthread_cond_t cond_tex = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m_fen  = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t m_tex  = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_wri = PTHREAD_COND_INITIALIZER; 
pthread_cond_t cond_aff = PTHREAD_COND_INITIALIZER;
int count = 0;


/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    pthread_mutex_lock(&m_fen);
    windowsx = buffer[0].width;
    windowsy = buffer[0].height;
    pthread_cond_signal(&cond_fen);
    pthread_mutex_unlock(&m_fen);
    
}

void attendreTailleFenetre() {
    pthread_mutex_lock(&m_fen);
    while(windowsx== 0 || windowsy == 0){
        pthread_cond_wait(&cond_fen,&m_fen);
    }
    pthread_mutex_unlock(&m_fen);
}

void signalerFenetreEtTexturePrete() {
    pthread_mutex_lock(&m_fen);
    pthread_cond_signal(&cond_fen);
    pthread_cond_signal(&cond_tex);
    pthread_mutex_unlock(&m_fen);
}

void attendreFenetreTexture() {
    pthread_mutex_lock(&m_fen);
    while(texturedate[NBTEX-1].plane[2]==NULL){
        pthread_cond_wait(&cond_tex,&m_fen);
    }
    pthread_mutex_unlock(&m_fen);
}

void debutConsommerTexture() {
    pthread_mutex_lock(&m_tex);
    while (count == 0){
        pthread_cond_wait(&cond_aff,&m_tex);
    }
    count--;
    pthread_mutex_unlock(&m_tex);
}

void finConsommerTexture() {
    pthread_mutex_lock(&m_tex);
    pthread_cond_signal(&cond_wri);
    pthread_mutex_unlock(&m_tex);
}

void debutDeposerTexture() {
    pthread_mutex_lock(&m_tex);
    while (count == NBTEX){
        pthread_cond_wait(&cond_wri,&m_tex);
    }
    count++;
    pthread_mutex_unlock(&m_tex);
}

void finDeposerTexture() {
    pthread_mutex_lock(&m_tex);
    pthread_cond_signal(&cond_aff);
    pthread_mutex_unlock(&m_tex);
}
