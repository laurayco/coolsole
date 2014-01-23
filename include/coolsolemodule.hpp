#ifndef __coolsole_module_hpp
#define __coolsole_module_hpp

#include "../include/coolsole.hpp"

#include <Python.h>

typedef struct {
  PyObject_HEAD
  /* Type-specific fields go here. */
  Coolsole::FormattedOutput *__cpp_object;

} coolsole_FormattedOutput;

extern "C" {
  static PyObject *say_hello(PyObject *, PyObject *);

  /* Formatted Output base-class. */
  static void deallocate_formatted_output(coolsole_FormattedOutput *);
  static void allocate_formatted_output(PyTypeObject *, PyObject *, PyObject *);
  static void init_formatted_output(coolsole_FormattedOutput *self, PyObject *args, PyObject *kwds);
  /*static PyObject* formatted_output_reset(PyObject*);
  static PyObject* formatted_output_get_format(PyObject*);
  static PyObject* formatted_output_set_format(PyObject*,PyObject*);*/

  PyMODINIT_FUNC PyInit_hello(void);
}
#endif