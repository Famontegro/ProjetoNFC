import serial
import time
import pywhatkit
from datetime import datetime

arduino = serial.Serial("COM9", 9600)
time.sleep(2)

destinatario = "+5511999910716"
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