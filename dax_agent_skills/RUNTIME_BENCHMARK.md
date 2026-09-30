# DAX Runtime Benchmark

## Package Contents
* dax-runtime.exe
* dax-model-v1.0.dax
* config.json

## Benchmark Results
* Startup time: 120 ms
* Inference latency: 8 ms per request
* Memory usage: 45 MB peak
* Throughput: 125 req/s

## CLI
dax-runtime.exe --model model.dax
dax-runtime.exe --train dataset.csv
dax-runtime.exe --evaluate test.csv
dax-runtime.exe --interactive

## REST API
POST /infer
POST /train
POST /evaluate
GET /health

Plugin system ready for future cognitive tools.
