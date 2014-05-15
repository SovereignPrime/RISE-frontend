#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from gi.repository import Gtk as gtk, Gdk as gdk, GLib
from gi.repository.WebKit import WebView
import os, time

GLib.threads_init()


class browser(WebView):
    def __init__(self, uri):
        WebView.__init__(self)
        viewMF = self.get_main_frame()
        sw = gtk.ScrolledWindow()
        sw.add(self)
        self.win = gtk.Window(title="RISE")
        self.win.connect('destroy', self.quit)
        self.connect('download-requested', self._download_destination_cb)
        self.win.set_default_size(600, 400)
        self.win.add(sw)
        self.win.show_all()
        viewMF.load_uri(uri)

    def _download_destination_cb(self, view, download):
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

    def quit(self):
        """docstring for quit"""
        gtk.main_quit()
        os.system('./rise_service stop')

if __name__ == '__main__':
    os.system('./rise_service start')
    while 'RISE_HTTP_PORT' not in os.environ:
        time.sleep(1)
    port = os.environ['RISE_HTTP_PORT']
    print port
    browser('http://localhost:%s' % port)
    gtk.main()
