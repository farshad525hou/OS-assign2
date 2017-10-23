//Use a buffer size of 10
#include "../buffer.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define TRUE 1
buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int insertPointer = 0, removePointer = 1;
void *producer(void *param);
void *consumer(void *param);
int insert_item(buffer_item item){
     //Acquire Empty Semaphore
    sem_wait(&empty);
    //Acquire mutex lock to protect buffe
	pthread_mutex_lock(&mutex);
    if(buffer[insertPointer]==0){
      buffer[insertPointer++] = item;
      insertPointer = insertPointer % 3;
    }
    //Release mutex lock and full semaphore
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    return 0;
}
buffer_item remove_item(){
  buffer_item item;
  //Acquire Full Semaphore
  sem_wait(&full);
//Acquire mutex lock to protect buffer
  pthread_mutex_lock(&mutex);
    item = buffer[removePointer];
    buffer[removePointer] = 0;
    removePointer++;
    removePointer = removePointer % 3;
  pthread_mutex_unlock(&mutex);
  sem_post(&empty);
  return item;
}
int main(int argc, char *argv[])
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    srand(time(0));
//Create the producer and consumer threads
    for(int i = 0; i < 1; i++)
    {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, producer, NULL);
       }
	sleep(1);
    for(int j = 0; j < 6; j++)
        {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, consumer, NULL);
        }
//usleep for user specified time
    sleep(30);
    return 0;
    }
void *producer(void *param)
{
    buffer_item random;
    int r,r1;
    while(TRUE)
    {
        r = rand() % 3;
        sleep(r);
        random = rand();
        if(insert_item(random))
            fprintf(stderr, "Error");
        else
            printf("Producer produced %d \n", random);
        }
}
void *consumer(void *param)
{
    buffer_item item_out;
    int r,r1;

    while(TRUE)
        {
        r = rand() % 3;
        sleep(r);
       // printf("helo");
       item_out=remove_item();
         printf("Buyer bought %d \n", item_out);
        }
}
