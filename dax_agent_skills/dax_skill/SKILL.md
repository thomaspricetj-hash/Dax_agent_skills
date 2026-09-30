# DAX Agent Skill for Bionic

Integrates Weaveformer DAX design into LM Studio Bionic.

## Capabilities
- Persistent memory via WeaveContext, Journal, Diary
- LLM backbone: Muse-Glimmer-30B GGUF
- Micro-agents: code, test, refactor, self-healing
- Build error logging to DAX Journal

## Commands
- `dax chat <prompt>` – chat with DAX memory
- `dax train <dataset.csv>` – train specialists
- `dax build` – run CMake build and log errors
- `dax workspace` – list workspace files
- `dax open <path>` – open file in side editor and log

## Setup
Model path: `C:/Users/thoma/OneDrive/Desktop/New folder (7)/weaveformer/dax-cpp/Muse-Glimmer-30B-KQuant-17GB-Q4_K_M.gguf`
Checkpoint: `C:/Users/thoma/.lmstudio/scratchpads/dt/model_coding_start.ckpt`
