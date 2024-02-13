#define _CRT_SECURE_NO_WARNINGS

#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


QUEUE_T *initQueue() {
	QUEUE_T *queue = (QUEUE_T *)malloc(sizeof(QUEUE_T));
	if (queue == 0) {
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}
	queue->head = 0;
	queue->tail = 0;
	queue->length = 0;
	return queue;
}

char enqueue(QUEUE_T *queue, char name[], uint8_t level, enum faction faction) {
	struct user *user = (struct user *)malloc(sizeof(struct user));
	if (user == 0) {
		fprintf(stderr, "Out of memory\n");
		return 1;
	}
	user->level = level;
	user->faction = faction;
	strncpy(user->username, name, MAX_USERNAME);

	if (queue == 0)
		return 0;
	// Set head and tail to user if queue is empty
	if (queue->length <= 0) {
		queue->head = user;
		queue->tail = user;
		queue->length++;
		return 0;
	}
	// Set head to user and link tail and user if length is 1
	if (queue->length == 1) {
		queue->head = user;
		queue->tail->prev = user;
		user->next = queue->tail;
		queue->length++;
		return 0;
	}
	// Link head and user and make user the new head
	else {
		user->next = queue->head;
		queue->head->prev = user;
		queue->head = user;
		queue->length++;
		return 0;
	}
}

struct user dequeue(QUEUE_T *queue) {
	if (queue->length == 0) {
		struct user out = { 0 };
		return out;
	}
	else if (queue->length == 1) {
		struct user out = *(queue->tail);

		free(queue->tail);
		queue->length--;

		queue->head = 0;
		queue->tail = 0;
		return out;
	}
	struct user out = *(queue->tail);
	struct user *newtail = queue->tail->prev;

	free(queue->tail);
	queue->tail = newtail;
	queue->length--;

	out.next = 0;
	out.prev = 0;

	return out;
}

bool queue_empty(QUEUE_T *queue) {
	return queue->length == 0;
}

void destroyQueue(QUEUE_T *queue) {
	while (!queue_empty(queue)) {
		dequeue(queue);
	}
	free(queue);
}