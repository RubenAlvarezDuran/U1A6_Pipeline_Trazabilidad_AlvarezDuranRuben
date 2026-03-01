# CHANGELOG — U1A6 Pipeline Trazabilidad
# Ruben Alvarez Duran - Mecatronica U8

## v0.2 — Dashboard + calibración funcionando
- Se agregó cálculo/registro de parámetros de calibración (min/max/umbral) por canal.
- Se implementó envío estable por USB/Serial.
- Se habilitó guardado de dataset de muestra (≥300 filas) en `data/raw/U1A6_sample.csv`.
- Se documentó checklist de reproducibilidad y metadatos del pipeline.
- Se añadieron evidencias en `/docs/`.

## v0.1 — Telemetría funcionando
- Se integró dashboard (Node-RED) para visualizar canales en tiempo casi real.
- Se definió formato de payload con `timestamp/seq` + lecturas ADC por canal.
- Se implementó envío estable por wifi con MQTT.
- Se creó estructura base del repositorio y README inicial.
- Se verificó recepción en PC con datos consistentes.
- Se añadieron evidencias en `/docs/`.