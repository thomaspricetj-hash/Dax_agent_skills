# DAX Model Format Specification v1.0

## Overview
DAX WeaveFormer checkpoint format is binary, versioned, and supports full model persistence for WeaveContext and all sub-states.

## File Header
```
magic: 4 bytes   = 'DAXM'
version: uint32 = 1
timestamp: uint64
```

## Top Level Structure
```
WeaveContext
  input_text: string
  token_sequence: vector<uint32_t>
  grid_state: GridState*
  cluster_state: ClusterState*
  lattice_state: LatticeState*
  resonance_state: ResonanceState*
  zoom_state: ZoomState*
```

## Serialization Order
1. WeaveContext metadata
2. GridState
3. ClusterState
4. LatticeState
5. ResonanceState
6. ZoomState
7. PatternWeightedMemory
8. WeightEvolutionGraph
9. WeightScalingLayer
10. PatternLifecycleEngine
11. DerivativeSignatureEngine

## Data Types
* string: length uint32 + bytes
* vector<T>: length uint64 + elements
* float: 4 bytes IEEE754
* uint32/uint64: 4/8 bytes little endian
* bool: 1 byte

## Component Formats

### GridState
points: vector<vector<float>>
edges: vector<Edge>
edge_weights: vector<float>
nodes: vector<Node>

### ClusterState
clusters: vector<vector<int>>
cluster_info: map<int,ClusterInfo>
clusters_with_weights: vector<Cluster>

### LatticeState
nodes: vector<Node>
edges: vector<LayerEdge>
depth: int

### ResonanceState
resonance_amplitude: float
phase_offset: float
current_time: uint64
resonance_values: vector<float>
events: vector<ResonanceEvent>

### PatternWeightedMemory
config: PatternConfig
linear_weights_: vector<vector<float>>
pattern_store: ...

### WeightEvolutionGraph
nodes: vector<WeightGraphNode>
edges: vector<WeightEdge>
clusters: vector<WeightCluster>

### WeightScalingLayer
cluster_scales_: map<uint32_t,WeightScaleFactors>

### PatternLifecycleEngine
patterns_: map<uint64_t,PatternObject>
super_patterns_: vector<SuperPattern>

### DerivativeSignatureEngine
signature_db_: vector<DerivativeSignature>
pattern_db_: vector<DerivativePattern>

## Save/Load API
```cpp
bool save_model(const std::string& path);
bool load_model(const std::string& path);
```

## Verification
Save -> Load -> Evaluate must produce identical metrics:
* Accuracy
* Pattern recognition
* Resonance quality
* Cognitive tool performance

## Versioning
Format version 1. Future versions must maintain backward compatibility via header version field.
