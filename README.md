# U1A6 — Bitácora Técnica: Trazabilidad del pipeline sensor→PC→dashboard→registro
# Ruben Alvarez Duran - Mecatronica 8U

## 1) Descripción breve del pipeline
Este repositorio documenta un pipeline reproducible para adquirir lecturas de sensores (ADC), enviarlas por telemetría (USB/Serial o MQTT), visualizarlas en un dashboard y registrar muestras en CSV para trazabilidad.

**Flujo general:**
Sensor(es) → ESP32 (ADC + empaquetado) → Telemetría (USB/Serial o MQTT) → PC/Node-RED dashboard → Registro CSV → (opcional) cálculo de calibración (min/max/umbral).

## 2) Estructura del repositorio
- `code/`: firmware ESP32 + flow Node-RED + utilidades de PC  
- `data/raw/`: datos crudos (CSV de muestra con ≥300 filas)  
- `data/processed/`: parámetros de calibración (min/max/umbral por canal)  
- `docs/`: evidencias (capturas, diagramas, notas)  
- `bitacora.md`: bitácora con entradas fechadas (decisiones, incidentes, evidencias)  
- `metadata_pipeline.md`: metadatos del pipeline (sensor, Hz, payload, SO, dependencias)  
- `CHANGELOG.md`: versiones y cambios (v0.1 / v0.2)  
- `repro_checklist.md`: checklist paso a paso para reproducir el resultado

## 3) Requisitos
### Hardware
- ESP32 DevKit
- Sensores infrarrojos (ej. TCRT5000) conectados a ADC

### Software (PC)
- Node-RED
- Nodos: `node-red-dashboard` (si usas UI), `node-red-node-serialport` (si usas USB/Serial)
- (Opcional) MQTT broker (Mosquitto) y nodos MQTT

## 4) Cómo ejecutar (orden recomendado)
1. **Firmware:** cargar el sketch de `code/esp32/` al ESP32.
2. **Telemetría:** conectar el ESP32 por USB y verificar salida de datos (Serial Monitor o debug).
3. **Dashboard:** importar el flow en Node-RED (`code/nodered/flows.json`) y desplegar.
4. **Registro:** activar el guardado a CSV (por flow o script de `code/pc/`).
5. **Calibración:** obtener min/max/umbral y guardar en `data/processed/calibration_params.json`.
6. **Validación:** confirmar que hay ≥300 muestras en `data/raw/U1A6_sample.csv`.

## 5) Salida esperada (qué debe verse)
- Dashboard actualiza en tiempo casi real.
- Se registran datos en CSV con timestamp/seq y canales (mínimo 2).
- Se generan parámetros de calibración (min/max/umbral) por canal.
- Evidencias en `/docs/` (mínimo 3 capturas).

## 6) Evidencias del repo
Ver carpeta `docs/`

## 7) Versionado
- `v0.1`: telemetría funcionando
- `v0.2`: dashboard + calibración funcionando  
Ver detalles en `CHANGELOG.md`.

## 8) Licencia / Notas
Reporte académico. No se incluyen archivos pesados; solo un CSV sample y documentación para regenerar el resto.