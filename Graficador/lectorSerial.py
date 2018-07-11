import serial, time, matplotlib, numpy as np, matplotlib.pyplot as plotter
from matplotlib.animation import FuncAnimation

#######################
#       Globales      #
#######################
#GRAFICO#
fig ,grafico = plotter.subplots()
grf, =plotter.plot([],[],color='blue',marker='.',linewidth=0, animated=True)
#PUERTO#
#Serial.println(String(T)+","+String(Wl)+","+String(Wr))#
PUERTO="/dev/ttyACM0"
#POR DEFINIR#
RANGOX=250
RANGOY=250
R=1.6
L=13.1
X=Y=O=TK=Tk=arduino=Wl=Wr=0
#DATOS A GRAFICAR
datosX, datosY = [], []

#######################
#Configuracion grafico#
#######################

#configuracion inicial del grafico
def init():
    grafico.set_xlim(-RANGOX, RANGOX)
    grafico.set_ylim(-RANGOY, RANGOY)
    grafico.set_title("Posicion")
    grafico.set_xlabel("Coordenadas X")
    grafico.set_ylabel("Coordenadas Y")
    return grf,

#Lee Arduino y grafica
def update(frame):
    global TK, Tk, X, Y
    leerArduino()
    calcular_angulo(Wr,Wl)
    calcular_coordenadas(Wr,Wl)
    datosX.append(X)
    datosY.append(Y)
    grf.set_data(datosX, datosY)
    Tk=TK
    return grf,

#######################
#  obtenerVariables   #
#######################

#Lectura de arduino
def leerArduino():
    global arduino
    lectura = arduino.readline()
    if "," in lectura:
        if lectura.count(",") == 2:
            return formatearVariables(lectura[:-2])
        else:
            leerArduino()
    return


#Formato para graficar
def formatearVariables(linea):
    global TK,Wl,Wr
    print (linea)
    coma=linea.index(",")
    TK=float(linea[:coma])/1000
    linea=linea[coma+1:]
    coma=linea.index(",")
    #corregir#
    Wl=float(linea[:coma])
    Wr=float(linea[coma+1:])
    return

#######################
# Calculo de Variables#
#######################

#calcula angulo
def calcular_angulo(Wr, Wl):
    global O,TK,Tk
    O += (R/L)*(Wr - Wl)*(TK-Tk)
    return
#calcula posicion X Y
def calcular_coordenadas(Wr, Wl):
    global X,Y
    X +=(R*0.5)*np.cos(O)*(Wr + Wl)*(TK-Tk)
    Y +=(R*0.5)*np.sin(O)*(Wr + Wl)*(TK-Tk)
    return

#######################
#         Main        #
#######################
def main():
    global arduino
    arduino = serial.Serial(PUERTO, 9600)
    ani = FuncAnimation(fig, update,init_func=init, blit=True)
    plotter.show()
    return

if __name__ == "__main__":
    main()
    raw_input()
