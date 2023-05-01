import PySimpleGUI as sg
import serial

sg.theme('DarkAmber')
layout = [ [sg.Text('ソナーシステムver0.1')],
           [sg.Button('索敵', key='read')],
           [sg.Text('Arduinoのポート'), sg.Combo(('/dev/ttyUSB0', '/dev/ttyUSB1', 'COM9', 'COM8', 'COM7', 'COM6', 'COM5','COM4', 'COM3', 'COM2', 'COM1', 'COM0'),  default_value="COM3", key='port')]
           # [sg.Output(size=(100,100))]
          ]
window = sg.Window('高専演習', layout, size = (500, 500))
ser = False
while True:
    event, values = window.read()
    if event == sg.WIN_CLOSED:
        break

    if event == 'read':
        try:
            ser = serial.Serial(values['port'], 9600, timeout=0.1)
        except:
            ser = False
        while ser:
            buf = ser.readline().decode()
            if 'AD' in buf:
                print(buf)
            else:
                ser.write(b's')
            if '180/' in buf:
                while not (ser.readline().decode() in 'q'):
                    ser.write(b'q')
                break

window.close()    
