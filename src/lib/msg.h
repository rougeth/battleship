#ifndef _MSG_H_
#define _MSG_H_


typedef struct introducion_message {

    int type;
    char nickname[30];

} introducion_message;

typedef struct attack_message {

    int type;
    int x, y;

} attack_message;

typedef struct response_message {

    int type;
    char response;

} response_message;


#endif