/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object* obj);
void freeScope(Scope* scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab* symtab;
Type* intType;
Type* charType;

/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type* makeCharType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type* makeArrayType(int arraySize, Type* elementType) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type* duplicateType(Type* type) {
  Type* newType = (Type*)malloc(sizeof(Type));
  newType->typeClass = type->typeClass;
  newType->arraySize = type->arraySize;

  if(type->typeClass == TP_ARRAY && type->elementType != NULL) {
    newType->elementType = duplicateType(type->elementType);
  } else {
    newType->elementType = type->elementType;
  }

  return newType;
}

int compareType(Type* type1, Type* type2) {
  if(type1->typeClass != type2->typeClass) {
    return 0;
  }

  if(type1->typeClass == TP_INT || type1->typeClass == TP_CHAR) {
    return 1; // Cùng kiểu cơ bản
  }

  if(type1->typeClass == TP_ARRAY) {
    if(type1->arraySize != type2->arraySize) {
      return 0;
    }
    return compareType(type1->elementType, type2->elementType);
  }

  return 0;
}

void freeType(Type* type) {
  if(type != NULL) {
    if(type->elementType != NULL) {
      freeType(type->elementType);
    }
    free(type);
  }
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
  ConstantValue *newIntConstantValue = (ConstantValue*)malloc(sizeof(ConstantValue));
  newIntConstantValue->type = TP_INT;
  newIntConstantValue->intValue = i;
  return newIntConstantValue;
}

ConstantValue* makeCharConstant(char ch) {
  ConstantValue *newCharConstantValue = (ConstantValue*)malloc(sizeof(ConstantValue));
  newCharConstantValue->type = TP_CHAR;
  newCharConstantValue->charValue = ch;
  return newCharConstantValue;
}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  ConstantValue *newConstantValue = (ConstantValue*)malloc(sizeof(ConstantValue));
  newConstantValue->type = v->type;

  if(v->type == TP_CHAR) {
    newConstantValue->charValue = v->charValue;
  } else if(v->type == TP_INT) {
    newConstantValue->intValue = v->intValue;
  }

  return newConstantValue;
}

/******************* Object utilities ******************************/

Scope* createScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* createProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program, NULL);
  symtab->program = program;
  return program;
}

Object* createConstantObject(char *name) {
  Object *newConstantObject = (Object*)malloc(sizeof(Object));
  strcpy(newConstantObject->name, name);
  newConstantObject->kind = OBJ_CONSTANT;
  newConstantObject->constAttrs = (ConstantAttributes*)malloc(sizeof(ConstantAttributes));
  newConstantObject->constAttrs->value = NULL;
  return newConstantObject;
}

Object* createTypeObject(char *name) {
  Object *newTypeObject = (Object*)malloc(sizeof(Object));
  strcpy(newTypeObject->name, name);
  newTypeObject->kind = OBJ_TYPE;
  newTypeObject->typeAttrs = (TypeAttributes*)malloc(sizeof(TypeAttributes));
  newTypeObject->typeAttrs->actualType = NULL;
  return newTypeObject;
}

Object* createVariableObject(char *name) {
  Object *newVariableObject = (Object*)malloc(sizeof(Object));
  strcpy(newVariableObject->name, name);
  newVariableObject->kind = OBJ_VARIABLE;
  newVariableObject->varAttrs = (VariableAttributes*)malloc(sizeof(VariableAttributes));
  newVariableObject->varAttrs->type = NULL;
  newVariableObject->varAttrs->scope = symtab->currentScope;
  return newVariableObject;
}

Object* createFunctionObject(char *name) {
  Object *newFunctionObject = (Object*)malloc(sizeof(Object));
  strcpy(newFunctionObject->name, name);
  newFunctionObject->kind = OBJ_FUNCTION;
  newFunctionObject->funcAttrs = (FunctionAttributes*)malloc(sizeof(FunctionAttributes));
  newFunctionObject->funcAttrs->paramList = NULL;
  newFunctionObject->funcAttrs->returnType = NULL;
  newFunctionObject->funcAttrs->scope = createScope(newFunctionObject, symtab->currentScope);
  return newFunctionObject;
}

Object* createProcedureObject(char *name) {
  Object *newProcedureObject = (Object*)malloc(sizeof(Object));
  strcpy(newProcedureObject->name, name);
  newProcedureObject->kind = OBJ_PROCEDURE;
  newProcedureObject->procAttrs = (ProcedureAttributes*)malloc(sizeof(ProcedureAttributes));
  newProcedureObject->procAttrs->paramList = NULL;
  newProcedureObject->procAttrs->scope = createScope(newProcedureObject, symtab->currentScope);
  return newProcedureObject;
}

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  Object *newParameterObject = (Object*)malloc(sizeof(Object));
  strcpy(newParameterObject->name, name);
  newParameterObject->kind = OBJ_PARAMETER;
  newParameterObject->paramAttrs = (ParameterAttributes*)malloc(sizeof(ParameterAttributes));
  newParameterObject->paramAttrs->kind = kind;
  newParameterObject->paramAttrs->type = NULL;
  newParameterObject->paramAttrs->function = owner;
  return newParameterObject;
}

void freeObject(Object* obj) {
  if(obj == NULL) return;

  switch (obj->kind) {
    case OBJ_CONSTANT:
      if(obj->constAttrs != NULL) {
        if(obj->constAttrs->value != NULL) {
          free(obj->constAttrs->value);
        }
        free(obj->constAttrs);
      }
      break;

    case OBJ_TYPE:
      if(obj->typeAttrs != NULL) {
        if(obj->typeAttrs->actualType != NULL) {
          freeType(obj->typeAttrs->actualType);
        }
        free(obj->typeAttrs);
      }
      break;

    case OBJ_VARIABLE:
      if(obj->varAttrs != NULL) {
        if(obj->varAttrs->type != NULL) {
          freeType(obj->varAttrs->type);
        }
        free(obj->varAttrs);
      }
      break;

    case OBJ_PARAMETER:
      if(obj->paramAttrs != NULL) {
        if(obj->paramAttrs->type != NULL) {
          freeType(obj->paramAttrs->type);
        }
        free(obj->paramAttrs);
      }
      break;

    case OBJ_FUNCTION:
      if(obj->funcAttrs != NULL) {
        if(obj->funcAttrs->paramList != NULL) {
          freeReferenceList(obj->funcAttrs->paramList);
        }
        if(obj->funcAttrs->returnType != NULL) {
          freeType(obj->funcAttrs->returnType);
        }
        if(obj->funcAttrs->scope != NULL) {
          freeScope(obj->funcAttrs->scope);
        }
        free(obj->funcAttrs);
      }
      break;

    case OBJ_PROCEDURE:
      if(obj->procAttrs != NULL) {
        if(obj->procAttrs->paramList != NULL) {
          freeReferenceList(obj->procAttrs->paramList);
        }
        if(obj->procAttrs->scope != NULL) {
          freeScope(obj->procAttrs->scope);
        }
        free(obj->procAttrs);
      }
      break;

    case OBJ_PROGRAM:
      if(obj->progAttrs != NULL) {
        if(obj->progAttrs->scope != NULL) {
          freeScope(obj->progAttrs->scope);
        }
        free(obj->progAttrs);
      }
      break;

    default:
      break;
  }

  free(obj);
}

void freeScope(Scope* scope) {
  if(scope != NULL) {
    freeObjectList(scope->objList);
    free(scope);
  }
}

void freeObjectList(ObjectNode *objList) {
  if(objList != NULL) {
    ObjectNode *next = objList->next;
    freeObject(objList->object);
    free(objList); // FIXED: Phải free node
    freeObjectList(next);
  }
}

void freeReferenceList(ObjectNode *objList) {
  ObjectNode *curr = objList;
  while(curr != NULL) {
    ObjectNode *next = curr->next;
    free(curr);
    curr = next;
  }
}

void addObject(ObjectNode **objList, Object* obj) {
  ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL)
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL)
      n = n->next;
    n->next = node;
  }
}

Object* findObject(ObjectNode *objList, char *name) {
  ObjectNode *currentObject = objList;
  while(currentObject != NULL) {
    if(strcmp(currentObject->object->name, name) == 0) {
      return currentObject->object;
    }
    currentObject = currentObject->next;
  }
  return NULL;
}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  symtab->currentScope = NULL;

  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList), param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList), param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void) {
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope* scope) {
  symtab->currentScope = scope;
}

void exitBlock(void) {
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object* obj) {
  if (obj->kind == OBJ_PARAMETER) {
    Object* owner = symtab->currentScope->owner;
    switch (owner->kind) {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }

  addObject(&(symtab->currentScope->objList), obj);
}