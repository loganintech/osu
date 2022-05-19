#include "beavalloc.h"
#include "unistd.h"
#include "stdio.h"  // for stderr
#include "string.h" // for memset
#include "errno.h"

#define bool int
#define TRUE 1
#define FALSE 0
#define REGION_DATA_SIZE sizeof(struct region_info)
#define BLOCK_REQUEST 1024

static struct region_info *head;
static bool global_verbose = FALSE;

struct region_info
{
    size_t bytes;
    struct region_info *next;
    struct region_info *prev;
    bool is_free;
};

struct region_info *get_empty_block(struct region_info **last, size_t size);
struct region_info *get_bytes(struct region_info *last, size_t size);

struct region_info *get_empty_block(struct region_info **last, size_t size)
{
    struct region_info *curr = *last;
    while (curr != NULL && (curr->bytes < size || !curr->is_free))
    {
        *last = curr;
        curr = curr->next;
    }
    return curr;
}

struct region_info *get_bytes(struct region_info *last, size_t size)
{
    struct region_info *new_block = sbrk(0);
    struct region_info *second_block = sbrk(0);

    size_t wanted = size + REGION_DATA_SIZE;
    size_t total = BLOCK_REQUEST;
    void *new_bytes = sbrk(BLOCK_REQUEST);
    void* errcheck;
    if (new_bytes == (void *)-1) // an error occurred
    {
        return NULL;
    }
    new_block->bytes = size;

    // If we said wanted < 0 we'd never stop because size_t would wrap
    while (size + REGION_DATA_SIZE > BLOCK_REQUEST && wanted + BLOCK_REQUEST >= BLOCK_REQUEST) {
        wanted -= BLOCK_REQUEST;
        total += BLOCK_REQUEST;

        errcheck = sbrk(BLOCK_REQUEST);
        if (errcheck == (void *)-1) // an error occurred
        {
            return NULL;
            errno = ENOMEM;
        }
    }

    // If we have enough leftover to make another block
    if (total - (new_block->bytes + REGION_DATA_SIZE) > REGION_DATA_SIZE) {

        second_block = ((void*)new_block) + REGION_DATA_SIZE + new_block->bytes;
        // Account for the region of the first block and this second block
        second_block->bytes = (((void*)new_block) + total) - (new_block->bytes + (REGION_DATA_SIZE * 2));
        second_block->next = NULL;
        second_block->is_free = TRUE;

    }
    // new_bytes and new_block should point to the same thing now

    new_block->next = NULL;
    if (last != NULL)
    {
        last->next = new_block;
        new_block->prev = last;

        // If we actually changed the second block's address (aka it exists) add it to the map
        if (second_block > new_block) {
            new_block->next = second_block;
            second_block->prev = new_block;
        }
    }

    new_block->is_free = FALSE;
    return new_block;
}

void *beavalloc(size_t size)
{
    struct region_info *last;
    struct region_info *new_block;
    if (size == 0)
    {
        return NULL;
    }

    if (head == NULL)
    { // We haven't initialized anything yet
        new_block = get_bytes(NULL, size);
        if (new_block == NULL)
        {
            return NULL;
        }
        head = new_block;
        return new_block + 1;
    }

    //This isn't the first call to malloc
    last = head;
    // get_empty_block traverses the list changing last
    new_block = get_empty_block(&last, size);
    if (new_block != NULL)
    {
        new_block->is_free = FALSE;

        // Check if we have enough space to split the block
        // Make sure it has enough space, giving it at least 64 (arbitrarily chosen) bytes of overhead
        if (new_block->bytes > size + REGION_DATA_SIZE + 64)
        {
            // We have to divide size by the region size because new_block is already a `region_info` pointer
            struct region_info *second_part = new_block + 1 + (size / REGION_DATA_SIZE);
            second_part->next = new_block->next;                               // Set our second part of this block to the next of w/e the current block is
            second_part->bytes = (new_block->bytes - size) - REGION_DATA_SIZE; // The size of the new block is the size of the old one - the size we're taking - the size of the data region
            second_part->is_free = TRUE;
            second_part->prev = new_block;
            new_block->next = second_part; // Set the current block to point to our new second part
            new_block->bytes = size;       // Reset the size on the new block
        }

        return new_block + 1;
    }

    new_block = get_bytes(last, size);
    if (new_block == NULL)
    {
        return NULL;
    }
    return new_block + 1; // Skip past the metadata and return the raw bytes
}

void beavfree(void *ptr)
{
    struct region_info *meta;
    if (ptr == NULL)
    {
        return;
    }

    struct region_info *meta_copy;
    meta = ptr - REGION_DATA_SIZE;
    meta_copy = meta;
    meta->is_free = TRUE;
    while (meta_copy->prev && meta_copy - (meta_copy->prev->bytes / REGION_DATA_SIZE) - 1 == meta_copy->prev && meta_copy->prev->is_free)
    {
        // Expand the previous node's current bytes to the size of it plus the area of this region
        meta->prev->bytes = meta->prev->bytes + REGION_DATA_SIZE + meta->bytes;
        // When going backwards, we want to change the previous node's "next" to point to the current node's next, eliminating it from the list
        meta->prev->next = meta->next;
        // And then traverse backwards
        meta = meta->prev;
    }

    // printf("\n%p - %p\n", meta + 1 + (meta->bytes / REGION_DATA_SIZE), meta->next);
    while (meta && meta + 1 + (meta->bytes / REGION_DATA_SIZE) == meta->next && meta->next->is_free)
    {
        // Expand the current bytes to the bytes of this region and the next + the info region
        meta->bytes = meta->bytes + REGION_DATA_SIZE + meta->next->bytes;
        // When going forwards, we don't want to change the previous because that isn't changing
        // Set our next to the next's next so that we eliminate the middle one from the list
        meta->next = meta->next->next;
        // And then traverse to the new next node
        meta = meta->next;
    }
}

void beavalloc_reset(void)
{
    brk(head);
    head = NULL;
}

void beavalloc_set_verbose(uint8_t verbose)
{
    global_verbose = verbose > 0;
}

void *beavcalloc(size_t nmemb, size_t size)
{
    size_t calc_size;
    void *ptr;
    calc_size = nmemb * size;
    ptr = beavalloc(calc_size);
    memset(ptr, 0, calc_size);
    return ptr;
}

void *beavrealloc(void *ptr, size_t size)
{
    struct region_info *meta;
    void *new_bytes;

    if (ptr == NULL)
    {
        return beavalloc(size);
    }

    meta = ptr - REGION_DATA_SIZE;
    if (meta->bytes >= size)
    {
        return ptr;
    }

    new_bytes = beavalloc(size);
    if (new_bytes == NULL)
    {
        return NULL;
    }

    memcpy(new_bytes, ptr, meta->bytes);
    beavfree(ptr);
    return new_bytes;
}

void beavalloc_dump(unsigned int leaks_only)
{
    struct region_info *curr = NULL;
    unsigned int i = 0;
    unsigned int leak_count = 0;
    unsigned int user_bytes = 0;
    unsigned int capacity_bytes = 0;
    unsigned int block_bytes = 0;
    unsigned int used_blocks = 0;
    unsigned int free_blocks = 0;

    if (leaks_only)
    {
        fprintf(stderr, "heap lost blocks\n");
    }
    else
    {
        fprintf(stderr, "heap map\n");
    }
    fprintf(stderr, "  %s\t%s\t%s\t%s\t%s"
                    "\t%s\t%s\t%s\t%s\t%s\t%s"
                    "\n",
            "blk no  ", "block add ", "next add  ", "prev add  ", "data add  ",
            "blk off  ", "dat off  ", "capacity ", "size     ", "blk size ", "status   ");
    for (curr = head, i = 0; curr != NULL; curr = curr->next, i++)
    {
        if (leaks_only == FALSE || (leaks_only == TRUE && curr->is_free == FALSE))
        {
            fprintf(stderr, "  %u\t\t%9p\t%9p\t%9p\t%9p\t%u\t\t%u\t\t"
                            "%u\t\t%u\t\t%u\t\t%s\t%c\n",
                    i,
                    curr,
                    curr->next,
                    curr->prev,
                    curr + REGION_DATA_SIZE,
                    (unsigned)((void *)curr - (void *)head),
                    (unsigned)((void *)curr + REGION_DATA_SIZE - (void *)head),
                    ((unsigned int)curr->is_free > 0) * (unsigned)curr->bytes, // If it's free the bytes are available
                    (unsigned)curr->bytes,
                    (unsigned)(curr->bytes + REGION_DATA_SIZE),
                    curr->is_free ? "free  " : "in use",
                    curr->is_free ? '*' : ' ');
            if (curr->is_free)
            {
                capacity_bytes += curr->bytes;
            }
            user_bytes += curr->bytes;

            block_bytes += curr->bytes + REGION_DATA_SIZE;
            if (curr->is_free == FALSE && leaks_only == TRUE)
            {
                leak_count++;
            }
            if (curr->is_free == TRUE)
            {
                free_blocks++;
            }
            else
            {
                used_blocks++;
            }
        }
    }
    if (leaks_only)
    {
        if (leak_count == 0)
        {
            fprintf(stderr, "  *** No leaks found!!! That does NOT mean no leaks are possible. ***\n");
        }
        else
        {
            fprintf(stderr, "  %s\t\t\t\t\t\t\t\t\t\t\t\t"
                            "%u\t\t%u\t\t%u\n",
                    "Total bytes lost", capacity_bytes, user_bytes, block_bytes);
        }
    }
    else
    {
        fprintf(stderr, "  %s\t\t\t\t\t\t\t\t\t\t\t\t"
                        "%u\t\t%u\t\t%u\n",
                "Total bytes used", capacity_bytes, user_bytes, block_bytes);
        fprintf(stderr, "  Used blocks: %u  Free blocks: %u  "
                        "Min heap: %p    Max heap: %p\n",
                used_blocks, free_blocks, (void *)head, block_bytes + (void *)head);
    }
}
