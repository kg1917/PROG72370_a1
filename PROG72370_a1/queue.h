#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#define MAX_USERNAME 9

enum faction {
	RED = 0, BLUE = 1, GREEN = 2
};

struct user {
	char username[MAX_USERNAME];
	uint8_t level;
	enum faction faction;

	struct user *prev;
	struct user *next;
};

typedef struct queue {
	struct user *tail;
	struct user *head;
	size_t length;
} QUEUE_T;

QUEUE_T *initQueue();

// Enqueues a new user to the head
char enqueue(QUEUE_T *, char[], uint8_t, enum faction);

struct user dequeue(QUEUE_T *);

bool queue_empty(QUEUE_T *);

void destroyQueue(QUEUE_T *);