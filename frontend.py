#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from gi.repository import Gtk as gtk, Gdk as gdk, GLib
from gi.repository.WebKit import WebView

GLib.threads_init()


class browser(WebView):
    def __init__(self, uri):
        WebView.__init__(self)
        viewMF = self.get_main_frame()
        sw = gtk.ScrolledWindow()
        sw.add(self)
        self.win = gtk.Window()
        self.win.connect('destroy', quit)
        self.connect('download-requested', self._download_destination_cb)
        self.win.set_default_size(600, 400)
        self.win.add(sw)
        self.win.show_all()
        viewMF.load_uri(uri)

    def _download_destination_cb(self, view, download):
        """docstring for _download_destination_cb"""
        fc = gtk.FileChooserDialog(title="Save file as...", parent=None, buttons=(gtk.STOCK_SAVE, gtk.ResponseType.OK,gtk.STOCK_CANCEL, gtk.ResponseType.CANCEL), action=gtk.FileChooserAction.SAVE)
        fc.set_default_response(gtk.ResponseType.OK)
        fname = download.get_suggested_filename()
        fc.set_current_name(fname)
        res = fc.run()
        if  res == gtk.ResponseType.OK:
            uri = fc.get_uri()
            download.set_destination_uri(uri)
        fc.destroy()
        return True

browser('http://localhost:8000')
gtk.main()
