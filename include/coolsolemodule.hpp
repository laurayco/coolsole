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
  static void init_formatted_output(coolsole_FormattedOutput *, PyObject *, PyObject *);
  /*static PyObject* formatted_output_reset(PyObject*);
  static PyObject* formatted_output_get_format(PyObject*);
  static PyObject* formatted_output_set_format(PyObject*,PyObject*);*/

  PyMODINIT_FUNC PyInit_hello(void);
}

static PyMemberDef coolsole_formatted_output_members[] = {
  {NULL}  /* Has no python-accessible members. Only methods. ( ! ) */
};

static PyMethodDef coolsole_formatted_output_methods[] = {
  /*{
    "reset",
    (PyCFunction)formatted_output_reset,
    METH_NOARGS,
    "Set formatting back to original formatting."
  }, {
    "get_format",
    (PyCFunction)formatted_output_get_format,
    METH_NOARGS,
    "Get the current format object. ( READ-ONLY )."
  }, {
    "set_format",
    (PyCFunction)formatted_output_set_format,
    METH_NOARGS,
    "Set the current format object. ( READ-ONLY )."
  },*/
  {NULL}  /* Sentinel */
};

static PyTypeObject coolsole_FormattedOutputType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "coolsole.FormattedOutput",/* tp_name */
  sizeof(coolsole_FormattedOutput),             /* tp_basicsize */
  0,                         /* tp_itemsize */
  (destructor)deallocate_formatted_output, /* tp_dealloc */
  0,                         /* tp_print */
  0,                         /* tp_getattr */
  0,                         /* tp_setattr */
  0,                         /* tp_reserved */
  0,                         /* tp_repr */
  0,                         /* tp_as_number */
  0,                         /* tp_as_sequence */
  0,                         /* tp_as_mapping */
  0,                         /* tp_hash  */
  0,                         /* tp_call */
  0,                         /* tp_str */
  0,                         /* tp_getattro */
  0,                         /* tp_setattro */
  0,                         /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT |
  Py_TPFLAGS_BASETYPE,   /* tp_flags */
  "Base class for FormattedOutput control.",           /* tp_doc */
  0,                         /* tp_traverse */
  0,                         /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  coolsole_formatted_output_methods,             /* tp_methods */
  coolsole_formatted_output_members,             /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)init_formatted_output, /* tp_init */
  0,                         /* tp_alloc */
  allocate_formatted_output, /* tp_new */
};

static PyMethodDef CoolsoleMethods[2] = {
  {"say_hello", say_hello, METH_VARARGS, "Greet somebody."},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef coolsole_module = {
  PyModuleDef_HEAD_INIT,
  "coolsole",   /* name of module */
  NULL,      /* module documentation, may be NULL */
  -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
  CoolsoleMethods
};
#endif