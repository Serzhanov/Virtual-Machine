# Virtual-Machine
Virtual Machine (Transforms low-level programming language to byte code (from 32 to 8) and execute it)


# INSTRUCTIONS:

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

# EXEMPLE FIBONACCI

LABEL start

@ A

  PUSH 10
  
  CALL fact
  
  JMP end
  
LABEL end

  POP
  
  HLT
  
LABEL fact

  @ B = A 
  
  LOAD $-2
  
@ if B < 2

  PUSH 2
  
  LOAD $-2
  
  LT _clfact
  
LABEL _fact

  @ B = B-1
  
  PUSH 1
  
  LOAD $-2
  
  SUB
  
  STORE $-2 $-1
  
  POP
  
  @ A = A * B
  
  LOAD $-3
  
  LOAD $-2
  
  MUL
  
  STORE $-4 $-1
  
  POP
  
  @ if B>1
  
  PUSH 1
  
  LOAD $-2
  
  GT _fact
  
LABEL _clfact

  POP
  
  RETURN
  
  # BYTE CODE
  
0000 0000 0d0a 0000 1100 0006 0000 010f
0c11 ffff feff 0000 0000 0c02 ffff feff
0007 0000 005e 0000 0100 ff0c ffff 03fe
ff0b ffff fffe ffff 01ff ff0c ffff 0cfd
ffff feff 0b04 ffff fcff ffff ffff 0001
0000 0100 ff0c ffff 08fe 0000 2500 0e01


