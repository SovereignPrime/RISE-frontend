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
def generate_data_files(prefix, tree, file_filter=None):
    """
    Walk the filesystem starting at "prefix" + "tree", producing a list of files
    suitable for the data_files option to setup(). The prefix will be omitted
    from the path given to setup(). For example, if you have

        C:\Python26\Lib\site-packages\gtk-2.0\runtime\etc\...

    ...and you want your "dist\" dir to contain "etc\..." as a subdirectory,
    invoke the function as

        generate_data_files(
            r"C:\Python26\Lib\site-packages\gtk-2.0\runtime",
            r"etc")

    If, instead, you want it to contain "runtime\etc\..." use:

        generate_data_files(
            r"C:\Python26\Lib\site-packages\gtk-2.0",
            r"runtime\etc")

    Empty directories are omitted.

    file_filter(root, fl) is an optional function called with a containing
    directory and filename of each file. If it returns False, the file is
    omitted from the results.
    """
    data_files = []
    for root, dirs, files in os.walk(os.path.join(prefix, tree)):
        to_dir = os.path.relpath(root, prefix)

        if file_filter is not None:
            file_iter = (fl for fl in files if file_filter(root, fl))
        else:
            file_iter = files

        data_files.append((to_dir, [os.path.join(root, fl) for fl in file_iter]))

    non_empties = [(to, fro) for (to, fro) in data_files if fro]

    return non_empties

setup(name='RISE',
      description='Secure sharing and collaboration',
      version='0.0.30',

      windows=['frontend.py'],
      data_files = (
          # Use the function above...
          generate_data_files(GTK_RUNTIME_DIR, GTK_THEME_DEFAULT) +
          generate_data_files(GTK_RUNTIME_DIR, GTK_THEME_WINDOWS) +
          generate_data_files(GTK_RUNTIME_DIR, GTK_ICONS) +

          # ...or include single files manually
          [
              (GTK_GTKRC_DIR, [
                  os.path.join(GTK_RUNTIME_DIR,
                               GTK_GTKRC_DIR,
                               GTK_GTKRC)
              ]),

                        (GTK_WIMP_DIR, [
                            os.path.join(
                                GTK_RUNTIME_DIR,
                                GTK_WIMP_DIR,
                                GTK_WIMP_DLL)
                        ])
                    ]
                ),
      options={
          'py2exe': {
              'packages': ['gi', 'gnome'],
              'includes': ['gi', 'gnome'],
              'dll_excludes': missing_dll
          }
      })
