#include "assert.h"
#include "except.h"

#include <stdio.h>

int main()
{
    TRY
	assert(0);
    END_TRY

    return 0;
}
