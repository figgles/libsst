/*
	EventQueue.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/18/2012

	Purpose: 

	Common event queue code for libsst-wm implementations

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _EVENTQUEUE_H
#define _EVENTQUEUE_H

#include <SST/SST_WMEvent.h>
#include <SST/SST_Build.h>
#include <stdlib.h>

typedef struct EventQueue
{
	SST_WMEvent* events;
	size_t head;	/* Index of next item to add (i.e. unused slot) */
	size_t tail;	/* Index of next item to remove (i.e. used slot) */
	size_t count;	/* Number of items in the queue */
	size_t storageSize; /* Size of the backing storage */
} EventQueue;

#define EQ_DEFAULT_SIZE 32 /* Default capacity of the event queue. It may grow beyond this. */

/*************************************************************************/

/* Initialize an event queue structure, returning non-zero if successful */
static INLINE int InitEQ(EventQueue* q)
{
	/* Allocate raw storage for event queue */
	q->events = (SST_WMEvent*)malloc(EQ_DEFAULT_SIZE * sizeof(SST_WMEvent));
	if(q->events == NULL)
		return 0;

	/* Initialize storage */
	q->head = 0;
	q->tail = 0;
	q->count = 0;
	q->storageSize = EQ_DEFAULT_SIZE;

	return 1;
}

/*************************************************************************/

/* Allocate a slot from the queue (as if adding) and return pointer. This manually
eliminates copying a SST_WMEvent structure that most "enqueue" operation require.  */
static INLINE SST_WMEvent* AllocSlotInEQ(EventQueue* q)
{
	SST_WMEvent* slot;

	/* Need to increase capacity? */
	if(q->head == q->tail && q->count == q->storageSize)
	{
		const size_t newSize = q->storageSize * 2;
		SST_WMEvent* events;

		/* Expand the queue */
		events = realloc(q->events, newSize * sizeof(SST_WMEvent));
		if(events == NULL)
			return NULL;

		/* All 'count' items from [0,tail] need to be moved to [oldSize, oldSize+count] */
		if(q->tail != 0)
		{
			/*
				1) A full queue
				       v--h
				[G][H][A][B][C][D][E][F]
				       ^--t

				2) Resized
				       v--h
				[G][H][A][B][C][D][E][F][ ][ ][ ][ ][ ][ ][ ][ ]
				       ^--t

				3) Shift elements from 0 to tail to end, update head ptr
				                               v--h
				[ ][ ][A][B][C][D][E][F][G][H][ ][ ][ ][ ][ ][ ]
				       ^--t

		   */

			/* Shift elements */
			memmove(&events[q->storageSize], &events[0], q->tail * sizeof(SST_WMEvent));
			
		}

		/* Adjust head pointer to point to next empty slot */
		q->head = q->tail + q->storageSize;

		/* Update storage fields */
		q->storageSize = newSize;
		q->events = events;
	} /* if(needed to increase capacity) */

	/* Get the pointer to the slot where the event may be stored */
	slot = &q->events[q->head];

	/* Advance the head pointer by 1 */
	q->head = (q->head + 1) % q->storageSize;
	q->count += 1;

	/* Return the slot */
	return slot;
}

static INLINE int RemoveFromEQ(EventQueue* q, SST_WMEvent* event)
{
	/* Completely empty? */
	if(q->head == q->tail && q->count != q->storageSize)
		return 0;

	/* Copy the structure */
	*event = q->events[q->tail];

	/* Advance the tail pointer by 1 */
	q->tail = (q->tail + 1) % q->storageSize;
	q->count -= 1;

	/* OK */
	return 1;
}

static INLINE void DestroyEQ(EventQueue* q)
{
	if(q->events != NULL)
		free(q->events);
}

#endif

