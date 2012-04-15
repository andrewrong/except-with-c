#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "except.h"

Except_Frame *except_stack = NULL;

void except_raise(const Except_T *e,const char *file,const int line)
{
    Except_Frame *p = except_stack;

    assert(e);

    if(p == NULL)
    {
	fprintf(stderr,"Unchanged excepted ");
	
	if(e->reason)
	{
	    fprintf(stderr,"%s ",e->reason);
	}
	else
	{
	    fprintf(stderr,"at ox%p ",e);
	}
	
	if(file && line >0)
	{
	    fprintf(stderr,"raised at %s:%d\n",file,line);
	}

	fprintf(stderr,"abort.....\n");
	fflush(stderr);
	abort();
    }
    
    p->except = e;
    p->file = file;
    p->line = line;
/*
 * 这里的这个pop stack表示不是很能明白*/
    except_stack = except_stack->prev;

    longjmp(p->env,Except_raised);
}

