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
  if(self->__cpp_object) {
    delete self->__cpp_object;
  }
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
  self->__cpp_object = nullptr;//new Coolsole::FormattedOutput();
  return (PyObject *)self;
}



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
  0,             /* tp_methods */
  0,             /* tp_members */
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

static PyMethodDef CoolsoleMethods[] = {
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