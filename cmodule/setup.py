#!/usr/bin/env python

from distutils.core import setup, Extension

mymodule = Extension('foo',
                    sources = ['foo.c'])

setup (name = 'Foo',
       version = '1.0',
       description = 'Say hello',
       ext_modules = [mymodule])
