#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from gi.repository import Gtk as gtk, Gdk as gdk, GLib
from gi.repository.WebKit import WebView
from subprocess import Popen
import os, time, sys

GLib.threads_init()


class browser(WebView):  # {{{1
    def __init__(self, uri):  # {{{2
        WebView.__init__(self)
        viewMF = self.get_main_frame()
        sw = gtk.ScrolledWindow()
        sw.add(self)
        self.win = gtk.Window(title="RISE")
        self.win.connect('delete-event', self.quit)
        self.connect('download-requested', self._download_destination_cb)
        self.win.set_default_size(600, 400)
        self.win.add(sw)
        self.win.show_all()
        self.backend = Popen(['start.cmd'])
        tmp = os.environ['TMP']
        while not os.path.isfile("%s\\rise.port" % tmp):
            time.sleep(1)
        viewMF.load_uri(uri)

    def _download_destination_cb(self, view, download):  # {{{2
        """docstring for _download_destination_cb"""
        fc = gtk.FileChooserDialog(title="Save file as...",
                                   parent=None,
                                   buttons=(gtk.STOCK_SAVE,
                                            gtk.ResponseType.OK,
                                            gtk.STOCK_CANCEL,
                                            gtk.ResponseType.CANCEL),
                                   action=gtk.FileChooserAction.SAVE)
        fc.set_default_response(gtk.ResponseType.OK)
        fname = download.get_suggested_filename()
        fc.set_current_name(fname)
        res = fc.run()
        if res == gtk.ResponseType.OK:
            uri = fc.get_uri()
            download.set_destination_uri(uri)
        fc.destroy()
        return True

    def quit(self, _v, _w):  # {{{2
        """docstring for quit"""
        self.backend.terminate()
        gtk.main_quit()

if __name__ == '__main__':  # {{{2
    browser('http://localhost:%s' % port)
    gtk.main()
