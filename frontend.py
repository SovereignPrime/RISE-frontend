# -*- coding: utf-8 -*-
#!/usr/bin/env python

import gtk
import webkit

gtk.gdk.threads_init()

class browser():
    def __init__(self, uri):
        view = webkit.WebView()
        viewMF = view.get_main_frame()
        sw = gtk.ScrolledWindow()
        sw.add(view)
        win = gtk.Window(gtk.WINDOW_TOPLEVEL)
        win.connect('destroy', quit)
        win.set_default_size(600, 400)
        win.add(sw)
        win.show_all()
        viewMF.load_uri(uri)
browser('http://localhost:8000')
gtk.main()
