#ifndef CODEGEN_H_
#define CODEGEN_H_

#include "../util/symtab.h"
#include <codegen/types.h>

#define SYSCALL_PRINT_INTEGER "1"	/**< The syscall code for printing an integer */
#define SYSCALL_PRINT_FLOAT   "2"   /**< The syscall code for printing a float */
#define SYSCALL_PRINT_STRING  "4"	/**< The syscall code for printing a string */
#define SYSCALL_READ_INTEGER  "5"	/**< The syscall code for reading an integer */
#define SYSCALL_READ_FLOAT    "6"   /**< The syscall code for reading a float */
#define SYSCALL_EXIT          "10"	/**< The syscall code for exiting the interpreter */

void genMain(DLinkList * instructions);
void genEnd(DLinkList * instructions);
int genString(DLinkList * declarations, SymTable symtab, int index);
void genNewLine(DLinkList * instructions);
int genInt(DLinkList * instructions, SymTable regSymTab, int n);
int genArith(DLinkList * instructions, SymTable regSymTab, int leftInd, int rightInd, char * type);
void genWriteStr(DLinkList * instructions, int index);
void genWriteNum(DLinkList * instructions, int resultInd);
void genRead(DLinkList * instructions, SymTable regSymTab, int index, int offset);
void genSpace(DLinkList * instructions, int n);
void genAssign(DLinkList * instructions, SymTable regSymTab, int index, int resultInd, int offset);
int genVal(DLinkList * instructions, SymTable regSymTab, int index, int offset);

#endif /*CODEGEN_H_*/
