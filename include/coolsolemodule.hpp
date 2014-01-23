#include "../include/coolsole.hpp"

#include <Python.h>

extern "C" {
  static PyObject *say_hello(PyObject *, PyObject *);
  static PyMethodDef HelloMethods[];
  PyMODINIT_FUNC inithello();
}