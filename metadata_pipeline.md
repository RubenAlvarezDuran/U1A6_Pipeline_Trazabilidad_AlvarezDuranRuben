# Metadatos del pipeline (U1A6)
# Ruben Alvarez Duran - Mecatronica U8

## 1) Sensor / módulo y señal
- Sensor infrarrojo — módulos x2
- Tipo de señal: Analógica a ADC (voltaje proporcional a reflectancia)
- Canales: s1..s2

## 2) Frecuencia de muestreo
- Frecuencia objetivo: 50 Hz
- Estrategia: muestreo periódico en loop con control por `millis()` (o timer)

## 3) Canal de telemetría y estructura del mensaje
### Opción usada: USB/Serial y wifi
- Medio: USB/Serial y wifi
- Baud rate: 115200
- Formato de payload (CSV por línea):
  `ts_ms,s1,s2`

*(Si usas MQTT, agrega aquí:)*
### MQTT
- Broker: broker.hivemq.com
- Topic: `meca/calibrar/control`
- Payload: JSON con `ts_ms` y `s1..s2`

## 4) Plataforma
- Microcontrolador: ESP32 DevKit
- PC: Windows 11
- Conexión: USB directo

## 5) Herramienta de dashboard y dependencias
- Dashboard: Node-RED
- Nodos usados:
  - `node-red-node-serialport`
  - `node-red-dashboard` (si hay UI)
  - (opc.) `node-red-node-ui-table`, `node-red-node-file` o equivalente para CSV
- Archivos clave:
  - Flow: `code/node-red`
  - CSV sample: `data/raw/U1A4C_Alvarez Duran_Ruben`