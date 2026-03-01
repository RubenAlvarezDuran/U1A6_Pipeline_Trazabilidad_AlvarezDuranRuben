# Checklist de reproducibilidad — U1A6
# Ruben Alvarez Duran - Mecatronica U8

## 1) Orden de ejecución (qué ejecutar primero)
1. Conectar ESP32 por USB o wifi.
2. Flashear firmware desde `code/ESP32/U1A4C_Alvarez Duran_Ruben.cpp`.
3. Verificar transmisión (Serial Monitor o debug de Node-RED).
4. Importar y desplegar flow Node-RED (`code/node-red/U1A4C_Alvarez Duran_Ruben.json`).
5. Iniciar dashboard y registro CSV.
6. Ejecutar calibración (min/max/umbral) y guardar parámetros.

## 2) Parámetros a configurar
- Muestreo: 50 Hz
- Serial:
  - Puerto: COM3
  - Baud: 115200
- Payload: `ts_ms,s1,s2,...`
- Registro: ruta/salida de CSV (guardar en `data/raw/U1A4C_Alvarez Druan_Ruben.csv`)

## 3) Qué se espera observar
- La gráfica del dashboard se actualiza en tiempo real (ej. cada 0.5 s o continuo).
- El log muestra líneas con timestamp/seq y canales sin romper formato.
- Se guarda un CSV con ≥300 filas en `data/raw/U1A4C_Alvarez Druan_Ruben.csv`.

## 4) Verificación rápida
- Check 1: En dashboard, mover el sensor sobre blanco/negro y ver cambio claro en valores.
- Check 2: Abrir `data/raw/U1A6_sample.csv` y confirmar ≥300 filas + columnas correctas.