/**
 * Copyright (c) 2020, Levi Bland.
 * All Rights Reserved.
 * This source code is licensed under the GNU GPL v3.0
 * Please read the LICENSE file in the root directory of this project
 * before using and/or modifying this source code.
 */
 
 #ifndef JOE_VM_H
 #define JOE_VM_H
 
 #include "chunk.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

/**
 * The call frame.
 * @author RailRunner16
 */
typedef struct {
    ObjClosure* closure;
    uint8_t* ip;
    Value* slots;
} CallFrame;

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stackTop;
    Obj* objects;
    Table globals;
    Table strings;
    ObjString* initString;
    ObjUpvalue* openUpvalues;

    CallFrame frames[FRAMES_MAX];
    int frameCount;

    const char* scriptName;
    const char* currentScriptName;

    int grayCount;
    int grayCapacity;
    Obj** grayStack;

    size_t bytesAllocated;
    size_t nextGC;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

/**
 * The main VM instance.
 */
extern VM vm;

void initVM(const char* scriptName);

void freeVM();

InterpretResult interpret(const char* source);

void push(Value value);

Value pop();

void defineNative(const char* name, NativeFn function);

void defineNativeVoid(const char* name, NativeFnVoid function);

void runtimeError(const char* format, ...);
 
#endif   // JOE_VM_H
