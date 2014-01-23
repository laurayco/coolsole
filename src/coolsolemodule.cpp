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

/*
  static void deallocate_formatted_output(coolsole_FormattedOutput*);
  static void allocate_formatted_output(PyTypeObject*, PyObject*, PyObject*);
  static void init_formatted_output(coolsole_FormattedOutput*, PyObject *, PyObject *);
  static PyObject* formatted_output_reset(PyObject*);
  static PyObject* formatted_output_get_format(PyObject*);
  static PyObject* formatted_output_set_format(PyObject*,PyObject*);
*/

static void deallocate_formatted_output(coolsole_FormattedOutput *self)
{
  delete self->__cpp_object;
}

static int init_formatted_output(coolsole_FormattedOutput *self, PyObject *args, PyObject *kwds)
{
  /*
    Since I'm not exposing anything
    to the external python members,
    I shouldn't need to do any kind of
    reference-counting, or assignments
    here
  */
  return 0;
}

static PyObject *allocate_formatted_output(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  coolsole_FormattedOutput *self = (coolsole_FormattedOutput *)type->tp_alloc(type, 0);
  self->__cpp_object = new Coolsole::FormattedOutput();
  return (PyObject *)self;
}

PyMODINIT_FUNC PyInit_coolsole(void)
{
  PyObject *m;
  if (PyType_Ready(&NoddyType) < 0) {
    return NULL;
  }
  m = PyModule_Create(&coolsole_module);
  if (m == NULL) {
    return NULL;
  }
  Py_INCREF(&coolsole_FormattedOutputType);
  PyModule_AddObject(m, "Noddy", (PyObject *)&coolsole_FormattedOutputType);
  return m;
}