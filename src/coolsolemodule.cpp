#include "../include/coolsolemodule.hpp"

#include <Python.h>

static PyObject *say_hello(PyObject *self, PyObject *args)
{
  const char *name;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return NULL;
  }
  printf("Hello %s!\n", name);
  Py_RETURN_NONE;
}

PyMODINIT_FUNC PyInit_coolsole(void)
{
  PyObject *m;
  m = PyModule_Create(&hello_module);
  if (m == NULL) {
    return NULL;
  }
  return m;
}