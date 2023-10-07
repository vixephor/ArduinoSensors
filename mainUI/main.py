from PyQt5 import QtWidgets
from PyQt5 import uic
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import  QIODevice
from pyqtgraph import PlotWidget
import pyqtgraph as pg
import sys


app = QtWidgets.QApplication([])
ui = uic.loadUi("untitled.ui")
ui.setWindowTitle("MAN_GUI")

serial = QSerialPort()
serial.setBaudRate(115200)
portList = []
ports = QSerialPortInfo.availablePorts()
for port in ports:
    portList.append(port.portName())

ui.ComL.addItems(portList)

listX = []
for x in range(100): listX.append(x)

listY = []
for x in range(100): listY.append(x)


def OnRead():
    rx = serial.readLine()
    rxs = str(rx, 'utf-8').strip()
    data = rxs.split(' ')
    print(data)
    global listX
    global listY
    ui.tempereture_value.setText(data[0])
    ui.graphCO2.plot(listX, listY)

def OnOpen():
    serial.setPortName(ui.ComL.currentText())
    serial.open(QIODevice.ReadWrite)


def OffClose():
    serial.close( )

def test(val):
    print("TEST")
    print(val)

def SerialSend(data): #список инт
    txs=""
    for val in data:
        txs+=str(val)
        txs+= ' '
    txs = txs[:-1]
    txs+=';'
    serial.write(txs.encode())

def controle():
    vals = [10, 11, 12]
    SerialSend(vals)
serial.readyRead.connect(OnRead)
ui.OPEN_COM.clicked.connect(OnOpen)
ui.CLOSE_COM.clicked.connect(OffClose)
ui.TEST.clicked.connect(controle)
ui.TEST2.stateChanged.connect(test)



ui.show()
app.exec()



