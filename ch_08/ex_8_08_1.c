#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

/* malloc: general-purpose storage allocator */
void *malloc(unsigned long nbytes)
{
    Header *prevp, *p;
    Header *morecore(unsigned);
    unsigned nunits;

    if (nbytes <= 0)
        return NULL;

    nunits = (unsigned) (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr;;prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits) {
                prevp->s.ptr = p->s.ptr;
            } else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *) (p + 1);
        }
        if (p == freep) {
            if ((p = morecore(nunits)) == NULL)
                return NULL;
        }
    }
}

#define NALLOC  1024
/* morecore: ask system for more memory */
Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;
    void free(void *);

    if (nu < NALLOC)
        nu = NALLOC;
    cp = (char *) sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    free((void *) (up + 1));
    return freep;
}

/* free: put block ap in free list */
void free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;
    if (bp->s.size <= 0)
        return;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    }

    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}

/* bfree: free an arbitrary block p of n characters into the free list */
void bfree(void *p, unsigned long n)
{
    char *ap, *bp;
    Header *hp;

    if (n < 2 * sizeof(Header)) 
        return; /* not worth it */
    ap = (char *) p;
    bp = (char *) ((unsigned long) (ap + sizeof(Header) - 1) &
        sizeof(Header) * (-1));
    if (n - (bp - ap) < 2 * sizeof(Header)) {
        return; /* not worth it after alignment */
    }

    hp = (Header *) bp;
    hp->s.size = (n - (bp - ap)) / sizeof(Header);

    if (freep == NULL) { /* bfree can be called before malloc */
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }
    free((void *) (hp + 1));
}

/* multiply by 2 for alignment */
#define ENTRY_SIZE  ((int) (128 + sizeof(Header) / sizeof(int) * 2))

int main()
{
    int i, gap, *p;
    static int tmp[ENTRY_SIZE];
    
    bfree((void *) tmp, ENTRY_SIZE * sizeof(int));
    gap = sizeof(Header) / sizeof(int) * 2;
    p = (int *) malloc((ENTRY_SIZE - gap) * sizeof(int));
    for (i = 0; i < ENTRY_SIZE; ++i)
        p[i] = i;

    for (i = 0; i < ENTRY_SIZE - gap; ++i)
        printf("%3d%c", p[i], i % 16 == 15 ? '\n' : ' ');
    putchar('\n');
    /* malloc returns the memory passed to bfree*/
    for (i = 0; i < ENTRY_SIZE - gap; ++i)
        printf("%3d%c", tmp[i + gap], i % 16 == 15 ? '\n' : ' ');
    free(p);

    return 0;
}

