# GGUF Compatibility Report – DAX WeaveFormer v1.0

## Executive Summary
DAX WeaveFormer uses graph-based, dynamic weight structures with persistent context, not static tensors. GGUF export feasibility is **Partial** – core numerical parameters can be mapped, but graph/state structures require custom metadata.

## 1. Persistent Model State Inventory

| Component | Type | Notes |
|-----------|------|-------|
| WeaveContext | struct | Holds shared_ptrs to GridState, ClusterState, LatticeState, ResonanceState, ZoomState + input_text, token_sequence |
| GridState | struct | points[vector<vector<float>>], edges, edge_weights, nodes |
| ClusterState | struct | clusters, cluster_info, clusters_with_weights |
| LatticeState | struct | nodes, edges, depth |
| ResonanceState | struct | resonance_values, events, amplitude, phase_offset |
| ZoomState | struct | scale_factor, zoom_factors, entropy_threshold |
| PatternWeightedMemory | class | linear_weights_, pattern_store, fast/slow memory |
| WeightEvolutionGraph | class | nodes, edges, clusters, delta histories |
| WeightScalingLayer | class | cluster_scales_ map<uint32_t, WeightScaleFactors> |
| PatternLifecycleEngine | class | patterns_, super_patterns_ |
| DerivativeSignatureEngine | class | signature_db_, pattern_db_ |
| ConsensusEngine | class | character_reputation_, history_ |
| CognitiveToolManager | class | tools_ vector<unique_ptr<CognitiveTool>> |

## 2. Trainable Parameters Inventory

* WeightScaleFactors.scale_factor : float
* PatternVector.weights : vector<float>
* PatternVector.micro_weights : vector<float>
* Linear weights in PatternWeightedMemory : vector<vector<float>>
* ResonanceState.resonance_amplitude, memory_decay : float
* LatticeState edge weights : float
* GridState edge_weights : float

**No traditional embedding matrices or transformer weights.**

## 3. Weight Structures

| Structure | Data type | Shape | Serialization |
|-----------|-----------|-------|---------------|
| WeightScaleFactors | float x2 | scalar | binary |
| WeightGraphNode.value | float | scalar | binary |
| WeightEdge.delta_change | float | scalar | binary |
| PatternVector.weights | float[] | [N] | vector binary |
| cluster_scales_ | map<uint32_t, WeightScaleFactors> | variable | map |

## 4. Tensor Structures

DAX does not use dense tensors. All numerical data is stored as:
* `std::vector<float>` – 1D arrays
* `std::vector<std::vector<float>>` – 2D arrays
* `std::shared_ptr<T>` – pointer indirection

No N-dimensional tensors with fixed shapes.

## 5. Graph/State Structures

* WeightEvolutionGraph – nodes + edges + clusters
* GridState – points + edges
* LatticeState – nodes + edges
* ResonanceState – events vector
* PatternLifecycleEngine – pattern objects with vectors

These are graph/objects, not tensors.

## 6. Checkpoint.bin Mapping

Current checkpoint implementation:
```cpp
void save_checkpoint(const WeaveContext& ctx, const std::string& path) {
    std::ofstream file(path);
    file << "checkpoint";
}
```
**Actual content**: placeholder text only. No serialization of model state.

## GGUF Mapping Table

| Component | Data type | Shape | Serialization format | GGUF equivalent | Conversion feasibility |
|-----------|-----------|-------|----------------------|-----------------|------------------------|
| WeightScaleFactors.scale | float | scalar | binary float | GGUF_TENSOR_F32 | High |
| PatternVector.weights | float[] | [N] | vector binary | GGUF_TENSOR_F32 | High |
| PatternVector.micro_weights | float[] | [8] | vector binary | GGUF_TENSOR_F32 | High |
| linear_weights_ | float[][] | [M][N] | vector binary | GGUF_TENSOR_F32 | High |
| GridState.points | float[][] | [L][L] | vector binary | GGUF_TENSOR_F32 | Medium |
| LatticeState.edges.weight | float | scalar | binary | GGUF_TENSOR_F32 | Medium |
| ResonanceState.resonance_values | float[] | [K] | vector binary | GGUF_TENSOR_F32 | Medium |
| WeaveContext metadata | string | - | text | GGUF_METADATA | Low |
| WeightEvolutionGraph | graph | variable | custom binary | GGUF_CUSTOM | Low |
| PatternLifecycleEngine patterns | object graph | variable | custom binary | GGUF_CUSTOM | Low |

## Conversion Feasibility Summary

* **High**: Flat float vectors and scalars → direct GGUF tensors
* **Medium**: 2D float arrays → reshape to GGUF tensors
* **Low**: Graph/object structures, shared_ptrs, maps → require custom serialization + metadata

**Recommendation**: Export trainable numeric parameters to GGUF as tensors with metadata describing graph topology. Keep graph/state structures in separate custom format or serialize as JSON metadata alongside GGUF.

GGUF export is feasible for parameter weights but not for full dynamic graph state without custom extensions.
