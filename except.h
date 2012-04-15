#ifndef EXCEPT_INCLUDE
#define EXCEPT_INCLUDE
#include <setjmp.h>

#define T Except_T

struct T
{
    const char *reason;
};

typedef struct T T;

struct Except_Frame
{
    struct Except_Frame *prev;
    jmp_buf env;
    char *file;
    int line;
    const T *except;
};

typedef struct Except_Frame Except_Frame;

//异常栈的定义
extern Except_Frame *except_stack;

//这是关于异常的定义
extern T Assert_Failed;

enum
{
    Except_entered = 0,
    Except_raised,
    Except_handled,
    Except_finalized
};

//声明的函数
void except_raise(const T *except,const char *file,const int lineno);
//宏定义的
#define RAISE(e) except_raise(&(e),__FILE__,__LINE__)
#define RERAISE  except_raise((except_frame.except),except_frame.file,except_frame.line)

#define TRY do{\
    volatile int except_flag;\
    Except_Frame except_frame;\
    except_frame.prev = except_stack;\
    except_stack = &except_frame;\
    except_flag = setjmp(except_frame.env);\
    if(except_flag == Except_entered)\
    {

#define EXCEPT(e)  if(except_flag == Except_entered)\
			except_stack = except_stack->prev;\
		    }\
		    else if(except_frame.except == &(e))\
		    {\
			except_flag = Except_handled;

#define ELSE	   if(except_flag == Except_entered)\
			except_stack = except_stack->prev;\
		    }\
		    else\
		    {\
			except_flag = Except_handled;

#define FINALLY	   if(except_flag == Except_entered)\
			except_stack = except_stack->prev;\
		    }\
		    {\
			if(except_flag == Except_entered)\
			    except_flag = Except_finalized;
#define END_TRY \
		    if(except_flag == Except_entered)\
			except_stack = except_stack->prev;\
		    }\
		    if(except_flag == Except_raised)\
			RERAISE;\
	     }while(0);

#endif
