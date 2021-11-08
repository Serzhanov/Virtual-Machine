# Virtual-Machine
Virtual Machine (Transforms low-level programming language to byte code (from 32 to 8) and execute it)



INSTRUCTIONS:

PUSH->pushing into the stack

POP->popping from the stack the last value

ADD->pop the last two values off the stack and sum up them

MUL->pop the last two values off the stack and multiply them

DIV->pop the last two values off the stack and divide first by second 

SUB->pop the last two values off the stack and substract first by second

JMP->jumping onto specific lane which has been passed as argument

LT-> <

GT-> >

EQ-> ==

NE-> !=

STORE-> store into the first argument value of second argument

LOAD-> load the last value of the stack

CALL-> same as JMP except that before the jump we push the current position into the stack (work with RETURN)

RETURN->we pop the last value from the stack (after CALL) to get return on last position

LABEL->just a mark

@->comments

HLT->end of code
