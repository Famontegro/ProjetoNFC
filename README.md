# ProjetoNFC

### Sobre:
Projeto de NFC feito durante o segundo semestre do curso de Engenharia da Computação na feira de projetos que ocorreu dia 05/11/26 na faculdade **Universidade São Francisco (USF) Campus Bragança Paulista**. Varios grupos participaram, incluindo outros cursos voltados a Engenharia. 

Também fizemos um site para o nosso projeto que da para acessa-lo apertando [aqui](https://famontegro.github.io/Site-emp-nfc/) e o repositório do GitHub acessando [aqui](https://github.com/Famontegro/Site-emp-nfc)

---

### Participantes do Projeto:
1. Rafael Montenegro
2. João Cesar
3. Chris Sousa
4. João Pedro
5. Náiade Peluso
6. Daniel Tenorio
7. Gabrielle Libralão

---

### Componentes utilizados:
O projeto consiste em um circuito que possui três principais componentes, que eles são:

- Módulo RFID-RC522
- Arduino UNO R3
- Servo motor

Nele também contem dois LEDs, dois resistores de 220Ω, um buzzer, um botão, varios jumpers e cartões NFC.

---

### Funcionamento:
Colocamos todos os componentes em uma maquete feita com papel paraná, nela tem um porta, furos para passar os fios que servem para ligar os componentes juntos e uma base. O RFID fica no lado de fora, e opera de uma maneira que ao aproximar um cartão NFC compatível ele emite um sinal para o Arduino. Se o cartão for autorizado, o Arduino faz o servo motor faz o movimento de 90 graus para abrir a porta, depois volta para o 0 fechando-a e acende o LED verde ate a porta fechar, se não for autorizado, o LED vermelho acende por um curto período de tempo e apita o buzzer brevemente, esse é o **NIVEL 1** de segurança, se novamente o acesso der negado, aciona o **NIVEL 2** de segurança, nele o buzzer apita mais tempo e o LED vermelho acende novamente até o buzzer parar, já no **NÍVEL 3**, aciona o alarme e envia uma mensagem no __Whatsapp__ de alguém especifico, o alarme só vai ser desativado quando alguém apertar o botão na porta D2.

---

### Imagens do nosso projeto:
![Grupo](<Imagens de NFC/WhatsApp Image 2026-11-05 at 21.38.08.jpeg>)
![NFC](<Imagens de NFC/WhatsApp Image 2026-11-06 at 19.58.03.jpeg>)
![NFC](<Imagens de NFC/WhatsApp Image 2026-11-06 at 19.58.03 (1).jpeg>)

---

### Vale citar:
Nos tentamos fazer outro projeto junto com o de NFC, mas acabou que ele não funcionou por falta de um componente, ele foi o EMP e posteriormente de EMFI. O EMP é um pulso eletromagnético que distorce ondas eletromagnéticas, causando perturbações em circuitos eletrónicos. O EMFI é basicamente um EMP mas mais concentrado em um ponto, então, mais seguro para apresentar em um trabalho educacional. Nós queríamos mostrar eles funcionando no Módulo RFID, que em teoria, ele apresentaria uma falha e faria qualquer cartão acionar o servo motor. Nos conseguimos enrolar as bobinas e tentamos fazer de várias maneiras, porém, a falta de um transistor bem especifico deixou difícil ou até sem chance de nós o substituir.

**Imagem do EMFI:**

