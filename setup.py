#!/usr/bin/python
# -*- coding: utf-8 -*-
# vin: ts=4 sw=4 et ft=python

from distutils.core import setup
import os, sys
import py2exe

from glob import glob

data_files = [("Microsoft.VC90.CRT", glob(r'C:\Program Files\Microsoft Visual Studio 9.0\VC\redist\x86\Microsoft.VC90.CRT\*.*'))]

setup(name='RISE',
      description='Secure sharing and collaboration',
      version='0.0.30',

      console=['frontend.py'],

      options={
          'py2exe': {
              'packages': ['encodings'],
              'includes': ['gobject', 'webkit']
          }
      })
