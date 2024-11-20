import serial
import paho.mqtt.client as mqtt

# Configurações da porta serial e MQTT
arduino_port = "/dev/ttyACM0"
baud_rate = 9600
mqtt_broker = "test.mosquitto.org"
mqtt_topic = "meu/topico"
port = 1883
client_id = "meuCliente"

# Configura a conexão serial
arduino = serial.Serial(arduino_port, baud_rate)

# Configura o cliente MQTT
client = mqtt.Client(client_id)
client.connect(mqtt_broker, port, 60)

def on_message(client, userdata, msg):
    # Envia mensagem recebida do MQTT para o Arduino
    print(f"Mensagem recebida: {msg.payload.decode()}")
    arduino.write(msg.payload)

# Função chamada quando o cliente se conecta ao broker
def on_connect(client, userdata, flags, rc):
    print("Conectado com código resultante " + str(rc))
    # Assine o tópico que você quer ouvir
    client.subscribe(mqtt_topic)

client.on_connect = on_connect
client.on_message = on_message
client.subscribe(mqtt_topic)
client.loop_start()

# Lê dados do Arduino e publica no MQTT
try:
    while True:
        if arduino.in_waiting > 0:
            data = arduino.readline().decode('utf-8').strip()
            print(f"Mensagem do Arduino: {data}")
            client.publish(mqtt_topic, data)
except KeyboardInterrupt:
    print("Encerrando...")
    arduino.close()
    client.loop_stop()
