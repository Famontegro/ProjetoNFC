import serial
import time
import pywhatkit
from datetime import datetime

arduino = serial.Serial("COM9", 9600) //Precisa ajustar para a porta compativel
time.sleep(2)

destinatario = "+5511999999999" //Numero de alguem especifico
alerta_enviado = False

while True:
    if arduino.in_waiting:
        mensagem = arduino.readline().decode().strip()
        print(mensagem)

        if mensagem == "ACESSO LIBERADO!":
            alerta_enviado = False

        elif mensagem == "ALERTA_NIVEL_3" and not alerta_enviado:
            horario = datetime.now().strftime("%d/%m/%Y %H:%M:%S")

            texto = f"🚨 ALERTA! Três tentativas de acesso inválido!\nHorário: {horario}"

            pywhatkit.sendwhatmsg_instantly(destinatario, texto)

            alerta_enviado = True
