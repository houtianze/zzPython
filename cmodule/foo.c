#include <stdio.h>
#include <Python.h>

static PyObject *FooError;

static PyObject*
foo_bar(PyObject *self, PyObject *args) {
	const char *command;
	int sts;

	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;
	sts = printf("Hello, %s", command);
	PyErr_SetString(FooError, "Just an error");
	return Py_BuildValue("i", sts);
}

static PyMethodDef FooMethods[] = {
    {"bar",  foo_bar, METH_VARARGS,
     "Say hello to you."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initfoo(void)
{
	PyObject *m;

	m = Py_InitModule("foo", FooMethods);
	if (m == NULL)
		return;

	FooError = PyErr_NewException("foo.error", NULL, NULL);
	Py_INCREF(FooError);
	PyModule_AddObject(m, "error", FooError);
}

int
main(int argc, char *argv[])
{
	/* Pass argv[0] to the Python interpreter */
	Py_SetProgramName(argv[0]);

	/* Initialize the Python interpreter.  Required. */
	Py_Initialize();

	/* Add a static module */
	initfoo();
}
