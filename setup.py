#!/usr/bin/python
# -*- coding: utf-8 -*-
# vin: ts=4 sw=4 et ft=python

from distutils.core import setup
import os, sys
import py2exe

from glob import glob

data_files = [("Microsoft.VC90.CRT", glob(r'C:\Program Files\Microsoft Visual Studio 9.0\VC\redist\x86\Microsoft.VC90.CRT\*.*'))]

missing_dll = ['libgtk-3-0.dll',
               'libgdk-3-0.dll',
               'libatk-1.0-0.dll',
               'libcairo-gobject-2.dll',
               'libgdk_pixbuf-2.0-0.dll',
               'libjpeg-8.dll',
               'libpango-1.0-0.dll',
               'libpangocairo-1.0-0.dll',
               'libpangoft2-1.0-0.dll',
               'libpangowin32-1.0-0.dll',
               'libgnutls-26.dll',
               'libglib-2.0-0.dll',
               'libwebkitgtk-3.0-0.dll',
               'libgirepository-1.0-1.dll',
               'libglib-2.0-0.dll',
               'libffi-6.dll',
               'libgobject-2.0-0.dll'
               ]

setup(name='RISE',
      description='Secure sharing and collaboration',
      version='0.0.30',

      windows=['frontend.py'],

      options={
          'py2exe': {
              'packages': ['gi'],
              'includes': ['gi'],
              'dll_excludes': missing_dll
          }
      })
