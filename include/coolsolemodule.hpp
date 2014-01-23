#ifndef __coolsole_module_hpp
#define __coolsole_module_hpp

#include "../include/coolsole.hpp"

#include <Python.h>

extern "C" {
  static PyObject *say_hello(PyObject *, PyObject *);
  PyMODINIT_FUNC PyInit_hello(void);
}

static PyMethodDef HelloMethods[2] = {
  {"say_hello", say_hello, METH_VARARGS, "Greet somebody."},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef hello_module = {
  PyModuleDef_HEAD_INIT,
  "coolsole",   /* name of module */
  NULL,      /* module documentation, may be NULL */
  -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
  HelloMethods
};
#endif