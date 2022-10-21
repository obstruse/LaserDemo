#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Multihypocycloid
# GNU Radio version: 3.10.1.1

from packaging.version import Version as StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from PyQt5 import Qt
from gnuradio import qtgui
import sip
from gnuradio import analog
from gnuradio import audio
from gnuradio import blocks
from gnuradio import gr
from gnuradio.filter import firdes
from gnuradio.fft import window
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.qtgui import Range, RangeWidget
from PyQt5 import QtCore



from gnuradio import qtgui

class multihypocycloid(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Multihypocycloid", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Multihypocycloid")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "multihypocycloid")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.rotate = rotate = .1
        self.frequency1 = frequency1 = 200
        self.b = b = 2
        self.a = a = 5
        self.volume = volume = .7
        self.samp_rate = samp_rate = 48000
        self.frequency2 = frequency2 = ((a/b) -1)*frequency1+ rotate

        ##################################################
        # Blocks
        ##################################################
        self._volume_range = Range(0, 10, .1, .7, 200)
        self._volume_win = RangeWidget(self._volume_range, self.set_volume, "'volume'", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_grid_layout.addWidget(self._volume_win, 4, 0, 1, 1)
        for r in range(4, 5):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._b_range = Range(1, 20, 1, 2, 200)
        self._b_win = RangeWidget(self._b_range, self.set_b, "'b'", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_grid_layout.addWidget(self._b_win, 1, 0, 1, 1)
        for r in range(1, 2):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._a_range = Range(1, 20, 1, 5, 200)
        self._a_win = RangeWidget(self._a_range, self.set_a, "'a'", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_grid_layout.addWidget(self._a_win, 0, 0, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._rotate_range = Range(0, 10, .1, .1, 200)
        self._rotate_win = RangeWidget(self._rotate_range, self.set_rotate, "'rotate'", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_grid_layout.addWidget(self._rotate_win, 5, 0, 1, 1)
        for r in range(5, 6):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
            10000, #size
            "", #name
            1, #number of inputs
            None # parent
        )
        self.qtgui_const_sink_x_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0.set_y_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(True)
        self.qtgui_const_sink_x_0.enable_grid(False)
        self.qtgui_const_sink_x_0.enable_axis_labels(True)

        self.qtgui_const_sink_x_0.disable_legend()

        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
            "red", "red", "red", "red", "red"]
        styles = [1, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [-1, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.qwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_const_sink_x_0_win, 2, 0, 1, 1)
        for r in range(2, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_sub_xx_0_0 = blocks.sub_ff(1)
        self.blocks_multiply_xx_0_0_0_1_1 = blocks.multiply_vff(1)
        self.blocks_multiply_xx_0_0_0_1_0_0 = blocks.multiply_vff(1)
        self.blocks_multiply_xx_0_0_0_1_0 = blocks.multiply_vff(1)
        self.blocks_multiply_xx_0_0_0_1 = blocks.multiply_vff(1)
        self.blocks_float_to_complex_0 = blocks.float_to_complex(1)
        self.blocks_delay_0_0 = blocks.delay(gr.sizeof_float*1, int((samp_rate/frequency2)/4))
        self.blocks_delay_0 = blocks.delay(gr.sizeof_float*1, int((samp_rate/frequency1)/4))
        self.blocks_complex_to_float_0_0 = blocks.complex_to_float(1)
        self.blocks_add_xx_0_0_0 = blocks.add_vff(1)
        self.audio_sink_1_0 = audio.sink(samp_rate, '', True)
        self.analog_sig_source_x_0_1_0 = analog.sig_source_f(samp_rate, analog.GR_SQR_WAVE, frequency1/20, 10, -5, 0)
        self.analog_sig_source_x_0_1 = analog.sig_source_f(samp_rate, analog.GR_SQR_WAVE, frequency1/10, 10, -5, 0)
        self.analog_sig_source_x_0_0 = analog.sig_source_f(samp_rate, analog.GR_COS_WAVE, frequency2, 1, 0, 0)
        self.analog_sig_source_x_0 = analog.sig_source_f(samp_rate, analog.GR_COS_WAVE, frequency1, 1, 0, 0)
        self.analog_const_source_x_0_0_1_1 = analog.sig_source_f(0, analog.GR_CONST_WAVE, 0, 0, a-b)
        self.analog_const_source_x_0_0_1_0_0 = analog.sig_source_f(0, analog.GR_CONST_WAVE, 0, 0, b)
        self.analog_const_source_x_0_0_1_0 = analog.sig_source_f(0, analog.GR_CONST_WAVE, 0, 0, b)
        self.analog_const_source_x_0_0_1 = analog.sig_source_f(0, analog.GR_CONST_WAVE, 0, 0, a-b)
        self.analog_agc_xx_0 = analog.agc_cc(1/samp_rate, volume, .01)
        self.analog_agc_xx_0.set_max_gain(10)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_agc_xx_0, 0), (self.blocks_complex_to_float_0_0, 0))
        self.connect((self.analog_agc_xx_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.analog_const_source_x_0_0_1, 0), (self.blocks_multiply_xx_0_0_0_1, 1))
        self.connect((self.analog_const_source_x_0_0_1_0, 0), (self.blocks_multiply_xx_0_0_0_1_0, 0))
        self.connect((self.analog_const_source_x_0_0_1_0_0, 0), (self.blocks_multiply_xx_0_0_0_1_0_0, 0))
        self.connect((self.analog_const_source_x_0_0_1_1, 0), (self.blocks_multiply_xx_0_0_0_1_1, 1))
        self.connect((self.analog_sig_source_x_0, 0), (self.blocks_delay_0, 0))
        self.connect((self.analog_sig_source_x_0, 0), (self.blocks_multiply_xx_0_0_0_1, 0))
        self.connect((self.analog_sig_source_x_0_0, 0), (self.blocks_delay_0_0, 0))
        self.connect((self.analog_sig_source_x_0_0, 0), (self.blocks_multiply_xx_0_0_0_1_0, 1))
        self.connect((self.analog_sig_source_x_0_1, 0), (self.blocks_add_xx_0_0_0, 0))
        self.connect((self.analog_sig_source_x_0_1_0, 0), (self.blocks_sub_xx_0_0, 2))
        self.connect((self.blocks_add_xx_0_0_0, 0), (self.blocks_float_to_complex_0, 0))
        self.connect((self.blocks_complex_to_float_0_0, 0), (self.audio_sink_1_0, 0))
        self.connect((self.blocks_complex_to_float_0_0, 1), (self.audio_sink_1_0, 1))
        self.connect((self.blocks_delay_0, 0), (self.blocks_multiply_xx_0_0_0_1_1, 0))
        self.connect((self.blocks_delay_0_0, 0), (self.blocks_multiply_xx_0_0_0_1_0_0, 1))
        self.connect((self.blocks_float_to_complex_0, 0), (self.analog_agc_xx_0, 0))
        self.connect((self.blocks_multiply_xx_0_0_0_1, 0), (self.blocks_add_xx_0_0_0, 1))
        self.connect((self.blocks_multiply_xx_0_0_0_1_0, 0), (self.blocks_add_xx_0_0_0, 2))
        self.connect((self.blocks_multiply_xx_0_0_0_1_0_0, 0), (self.blocks_sub_xx_0_0, 1))
        self.connect((self.blocks_multiply_xx_0_0_0_1_1, 0), (self.blocks_sub_xx_0_0, 0))
        self.connect((self.blocks_sub_xx_0_0, 0), (self.blocks_float_to_complex_0, 1))
        self.connect((self.blocks_throttle_0, 0), (self.qtgui_const_sink_x_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "multihypocycloid")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_rotate(self):
        return self.rotate

    def set_rotate(self, rotate):
        self.rotate = rotate
        self.set_frequency2(((self.a/self.b) -1)*self.frequency1+ self.rotate)

    def get_frequency1(self):
        return self.frequency1

    def set_frequency1(self, frequency1):
        self.frequency1 = frequency1
        self.set_frequency2(((self.a/self.b) -1)*self.frequency1+ self.rotate)
        self.analog_sig_source_x_0.set_frequency(self.frequency1)
        self.analog_sig_source_x_0_1.set_frequency(self.frequency1/10)
        self.analog_sig_source_x_0_1_0.set_frequency(self.frequency1/20)
        self.blocks_delay_0.set_dly(int((self.samp_rate/self.frequency1)/4))

    def get_b(self):
        return self.b

    def set_b(self, b):
        self.b = b
        self.set_frequency2(((self.a/self.b) -1)*self.frequency1+ self.rotate)
        self.analog_const_source_x_0_0_1.set_offset(self.a-self.b)
        self.analog_const_source_x_0_0_1_0.set_offset(self.b)
        self.analog_const_source_x_0_0_1_0_0.set_offset(self.b)
        self.analog_const_source_x_0_0_1_1.set_offset(self.a-self.b)

    def get_a(self):
        return self.a

    def set_a(self, a):
        self.a = a
        self.set_frequency2(((self.a/self.b) -1)*self.frequency1+ self.rotate)
        self.analog_const_source_x_0_0_1.set_offset(self.a-self.b)
        self.analog_const_source_x_0_0_1_1.set_offset(self.a-self.b)

    def get_volume(self):
        return self.volume

    def set_volume(self, volume):
        self.volume = volume
        self.analog_agc_xx_0.set_reference(self.volume)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_agc_xx_0.set_rate(1/self.samp_rate)
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0_0.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0_1.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0_1_0.set_sampling_freq(self.samp_rate)
        self.blocks_delay_0.set_dly(int((self.samp_rate/self.frequency1)/4))
        self.blocks_delay_0_0.set_dly(int((self.samp_rate/self.frequency2)/4))
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)

    def get_frequency2(self):
        return self.frequency2

    def set_frequency2(self, frequency2):
        self.frequency2 = frequency2
        self.analog_sig_source_x_0_0.set_frequency(self.frequency2)
        self.blocks_delay_0_0.set_dly(int((self.samp_rate/self.frequency2)/4))




def main(top_block_cls=multihypocycloid, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.show()

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()

        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    qapp.exec_()

if __name__ == '__main__':
    main()
