#ifndef constantbuffer_h
#define constantbuffer_h

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* start;
    int length;
} String;

typedef enum {
    CONST_NUMBER,
    CONST_IDENTIFIER
} ConstantType;

typedef struct {
   ConstantType type;
   
   union {
       double number;
       String* identifier;
   } as;

} Constant;

typedef struct {
    int size;
    int count;

    Constant* values;
} ConstantBuffer;

//Macro to check the type tag
#define IS_NUMBER(value) ((value.type) == CONST_NUMBER)
#define IS_IDENTIFIER(value) ((value.type) == CONST_IDENTIFIER)

//Macro to read the data as 
#define AS_NUMBER(value) (value.as.number)
#define AS_IDENTIFIER(value) (value.as.identifier)

//Macro to create object as type
#define NUMBER_CONST(value) ((Constant){CONST_NUMBER, {.number = value} })
#define IDENTIFIER_CONST(value) ((Constant){CONST_IDENTIFIER, {.identifier = (String*)value}})

void initConstantBuffer(ConstantBuffer* buffer);
void freeConstantBuffer(ConstantBuffer* buffer);
int writeConstantBuffer(ConstantBuffer* buffer, Constant value);

#endif
