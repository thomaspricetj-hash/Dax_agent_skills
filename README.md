# DAX Bionic Skill

Bionic Skill for DAX Cognitive Agent with LLM Backbone

## Overview
DAX Bionic Skill integrates DAX memory architecture with LLM inference for a desktop CLI agent that mirrors Bionic capabilities while using DAX memory, weaveformer design, and cognitive tools.

## Core Components
- DAX Memory Vortexes
- WeaveContext / GridState / ClusterState
- PatternWeightedMemory & WeightEvolutionGraph
- Cognitive Tool Manager
- LLM Backbone: Muse-Glimmer-30B-KQuant-17GB-Q4_K_M.gguf
- Interactive CLI agent with tool calls and micro-agents

## Features
- Persistent DAX memory with checkpoint save/load
- Real-time learning loop with training datasets
- Interactive chat mode with code/chat teaching
- Self-healing logic and cognitive tool routing
- REST API and CLI interface
- AddressSanitizer / UBSan validated builds

go into dax_skills and modifie the manifest.json to use your model directory


